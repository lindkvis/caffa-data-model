// ##################################################################################################
//
//    Caffa
//    Copyright (C) 2011-2013 Ceetron AS
//    Copyright (C) 2021 3D-Radar AS
//    Copyright (C) 2022- Kontur AS
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

#include "cafFieldHandle.h"
#include "cafFieldValidator.h"
#include "cafPortableDataType.h"
#include "cafValueProxy.h"

#include "cafAssert.h"

#include "cafLogger.h"

#include <optional>
#include <stdexcept>
#include <vector>

namespace caffa
{

template <typename DataType>
class DereferenceHelper
{
public:
    using FieldType   = DataType;
    using ContentType = DataType;

    static const ContentType& dereference( const DataType& data ) { return data; }
    static const ContentType* pointer( const DataType& data ) { return &data; }

    static ContentType& dereference( DataType& data ) { return data; }
    static ContentType* pointer( DataType& data ) { return &data; }
};

template <typename DataType>
class DereferenceHelper<std::shared_ptr<DataType>>
{
public:
    using FieldType   = std::shared_ptr<DataType>;
    using ContentType = DataType;

    static const ContentType& dereference( const std::shared_ptr<DataType>& data ) { return *data; }
    static const ContentType* pointer( const std::shared_ptr<DataType>& data ) { return data.get(); }

    static ContentType& dereference( std::shared_ptr<DataType>& data ) { return *data; }
    static ContentType* pointer( std::shared_ptr<DataType>& data ) { return data.get(); }
};

/**
 * Typed field class.
 */
template <typename DataType>
class Field : public FieldHandle
{
public:
    using FieldType   = DereferenceHelper<DataType>::FieldType;
    using ContentType = DereferenceHelper<DataType>::ContentType;
    /**
     * Main constructor with default initialisation of the value
     */
    Field()
        : m_value{}
    {
    }

    explicit Field( const Field& other )         = delete;
    explicit Field( const DataType& fieldValue ) = delete;

    ~Field() noexcept override {}

    /**
     * Get a portable string representation of the data type
     * @return a data type name represented as a string
     */
    std::string dataType() const override { return PortableDataType<DataType>::name(); }

    /**
     * Assignment of field value from another field
     * @param other The other field
     * @return this
     */
    Field& operator=( const Field& other )
    {
        this->setValue( other.m_value );
        return *this;
    }

    /**
     * Assignment of field value from another value
     * @param other The new value
     * @return this
     */
    Field& operator=( const DataType& fieldValue )
    {
        this->setValue( fieldValue );
        return *this;
    }

    /**
     * Returns the value of the field *BY VALUE*
     * @return the value of the field
     */
    DataType value()
    {
        CAFFA_ASSERT( this->isInitialized() );
        return m_value;
    }

    /**
     * Assign a new value and check the validators
     * @param fieldValue the new value
     * @throws Throws std::runtime_error if a validation failed.
     */
    void setValue( const DataType& fieldValue )
    {
        CAFFA_ASSERT( this->isInitialized() );

        try
        {
            for ( const auto& validator : m_valueValidators )
            {
                if ( auto [status, message] = validator->validate( fieldValue ); !status )
                {
                    CAFFA_ASSERT( !message.empty() );
                    if ( validator->failureSeverity() == FieldValidatorInterface::FailureSeverity::VALIDATOR_ERROR ||
                         validator->failureSeverity() == FieldValidatorInterface::FailureSeverity::VALIDATOR_CRITICAL )
                    {
                        throw std::runtime_error( message );
                    }
                    else
                    {
                        CAFFA_WARNING( message );
                    }
                }
            }
            m_value = fieldValue;
        }
        catch ( const std::exception& e )
        {
            std::string errorMessage = "Failed to set value for '" + this->keyword() + "': " + e.what();
            CAFFA_ERROR( errorMessage );
            throw std::runtime_error( errorMessage );
        }
    }

    operator ContentType&() { return DereferenceHelper<DataType>::dereference( m_value ); }

    operator const ContentType&() const { return DereferenceHelper<DataType>::dereference( m_value ); }

    const ContentType& operator*() const { return DereferenceHelper<DataType>::dereference( m_value ); }

    ContentType& operator*() { return DereferenceHelper<DataType>::dereference( m_value ); }

    const ContentType* operator->() const { return DereferenceHelper<DataType>::pointer( m_value ); }

    ContentType* operator->() { return DereferenceHelper<DataType>::pointer( m_value ); }

    auto operator<=>( const DataType& fieldValue ) const { return m_value <=> fieldValue; }

    std::vector<const FieldValidator<DataType>*> valueValidators() const
    {
        std::vector<const FieldValidator<DataType>*> allValidators;
        for ( const auto& validator : m_valueValidators )
        {
            allValidators.push_back( validator.get() );
        }
        return allValidators;
    }

    std::vector<FieldValidator<DataType>*> valueValidators()
    {
        std::vector<FieldValidator<DataType>*> allValidators;
        for ( auto& validator : m_valueValidators )
        {
            allValidators.push_back( validator.get() );
        }
        return allValidators;
    }

    void addValidator( std::unique_ptr<FieldValidator<DataType>> valueValidator )
    {
        m_valueValidators.push_back( std::move( valueValidator ) );
        setValue( m_value );
    }

    void clearValidators() { m_valueValidators.clear(); }

public:
    std::optional<FieldType> defaultValue() const { return m_defaultValue; }
    void                     setDefaultValue( const FieldType& val ) { m_defaultValue = val; }

    bool operator==( const Field<DataType>& rhs ) const  = delete;
    auto operator<=>( const Field<DataType>& rhs ) const = delete;

private:
    DataType                                               m_value;
    std::optional<FieldType>                               m_defaultValue;
    std::vector<std::unique_ptr<FieldValidator<DataType>>> m_valueValidators;
};

} // End of namespace caffa
