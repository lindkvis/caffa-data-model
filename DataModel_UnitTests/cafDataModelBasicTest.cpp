
#include "gtest/gtest.h"

#include "Child.h"
#include "Parent.h"

#include "cafField.h"
#include "cafObjectCollector.h"
#include "cafObjectHandle.h"
#include "cafObjectMacros.h"
#include "cafPortableDataType.h"
#include "cafValueProxy.h"

#include <functional>
#include <map>
#include <vector>
namespace caffa
{
class Serializer;
}

using namespace std::placeholders;

class DemoObject : public caffa::ObjectHandle
{
    CAFFA_HEADER_INIT( DemoObject, ObjectHandle )

public:
    DemoObject()
    {
        addField( &m_proxyDoubleField, "m_proxyDoubleField" );

        m_proxyDoubleField->registerSetMethod( std::bind( &DemoObject::setDoubleMember, this, _1 ) );
        m_proxyDoubleField->registerGetMethod( std::bind( &DemoObject::doubleMember, this ) );

        addField( &m_proxyIntField, "m_proxyIntField" );
        m_proxyIntField->registerSetMethod( std::bind( &DemoObject::setIntMember, this, _1 ) );
        m_proxyIntField->registerGetMethod( std::bind( &DemoObject::intMember, this ) );

        addField( &m_proxyStringField, "m_proxyStringField" );
        m_proxyStringField->registerSetMethod( std::bind( &DemoObject::setStringMember, this, _1 ) );
        m_proxyStringField->registerGetMethod( std::bind( &DemoObject::stringMember, this ) );

        addField( &m_memberDoubleField, "m_memberDoubleField" );
        addField( &m_memberIntField, "m_memberIntField" );
        addField( &m_memberStringField, "m_memberStringField" );

        // Default values
        m_doubleMember = 2.1;
        m_intMember    = 7;
        m_stringMember = "abba";

        m_memberDoubleField = 0.0;
        m_memberIntField    = 0;
        m_memberStringField = "";
    }

    // Fields
    caffa::Field<caffa::ValueProxy<double>>      m_proxyDoubleField;
    caffa::Field<caffa::ValueProxy<int>>         m_proxyIntField;
    caffa::Field<caffa::ValueProxy<std::string>> m_proxyStringField;

    caffa::Field<double>      m_memberDoubleField;
    caffa::Field<int>         m_memberIntField;
    caffa::Field<std::string> m_memberStringField;

    // Internal class members accessed by proxy fields
    double doubleMember() const
    {
        std::cout << "doubleMember" << std::endl;
        return m_doubleMember;
    }
    void setDoubleMember( const double& d )
    {
        m_doubleMember = d;
        std::cout << "setDoubleMember" << std::endl;
    }

    int  intMember() const { return m_intMember; }
    void setIntMember( const int& val ) { m_intMember = val; }

    std::string stringMember() const { return m_stringMember; }
    void        setStringMember( const std::string& val ) { m_stringMember = val; }

private:
    double      m_doubleMember;
    int         m_intMember;
    std::string m_stringMember;
};

CAFFA_SOURCE_INIT( DemoObject )

class InheritedDemoObj : public DemoObject
{
    CAFFA_HEADER_INIT( InheritedDemoObj, DemoObject )

public:
    InheritedDemoObj()
    {
        addField( &m_texts, "Texts" );
        addField( &m_childArrayField, "DemoObjectects" );
    }

    caffa::Field<std::string>                              m_texts;
    caffa::Field<std::vector<std::shared_ptr<DemoObject>>> m_childArrayField;
};

TEST( DataModelTest, Delete )
{
    DemoObject* s2 = new DemoObject;
    delete s2;
}

CAFFA_SOURCE_INIT( InheritedDemoObj )

//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
TEST( DataModelTest, TestInheritanceStack )
{
    InheritedDemoObj              demoObj;
    auto                          stack = demoObj.classInheritanceStack();
    std::vector<std::string_view> validEntries;
    for ( auto entry : stack )
    {
        if ( !entry.empty() )
        {
            CAFFA_INFO( "Valid entry in stack for InheritedDemoObj: " << entry );
            validEntries.push_back( entry );
        }
    }
    ASSERT_EQ( (size_t)3, validEntries.size() );
}

