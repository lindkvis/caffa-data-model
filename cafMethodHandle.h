// ##################################################################################################
//
//    Caffa
//    Copyright (C) Kontur As
//
//    GNU Lesser General Public License Usage
//    This library is free software; you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation; either version 2.1 of the License, or
//    (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful, but WITHOUT ANY
//    WARRANTY; without even the implied warranty of MERCHANTABILITY or
//    FITNESS FOR A PARTICULAR PURPOSE.
//
//    See the GNU Lesser General Public License at <<http://www.gnu.org/licenses/lgpl-2.1.html>>
//    for more details.
//
// ##################################################################################################
#pragma once

#include <string>
#include <vector>

namespace caffa
{
class MethodHandle;
class ObjectHandle;
class ObjectFactory;
class Session;

class MethodAccessorInterface
{
public:
    MethodAccessorInterface( const ObjectHandle* selfHandle, const MethodHandle* methodHandle, ObjectFactory* objectFactory )
        : m_selfHandle( selfHandle )
        , m_methodHandle( methodHandle )
        , m_objectFactory( objectFactory )
    {
    }
    virtual ~MethodAccessorInterface()                                                   = default;
    [[nodiscard]] virtual std::string execute( const std::string& argumentString ) const = 0;

    [[nodiscard]] ObjectFactory* objectFactory() const { return m_objectFactory; }

protected:
    const ObjectHandle* m_selfHandle;
    const MethodHandle* m_methodHandle;
    ObjectFactory*      m_objectFactory;
};

class MethodHandle
{
public:
    MethodHandle()
        : m_isConst( false )
    {
    }
    virtual ~MethodHandle() = default;

    [[nodiscard]] std::string keyword() const { return m_name; }
    void setArgumentNames( const std::vector<std::string>& argumentNames ) { m_argumentNames = argumentNames; }
    [[nodiscard]] const std::vector<std::string>& argumentNames() const { return m_argumentNames; }

    [[nodiscard]] bool               isConst() const { return m_isConst; }
    void                             setConst( bool isConst ) { m_isConst = isConst; }
    [[nodiscard]] const std::string& documentation() const { return m_documentation; }
    void setDocumentation( const std::string& documentation ) { m_documentation = documentation; }

    [[nodiscard]] virtual std::string execute( std::shared_ptr<Session> session,
                                               const std::string&       argumentsString ) const = 0;
    [[nodiscard]] virtual std::string schema() const                                      = 0;

    [[nodiscard]] MethodAccessorInterface* accessor() const { return m_accessor.get(); }
    void setAccessor( std::unique_ptr<MethodAccessorInterface> accessor ) { m_accessor = std::move( accessor ); }

private:
    friend class ObjectHandle;
    void setName( const std::string& name ) { m_name = name; }

    std::string              m_name;
    std::vector<std::string> m_argumentNames;
    bool                     m_isConst;
    std::string              m_documentation;

    std::unique_ptr<MethodAccessorInterface> m_accessor;
};
} // namespace caffa