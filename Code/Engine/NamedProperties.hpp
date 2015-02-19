#ifndef include_NamedProperties
#define include_NamedProperties
#pragma once

//-----------------------------------------------------------------------------------------------
#include <map>
#include <string>


//-----------------------------------------------------------------------------------------------
enum PropertyGetResult
{
	PROPERTY_GET_SUCCESS,
	PROPERTY_GET_FAILED_NOT_FOUND,
	PROPERTY_GET_FAILED_TYPE_MISMATCH,
	PROPERTY_GET_FAILED_PROPERTY_WAS_EMPTY,
};


//-----------------------------------------------------------------------------------------------
class NamedPropertiesBase
{
public:
	virtual ~NamedPropertiesBase() {}
};


//-----------------------------------------------------------------------------------------------
template< typename T_PropertyDataType >
class TypeNamedProperties : public NamedPropertiesBase
{
public:
	T_PropertyDataType	m_data;
};


//-----------------------------------------------------------------------------------------------
class NamedProperties
{
public:
	NamedProperties() {}
	~NamedProperties();
	void SetProperty( const std::string& propertyName, const char* typedDataValue );
	template< typename T_PropertyDataType >
		void SetProperty( const std::string& propertyName, const T_PropertyDataType& typedDataValue );
	template< typename T_PropertyDataType >
		PropertyGetResult GetProperty( const std::string& propertyName, T_PropertyDataType& typedData_out ) const;


private:
	std::map< std::string, NamedPropertiesBase* >	m_properties;
};


//-----------------------------------------------------------------------------------------------
inline NamedProperties::~NamedProperties()
{
	std::map< std::string, NamedPropertiesBase* >::iterator mapIter;
	for( mapIter = m_properties.begin(); mapIter != m_properties.end(); ++mapIter )
	{
		delete mapIter->second;
	}

	m_properties.clear();
}


//-----------------------------------------------------------------------------------------------
inline void NamedProperties::SetProperty( const std::string& propertyName, const char* typedDataValue )
{
	SetProperty( propertyName, std::string( typedDataValue ) );
}


//-----------------------------------------------------------------------------------------------
template< typename T_PropertyDataType >
inline void NamedProperties::SetProperty( const std::string& propertyName, const T_PropertyDataType& typedDataValue )
{
	if( m_properties.find( propertyName ) != m_properties.end() )
	{
		std::map< std::string, NamedPropertiesBase* >::iterator mapIter = m_properties.find( propertyName );
		delete mapIter->second;
		m_properties.erase( mapIter );
	}

	TypeNamedProperties< T_PropertyDataType >* propertyValue = new TypeNamedProperties< T_PropertyDataType >;
	propertyValue->m_data = typedDataValue;
	m_properties[ propertyName ] = propertyValue;
}


//-----------------------------------------------------------------------------------------------
template< typename T_PropertyDataType >
inline PropertyGetResult NamedProperties::GetProperty( const std::string& propertyName, T_PropertyDataType& typedData_out ) const
{
	std::map< std::string, NamedPropertiesBase* > tempProperties = m_properties;

	std::map< std::string, NamedPropertiesBase* >::iterator mapIter = tempProperties.find( propertyName );
	if( mapIter == tempProperties.end() )
	{
		return PROPERTY_GET_FAILED_NOT_FOUND;
	}

	if( mapIter->second == nullptr )
	{
		return PROPERTY_GET_FAILED_PROPERTY_WAS_EMPTY;
	}

	TypeNamedProperties< T_PropertyDataType >* typePropertiesPtr = dynamic_cast< TypeNamedProperties< T_PropertyDataType >* >( mapIter->second );
	if( typePropertiesPtr == nullptr )
	{
		return PROPERTY_GET_FAILED_TYPE_MISMATCH;
	}

	typedData_out = typePropertiesPtr->m_data;
	return PROPERTY_GET_SUCCESS;
}


#endif // include_NamedProperties