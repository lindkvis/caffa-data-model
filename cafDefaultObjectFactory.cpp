#include "cafDefaultObjectFactory.h"

#include <ranges>

namespace caffa
{
//--------------------------------------------------------------------------------------------------
///  ObjectFactory implementations
//--------------------------------------------------------------------------------------------------

std::list<std::string> DefaultObjectFactory::classes() const
{
    std::list<std::string> classList;
    for ( const auto& name : std::views::keys( m_factoryMap ) )
    {
        classList.push_back( name );
    }
    return classList;
}

//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
std::shared_ptr<ObjectHandle> DefaultObjectFactory::doCreate( const std::string_view& classKeyword )
{
    if ( const auto entryIt = m_factoryMap.find( classKeyword ); entryIt != m_factoryMap.end() )
    {
        return entryIt->second->create();
    }
    return nullptr;
}

//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
std::shared_ptr<DefaultObjectFactory> DefaultObjectFactory::instance()
{
    static auto fact = std::shared_ptr<DefaultObjectFactory>( new DefaultObjectFactory );
    return fact;
}

} // End of namespace caffa
