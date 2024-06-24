// ##################################################################################################
//
//    Caffa
//    Copyright (C) 2024- Kontur AS
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

#include "cafObjectHandle.h"
#include "cafPortableDataType.h"
#include "cafValueProxy.h"
#include "cafVisitor.h"

namespace caffa
{
template <typename DataType>
class Field;

template <typename DataType>
class FieldHelper
{
public:
    using Type              = DataType;
    using ContentType       = DataType;
    using FieldType         = Field<Type>;
    using SerializationType = DataType;

    static const ContentType& dereference( const Type& data ) { return data; }
    static const ContentType* pointer( const Type& data ) { return &data; }

    static ContentType& dereference( Type& data ) { return data; }
    static ContentType* pointer( Type& data ) { return &data; }

    static void arrangeVisit( Inspector* inspector, const FieldType* self ) { inspector->visit( self ); }
    static void arrangeVisit( Editor* editor, FieldType* self ) { editor->visit( self ); }

    static Type value( const Type& data ) { return data; }

    static std::string dataType( const Type& data ) { return PortableDataType<Type>::name(); }
};

template <typename DataType>
class FieldHelper<ValueProxy<DataType>>
{
public:
    using Type              = ValueProxy<DataType>;
    using ContentType       = ValueProxy<DataType>;
    using FieldType         = Field<Type>;
    using SerializationType = DataType;

    static const ContentType& dereference( const Type& data ) { return data; }
    static const ContentType* pointer( const Type& data ) { return &data; }

    static ContentType& dereference( Type& data ) { return data; }
    static ContentType* pointer( Type& data ) { return &data; }

    static void arrangeVisit( Inspector* inspector, const FieldType* self ) { inspector->visit( self ); }
    static void arrangeVisit( Editor* editor, FieldType* self ) { editor->visit( self ); }

    static DataType value( const Type& data ) { return data.value(); }
    static DataType value( Type& data ) { return data.value(); }

    static std::string dataType( const Type& data ) { return PortableDataType<DataType>::name(); }
};

template <typename DataType>
class FieldHelper<std::shared_ptr<DataType>>
{
public:
    using Type              = std::shared_ptr<DataType>;
    using ContentType       = DataType;
    using FieldType         = Field<Type>;
    using SerializationType = Type;

    static const ContentType& dereference( const Type& data ) { return *data; }
    static const ContentType* pointer( const Type& data ) { return data.get(); }

    static ContentType& dereference( Type& data ) { return *data; }
    static ContentType* pointer( Type& data ) { return data.get(); }

    static void arrangeVisit( Inspector* inspector, const FieldType* self )
    {
        inspector->visit( self );
        inspector->visit( self->m_value.get() );
    }
    static void arrangeVisit( Editor* editor, FieldType* self )
    {
        editor->visit( self );
        if ( self->m_value )
        {
            editor->visit( self->m_value.get() );
        }
    }

    static std::shared_ptr<const DataType> value( const Type& data ) { return data; }
    static std::shared_ptr<DataType>       value( Type& data ) { return data; }
    static std::string                     dataType( const Type& data ) { return PortableDataType<Type>::name(); }
};

template <typename DataType>
class FieldHelper<std::vector<std::shared_ptr<DataType>>>
{
public:
    using Type              = std::vector<std::shared_ptr<DataType>>;
    using ContentType       = Type;
    using FieldType         = Field<Type>;
    using SerializationType = Type;

    static const ContentType& dereference( const Type& data ) { return data; }
    static const ContentType* pointer( const Type& data ) { return &data; }

    static ContentType& dereference( Type& data ) { return data; }
    static ContentType* pointer( Type& data ) { return &data; }

    static void arrangeVisit( Inspector* inspector, const FieldType* self )
    {
        inspector->visit( self );
        for ( auto objPtr : self->m_value )
        {
            inspector->visit( objPtr.get() );
        }
    }
    static void arrangeVisit( Editor* editor, FieldType* self )
    {
        editor->visit( self );
        for ( auto objPtr : self->m_value )
        {
            editor->visit( objPtr.get() );
        }
    }

    static std::vector<std::shared_ptr<const DataType>> value( const Type& data )
    {
        std::vector<std::shared_ptr<const DataType>> ptrs;
        ptrs.reserve( data.size() );
        for ( auto ptr : data )
        {
            ptrs.emplace_back( ptr );
        }
        return ptrs;
    }

    static Type value( Type& data ) { return data; }

    static std::string dataType( const Type& data ) { return PortableDataType<Type>::name(); }
};
} // namespace caffa