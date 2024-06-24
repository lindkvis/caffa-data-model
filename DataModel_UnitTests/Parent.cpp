#include "Parent.h"
#include "Child.h"

CAFFA_SOURCE_INIT( Parent )

Parent::Parent()
{
    addField( &m_simpleObjectVectorField, "SimpleObjects" );
    addField( &m_simpleObjectField, "SimpleObject" );
}

#include "gtest/gtest.h"

TEST( IncludeTest, Basic )
{
    auto p = std::make_shared<Parent>();
}
