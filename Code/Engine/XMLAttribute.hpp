#ifndef include_XMLAttribute
#define include_XMLAttribute
#pragma once

//-----------------------------------------------------------------------------------------------
#include "pugixml.hpp"


//-----------------------------------------------------------------------------------------------
class XMLAttribute
{
public:
	XMLAttribute() {}
	XMLAttribute( const pugi::xml_attribute& attribute ) : m_attribute( attribute ) {}
	void SetAttribute( const pugi::xml_attribute& attribute ) { m_attribute = attribute; }
	std::string GetAttributeName() { return m_attribute.name(); }
	bool GetAttributeAsBool() { return m_attribute.as_bool(); }
	double GetAttributeAsDouble() { return m_attribute.as_double(); }
	float GetAttributeAsFloat() { return m_attribute.as_float(); }
	int GetAttributeAsInt() { return m_attribute.as_int(); }
	std::string GetAttributeAsString() { return m_attribute.as_string(); }
	unsigned int GetAttributeAsUnsignedInt() { return m_attribute.as_uint(); }
	bool IsEmpty() { return m_attribute == nullptr; }

private:
	pugi::xml_attribute m_attribute;
};


#endif // include_XMLAttribute