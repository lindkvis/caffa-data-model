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

#include "cafAssert.h"
#include "cafFieldHandle.h"
#include "cafFieldHelper.h"
#include "cafFieldValidator.h"
#include "cafLogger.h"
#include "cafObjectHandlePortableDataType.h"
#include "cafPortableDataType.h"
#include "cafValueProxy.h"
#include "cafVisitor.h"

#include <optional>
#include <stdexcept>
#include <vector>

namespace caffa
{
/**
 * Typed field class.
 */
template <typename T>
class Field : public FieldHandle
{
public:
    using DataType          = FieldHelper<T>::Type;
    using ContentType       = FieldHelper<T>::ContentType;
    using SerializationType = FieldHelper<T>::SerializationType;
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
    std::string dataType() const override { return PortableDataType<T>::name(); }

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
    Field& operator=( const SerializationType& fieldValue )
    {
        this->setValue( fieldValue );
        return *this;
    }

    /**
     * Returns the value of the field *BY VALUE*
     * @return the value of the field
     */
    [[nodiscard]] SerializationType value()
    {
        CAFFA_ASSERT( this->isInitialized() );
        return FieldHelper<T>::value( m_value );
    }

    /**
     * Returns the value of the field *BY VALUE*
     * @return the value of the field
     */
    [[nodiscard]] SerializationType value() const
    {
        CAFFA_ASSERT( this->isInitialized() );
        return FieldHelper<T>::value( m_value );
    }

    /**
     * @brief Returns a reference to the field content
     *
     * @return const DataType&
     */
    const DataType& reference() const { return m_value; }

    /**
     * @brief Returns a reference to the field content
     *
     * @return DataType&
     */
    DataType& reference() { return m_value; }

    /**
     * Assign a new value and check the validators
     * @param fieldValue the new value
     * @throws Throws std::runtime_error if a validation failed.
     */
    void setValue( const SerializationType& fieldValue )
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

    operator ContentType&() { return FieldHelper<DataType>::dereference( m_value ); }

    operator const ContentType&() const { return FieldHelper<DataType>::dereference( m_value ); }

    const ContentType* operator->() const { return FieldHelper<DataType>::pointer( m_value ); }

    ContentType* operator->() { return FieldHelper<DataType>::pointer( m_value ); }

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

    void accept( Inspector* inspector ) const override { FieldHelper<DataType>::arrangeVisit( inspector, this ); }
    void accept( Editor* editor ) override { FieldHelper<DataType>::arrangeVisit( editor, this ); }

public:
    std::optional<DataType> defaultValue() const { return m_defaultValue; }
    void                    setDefaultValue( const DataType& val ) { m_defaultValue = val; }

    bool operator==( const Field<DataType>& rhs ) const { return m_value == rhs.m_value; }

    auto operator<=>( const Field<DataType>& rhs ) const { return m_value <=> rhs.m_value; }

private:
    friend class FieldHelper<DataType>;

    DataType                                               m_value;
    std::optional<DataType>                                m_defaultValue;
    std::vector<std::unique_ptr<FieldValidator<DataType>>> m_valueValidators;
};

} // End of namespace caffa
