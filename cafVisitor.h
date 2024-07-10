// ##################################################################################################
//
//    CAFFA
//    Copyright (C) 2023- Kontur AS
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

#include <cstddef>

namespace caffa
{
class ChildFieldBaseHandle;
class DataField;
class FieldHandle;
class ObjectHandle;

/**
 * A visitor which is only allowed to inspect objects
 */
class Inspector
{
public:
    explicit Inspector( bool requireReadable = true );
    virtual ~Inspector() = default;

    void visit( const ObjectHandle* object );
    void visit( const ChildFieldBaseHandle* field );
    void visit( const DataField* field );

private:
    virtual void visitObject( const ObjectHandle* object ) = 0;
    virtual void visitField( const FieldHandle* field )    = 0;
    virtual void leaveObject( const ObjectHandle* object ) {}
    virtual void leaveField( const FieldHandle* field ) {}
    virtual void visitChild( const ChildFieldBaseHandle* field, size_t index ) {}
    virtual void leaveChild( const ChildFieldBaseHandle* field, size_t index ) {}

    bool m_requireReadable;
};

/**
 * A visitor which is allowed to edit objects
 */
class Editor
{
public:
    explicit Editor( bool requireWritable = true );
    virtual ~Editor() = default;

    void visit( ObjectHandle* object );
    void visit( ChildFieldBaseHandle* field );
    void visit( DataField* field );

private:
    virtual void visitObject( ObjectHandle* object ) = 0;
    virtual void visitField( FieldHandle* field )    = 0;
    virtual void leaveObject( ObjectHandle* object ) {}
    virtual void leaveField( FieldHandle* field ) {}
    virtual void visitChild( ChildFieldBaseHandle* field, size_t index ) {}
    virtual void leaveChild( ChildFieldBaseHandle* field, size_t index ) {}

    bool m_requireWritable;
};

} // namespace caffa
