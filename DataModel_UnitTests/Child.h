#pragma once

#include "TestObj.h"
#include "cafObjectHandle.h"
#include "cafObjectMacros.h"

#include "cafLogger.h"

class Child : public caffa::ObjectHandle
{
    CAFFA_HEADER_INIT( Child, ObjectHandle )

public:
    Child();
    ~Child();

    void doSomething() { CAFFA_INFO( "Doing something!" ); }

    caffa::Field<std::shared_ptr<TestObj>> m_testObj;
};
