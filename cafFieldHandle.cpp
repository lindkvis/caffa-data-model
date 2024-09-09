#include "cafFieldHandle.h"

#include "cafFieldCapability.h"
#include "cafObjectHandle.h"

#include <typeinfo>

namespace caffa
{
//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
FieldHandle::FieldHandle()
    : m_ownerObject( nullptr )
    , m_isDeprecated( false )
{
}

//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
FieldHandle::~FieldHandle()
{
}

void FieldHandle::updateLastModified()
{
    m_lastModified = std::chrono::system_clock::now();
}

//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
void FieldHandle::setKeyword( const std::string& keyword )
{
    m_keyword = keyword;
}

//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
ObjectHandle* FieldHandle::ownerObject()
{
    return m_ownerObject;
}

//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
const ObjectHandle* FieldHandle::ownerObject() const
{
    return m_ownerObject;
}

bool FieldHandle::isDeprecated() const
{
    return m_isDeprecated;
}

void FieldHandle::markDeprecated()
{
    m_isDeprecated = true;
}

void FieldHandle::setDocumentation( const std::string& documentation )
{
    m_documentation = documentation;
}

const std::string& FieldHandle::documentation() const
{
    return m_documentation;
}

const std::chrono::system_clock::time_point& FieldHandle::lastModified() const
{
    return m_lastModified;
}

} // End of namespace caffa