//--------------------------------------------------------------------------------------------------
/// TestField
//--------------------------------------------------------------------------------------------------
TEST( DataModelTest, TestField )
{
    auto a = std::make_shared<DemoObject>();

    ASSERT_DOUBLE_EQ( 0.0, a->m_memberDoubleField.value() );
    a->m_memberDoubleField.setValue( 1.2 );
    ASSERT_DOUBLE_EQ( 1.2, a->m_memberDoubleField.value() );

    // Simpler access
    ASSERT_DOUBLE_EQ( 1.2, a->m_memberDoubleField.reference() );
    a->m_memberDoubleField = 42.0;
    ASSERT_DOUBLE_EQ( 42.0, a->m_memberDoubleField.value() );
    ASSERT_EQ( 0, a->m_memberIntField.value() );
    ASSERT_NO_THROW( a->m_memberIntField = 1000 );
    ASSERT_NO_THROW( a->m_memberIntField = -10 );
    ASSERT_NO_THROW( a->m_memberIntField = 11 );
    ASSERT_EQ( 11, a->m_memberIntField.value() );

    ASSERT_TRUE( a->m_memberStringField->empty() );
    a->m_memberStringField.setValue( "123" );
    ASSERT_TRUE( a->m_memberStringField.value() == "123" );
}

//--------------------------------------------------------------------------------------------------
/// TestProxyTypedField
//--------------------------------------------------------------------------------------------------
TEST( DataModelTest, TestProxyTypedField )
{
    auto a = std::make_shared<DemoObject>();

    ASSERT_DOUBLE_EQ( 2.1, a->m_proxyDoubleField->value() );
    a->m_proxyDoubleField->setValue( 1.2 );
    ASSERT_DOUBLE_EQ( 1.2, a->m_proxyDoubleField->value() );

    ASSERT_EQ( 7, a->m_proxyIntField->value() );
    a->m_proxyIntField->setValue( 11 );
    ASSERT_EQ( 11, a->m_proxyIntField->value() );

    ASSERT_TRUE( a->m_proxyStringField->value() == "abba" );
    a->m_proxyStringField->setValue( "123" );
    ASSERT_TRUE( a->m_proxyStringField->value() == "123" );
}

class A : public caffa::ObjectHandle
{
    CAFFA_HEADER_INIT( A, ObjectHandle )

public:
    A() {}

    explicit A( const std::vector<double>& testValue )
    {
        addField( &field1, "field1" );
        addField( &field2, "field2" );
        addField( &field3, "field3" );

        field2 = testValue;
        field3 = field2;
    }

    caffa::Field<std::vector<double>> field1;
    caffa::Field<std::vector<double>> field2;
    caffa::Field<std::vector<double>> field3;
};

CAFFA_SOURCE_INIT( A )

//--------------------------------------------------------------------------------------------------
/// Test of Field operations
//--------------------------------------------------------------------------------------------------
TEST( DataModelTest, NormalField )
{
    std::vector<double> testValue;
    testValue.push_back( 1.1 );
    testValue.push_back( 1.2 );
    testValue.push_back( 1.3 );

    std::vector<double> testValue2;
    testValue2.push_back( 2.1 );
    testValue2.push_back( 2.2 );
    testValue2.push_back( 2.3 );

    // Constructors

    A a( testValue );

    EXPECT_EQ( 1.3, a.field2->at( 2 ) );
    EXPECT_EQ( 1.3, a.field3->at( 2 ) );
    EXPECT_EQ( size_t( 0 ), a.field1->size() );

    // Operators
    // ==
    EXPECT_FALSE( a.field1.value() == a.field3.value() );
    // = field to field
    a.field1 = a.field2;
    // value()
    EXPECT_EQ( 1.3, a.field1.value()[2] );
    // = value to field
    a.field1 = testValue2;
    // *v
    EXPECT_EQ( 2.3, a.field1.reference()[2] );
    // = with dereference
    a.field3 = a.field1.value();
    EXPECT_TRUE( a.field1.value() == a.field3.value() );
}

//--------------------------------------------------------------------------------------------------
/// Test of ChildArrayField operations
//--------------------------------------------------------------------------------------------------

