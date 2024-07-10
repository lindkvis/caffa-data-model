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

#include "cafVisitor.h"

#include "cafChildFieldHandle.h"
#include "cafDataField.h"
#include "cafObjectHandle.h"

using namespace caffa;

Inspector::Inspector( const bool requireReadable )
    : m_requireReadable( requireReadable )
{
}

void Inspector::visit( const ObjectHandle* object )
{
    visitObject( object );

    for ( const auto field : object->fields() )
    {
        if ( !m_requireReadable || field->isReadable() )
        {
            field->accept( this );
        }
    }

    leaveObject( object );
}

void Inspector::visit( const ChildFieldBaseHandle* field )
{
    visitField( field );

    size_t index = 0;
    for ( const auto& object : field->childObjects() )
    {
        this->visitChild( field, index );
        object->accept( this );
        this->leaveChild( field, index++ );
    }

    leaveField( field );
}

void Inspector::visit( const DataField* field )
{
    visitField( field );
    leaveField( field );
}

Editor::Editor( const bool requireWritable )
    : m_requireWritable( requireWritable )
{
}

void Editor::visit( ObjectHandle* object )
{
    visitObject( object );

    for ( const auto field : object->fields() )
    {
        if ( !m_requireWritable || field->isWritable() )
        {
            field->accept( this );
        }
    }
    leaveObject( object );
}

void Editor::visit( ChildFieldBaseHandle* field )
{
    visitField( field );

    size_t index = 0;
    for ( const auto& object : field->childObjects() )
    {
        this->visitChild( field, index );
        object->accept( this );
        this->leaveChild( field, index++ );
    }
    leaveField( field );
}

void Editor::visit( DataField* field )
{
    visitField( field );
    leaveField( field );
}
