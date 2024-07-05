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
    if ( auto entryIt = m_factoryMap.find( classKeyword ); entryIt != m_factoryMap.end() )
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
    static auto objectFactory = std::shared_ptr<DefaultObjectFactory>( new DefaultObjectFactory );
    return objectFactory;
}

} // End of namespace caffa