TEST( DataModelTest, ChildArrayField )
{
    auto ihd1 = std::make_shared<InheritedDemoObj>();

    auto s1 = std::make_shared<DemoObject>();
    auto s2 = std::make_shared<DemoObject>();
    auto s3 = std::make_shared<DemoObject>();

    std::weak_ptr<DemoObject> s1p = s1;
    std::weak_ptr<DemoObject> s2p = s2;
    std::weak_ptr<DemoObject> s3p = s3;

    // empty() number 1
    EXPECT_TRUE( ihd1->m_childArrayField->empty() );
    EXPECT_EQ( size_t( 0 ), ihd1->m_childArrayField->size() );

    ihd1->m_childArrayField->push_back( s1 );
    ihd1->m_childArrayField->push_back( s2 );
    ihd1->m_childArrayField->push_back( s3 );

    EXPECT_EQ( 2, s1.use_count() );
    EXPECT_EQ( 2, s2.use_count() );
    EXPECT_EQ( 2, s3.use_count() );

    // size()
    EXPECT_EQ( size_t( 3 ), ihd1->m_childArrayField->size() );

    // operator[]
    EXPECT_EQ( s1, ihd1->m_childArrayField->at( 0 ) );
    EXPECT_EQ( s2, ihd1->m_childArrayField->at( 1 ) );
    EXPECT_EQ( s3, ihd1->m_childArrayField->at( 2 ) );

    // children by reference
    {
        auto& objects = ihd1->m_childArrayField.reference();
        EXPECT_EQ( size_t( 3 ), objects.size() );
        EXPECT_EQ( 2, s1.use_count() );
        EXPECT_EQ( 2, s2.use_count() );
        EXPECT_EQ( 2, s3.use_count() );
    }

    // children by value
    {
        auto objects = ihd1->m_childArrayField.value();
        EXPECT_EQ( size_t( 3 ), objects.size() );
        EXPECT_EQ( 3, s1.use_count() );
        EXPECT_EQ( 3, s2.use_count() );
        EXPECT_EQ( 3, s3.use_count() );
    }

    EXPECT_EQ( 2, s1.use_count() );
    EXPECT_EQ( 2, s2.use_count() );
    EXPECT_EQ( 2, s3.use_count() );

    // remove child object
    ihd1->m_childArrayField->erase( std::find( ihd1->m_childArrayField->begin(), ihd1->m_childArrayField->end(), s2 ) );
    EXPECT_EQ( size_t( 2 ), ihd1->m_childArrayField->size() );
    EXPECT_EQ( 2, s1.use_count() );
    EXPECT_EQ( 1, s2.use_count() );
    EXPECT_EQ( 2, s3.use_count() );

    auto it = std::find( ihd1->m_childArrayField->begin(), ihd1->m_childArrayField->end(), nullptr );
    ASSERT_TRUE( it == ihd1->m_childArrayField->end() );

    ihd1->m_childArrayField->erase( it, ihd1->m_childArrayField->end() );
    EXPECT_EQ( size_t( 2 ), ihd1->m_childArrayField->size() );

    EXPECT_EQ( s3, ihd1->m_childArrayField->at( 1 ) );
    EXPECT_EQ( s1, ihd1->m_childArrayField->at( 0 ) );

    // insertAt()
    ihd1->m_childArrayField->insert( ihd1->m_childArrayField->begin() + 1, s2 );
    EXPECT_EQ( size_t( 3 ), ihd1->m_childArrayField->size() );
    EXPECT_EQ( s1, ihd1->m_childArrayField->at( 0 ) );
    EXPECT_EQ( s2, ihd1->m_childArrayField->at( 1 ) );
    EXPECT_EQ( s3, ihd1->m_childArrayField->at( 2 ) );

    // erase (index)
    EXPECT_EQ( size_t( 3 ), ihd1->m_childArrayField->size() );

    {
        caffa::ObjectCollector collector;
        collector.visit( ihd1.get() );
        ASSERT_EQ( size_t( 4 ), collector.objects().size() );
    }

    ihd1->m_childArrayField->erase( ihd1->m_childArrayField->begin() + 1 );
    EXPECT_TRUE( s2 );
    EXPECT_EQ( size_t( 2 ), ihd1->m_childArrayField->size() );
    EXPECT_EQ( s3, ihd1->m_childArrayField->at( 1 ) );
    EXPECT_EQ( s1, ihd1->m_childArrayField->at( 0 ) );

    {
        caffa::ObjectCollector collector;
        collector.visit( ihd1.get() );
        ASSERT_EQ( size_t( 3 ), collector.objects().size() );
    }
    // clear()
    auto extractedObjects = ihd1->m_childArrayField.value();

    EXPECT_EQ( 3, s1.use_count() );
    EXPECT_EQ( 1, s2.use_count() );
    EXPECT_EQ( 3, s3.use_count() );

    ihd1->m_childArrayField->clear();

    EXPECT_EQ( size_t( 2 ), extractedObjects.size() );
    EXPECT_EQ( size_t( 0 ), ihd1->m_childArrayField->size() );

    for ( auto& object : extractedObjects )
    {
        ihd1->m_childArrayField->push_back( object );
    }

    s1.reset();
    s2.reset();
    s3.reset();

    EXPECT_TRUE( s1 == nullptr );
    EXPECT_TRUE( s2 == nullptr );
    EXPECT_TRUE( s3 == nullptr );

    EXPECT_EQ( size_t( 2 ), ihd1->m_childArrayField->size() );
    EXPECT_FALSE( s1p.expired() );
    EXPECT_TRUE( s2p.expired() );
    EXPECT_FALSE( s3p.expired() );

    extractedObjects.clear();
    EXPECT_FALSE( s1p.expired() );
    EXPECT_TRUE( s2p.expired() );
    EXPECT_FALSE( s3p.expired() );

    ihd1->m_childArrayField->clear();
    EXPECT_EQ( size_t( 0 ), ihd1->m_childArrayField->size() );
    EXPECT_TRUE( s1p.expired() );
    EXPECT_TRUE( s2p.expired() );
    EXPECT_TRUE( s3p.expired() );
}

