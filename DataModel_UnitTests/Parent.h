#pragma once

#include "Child.h"

#include "cafField.h"
#include "cafObjectHandle.h"
#include "cafObjectMacros.h"

class Parent : public caffa::ObjectHandle
{
    CAFFA_HEADER_INIT( Parent, ObjectHandle )

public:
    Parent();

    caffa::Field<std::vector<std::shared_ptr<Child>>> m_simpleObjectVectorField;
    caffa::Field<std::shared_ptr<Child>>              m_simpleObjectField;
};
