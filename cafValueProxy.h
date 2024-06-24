#pragma once

#include "cafAssert.h"
#include "cafPortableDataType.h"

#include <functional>
#include <type_traits>
#include <vector>

namespace caffa
{
template <typename DataType>
class SetValueInterface
{
public:
    virtual ~SetValueInterface() {}
    virtual void setValue( const DataType& value ) = 0;
};

template <typename DataType>
class SetterMethodCB : public SetValueInterface<DataType>
{
public:
    using SetterMethodType = std::function<void( const DataType& )>;

    SetterMethodCB( SetterMethodType setterMethod ) { m_setterMethod = setterMethod; }

    void setValue( const DataType& value )
    {
        CAFFA_ASSERT( m_setterMethod );
        m_setterMethod( value );
    }

private:
    SetterMethodType m_setterMethod;
};

template <typename DataType>
class GetValueInterface
{
public:
    virtual ~GetValueInterface() {}
    virtual DataType getValue() const = 0;
};

template <typename DataType>
class GetterMethodCB : public GetValueInterface<DataType>
{
public:
    using GetterMethodType = std::function<DataType()>;

    GetterMethodCB( GetterMethodType setterMethod ) { m_getterMethod = setterMethod; }

    DataType getValue() const { return m_getterMethod(); }

private:
    GetterMethodType m_getterMethod;
};

template <typename DataType>
class ValueProxy
{
public:
    DataType value()
    {
        if ( !m_valueGetter ) throw std::runtime_error( "No getter for field" );
        return m_valueGetter->getValue();
    }

    void setValue( const DataType& value )
    {
        if ( !m_valueSetter ) throw std::runtime_error( "No setter for field" );
        m_valueSetter->setValue( value );
    }

    ValueProxy<DataType>& operator=( const DataType& value )
    {
        setValue( value );
        return *this;
    }

    ValueProxy<DataType>& operator=( const ValueProxy<DataType>& proxy )
    {
        setValue( proxy.value() );
        return *this;
    }
    // Proxy Field stuff to handle the method pointers
    // The public registering methods must be written below the private classes
    // For some reason. Forward declaration did some weirdness.
    void registerSetMethod( typename SetterMethodCB<DataType>::SetterMethodType setterMethod )
    {
        m_valueSetter = std::make_unique<SetterMethodCB<DataType>>( setterMethod );
    }

    void registerGetMethod( typename GetterMethodCB<DataType>::GetterMethodType getterMethod )
    {
        m_valueGetter = std::make_unique<GetterMethodCB<DataType>>( getterMethod );
    }

    bool hasSetter() const { return m_valueSetter != nullptr; }
    bool hasGetter() const { return m_valueGetter != nullptr; }

private:
    std::unique_ptr<SetValueInterface<DataType>> m_valueSetter;
    std::unique_ptr<GetValueInterface<DataType>> m_valueGetter;
};

template <typename DataType>
struct PortableDataType<ValueProxy<DataType>>
{
    static std::string name() { return PortableDataType<DataType>::name(); }
};

} // End of namespace caffa