TEST( DataModelTest, ChildArrayParentField )
{
    // Test of instanciating a class with forward declare of object used in ChildArrayField and ChildField
    Parent* parentObj = new Parent;

    delete parentObj;
}

TEST( DataModelTest, PointersFieldInsertVector )
{
    auto ihd1 = std::make_shared<Parent>();

    auto s1 = std::make_shared<Child>();
    auto s2 = std::make_shared<Child>();
    auto s3 = std::make_shared<Child>();

    std::vector<std::shared_ptr<Child>> typedObjects;
    typedObjects.push_back( s1 );
    typedObjects.push_back( s2 );
    typedObjects.push_back( s3 );

    ihd1->m_simpleObjectVectorField->push_back( std::make_shared<Child>() );
    for ( auto& typedObject : typedObjects )
    {
        ihd1->m_simpleObjectVectorField->push_back( typedObject );
    }
    EXPECT_EQ( size_t( 4 ), ihd1->m_simpleObjectVectorField->size() );
    EXPECT_EQ( ihd1->m_simpleObjectVectorField->at( 3 ), s3 );

    ihd1->m_simpleObjectField = std::make_shared<Child>();

    {
        caffa::ObjectCollector collector;
        collector.visit( ihd1.get() );
        ASSERT_EQ( size_t( 6 ), collector.objects().size() );
    }
}

class A2 : public caffa::ObjectHandle
{
    CAFFA_HEADER_INIT( A2, ObjectHandle )

public:
    explicit A2()
        : b( 0 )
    {
        addField( &field2, "field2" );
    }

    caffa::Field<std::shared_ptr<Child>> field2;
    int                                  b;
};

CAFFA_SOURCE_INIT( A2 )
//--------------------------------------------------------------------------------------------------
/// Test of ChildField
//--------------------------------------------------------------------------------------------------

TEST( DataModelTest, ChildField )
{
    {
        std::weak_ptr<Child> weakPtr;

        {
            auto testValue = std::make_shared<Child>();
            weakPtr        = testValue;
            EXPECT_FALSE( weakPtr.expired() );

            A2 a;
            a.field2 = testValue;
            EXPECT_EQ( a.field2.value(), weakPtr.lock() );
        }
        // Guarded
        EXPECT_TRUE( weakPtr.expired() );
    }
    {
        A2   a;
        auto c2 = std::make_shared<Child>();
        // Assign
        a.field2 = c2;

        a.field2->doSomething();
        // Access
        EXPECT_EQ( c2, a.field2.value() );
        EXPECT_TRUE( c2 == a.field2.value() );
    }
}

//--------------------------------------------------------------------------------------------------
/// Tests the features of Pointer
//--------------------------------------------------------------------------------------------------
TEST( DataModelTest, Pointer )
{
    auto d = std::make_shared<InheritedDemoObj>();

    {
        std::weak_ptr<InheritedDemoObj> p;
        EXPECT_TRUE( p.expired() );
    }

    {
        std::weak_ptr<InheritedDemoObj> p  = d;
        std::weak_ptr<InheritedDemoObj> p2 = p.lock();

        EXPECT_EQ( p.lock().get(), d.get() );
        EXPECT_EQ( p2.lock().get(), d.get() );
        p.reset();
        EXPECT_TRUE( p.lock() == nullptr );
        EXPECT_TRUE( p.expired() );
        p = p2.lock();
        EXPECT_TRUE( p.lock() == d );
        d.reset();
        EXPECT_TRUE( p.expired() && p2.expired() );
    }
}

class ObjectWithPointerInField : public caffa::ObjectHandle
{
    CAFFA_HEADER_INIT( DemoObject, ObjectHandle )

public:
    ObjectWithPointerInField() { addField( &fieldWithPointer, "fieldWithPointer" ); }

    caffa::Field<std::shared_ptr<DemoObject>> fieldWithPointer;
};

TEST( DataModelTest, PointerInRegularField )
{
    ObjectWithPointerInField object;
    object.fieldWithPointer = std::make_shared<DemoObject>();

    // object.fieldWithPointer->
}
