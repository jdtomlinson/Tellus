#ifndef include_XMLParsingFunctions
#define include_XMLParsingFunctions
#pragma once

//-----------------------------------------------------------------------------------------------
#include <vector>
#include <windows.h>
#include "XMLNode.hpp"
#include "XMLAttribute.hpp"
#include "XMLDocument.hpp"
#include "Color.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "IntVector2.hpp"
#include "IntVector3.hpp"
#include "StringFunctions.hpp"


//-----------------------------------------------------------------------------------------------
inline int GetIntXMLAttribute( const XMLDocument& xmlDoc, const std::string& attributeName, int defaultValueIfNotFound )
{
	XMLAttribute attribute = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName );
	if( attribute.IsEmpty() )
		return defaultValueIfNotFound;

	return attribute.GetAttributeAsInt();
}


//-----------------------------------------------------------------------------------------------
inline unsigned int GetUnsignedIntXMLAttribute( const XMLDocument& xmlDoc, const std::string& attributeName, unsigned int defaultValueIfNotFound )
{
	XMLAttribute attribute = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName );
	if( attribute.IsEmpty() )
		return defaultValueIfNotFound;

	return attribute.GetAttributeAsUnsignedInt();
}


//-----------------------------------------------------------------------------------------------
inline float GetFloatXMLAttribute( const XMLDocument& xmlDoc, const std::string& attributeName, float defaultValueIfNotFound )
{
	XMLAttribute attribute = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName );
	if( attribute.IsEmpty() )
		return defaultValueIfNotFound;

	return attribute.GetAttributeAsFloat();
}


//-----------------------------------------------------------------------------------------------
inline double GetDoubleXMLAttribute( const XMLDocument& xmlDoc, const std::string& attributeName, double defaultValueIfNotFound )
{
	XMLAttribute attribute = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName );
	if( attribute.IsEmpty() )
		return defaultValueIfNotFound;

	return attribute.GetAttributeAsDouble();
}


//-----------------------------------------------------------------------------------------------
inline bool GetBoolXMLAttribute( const XMLDocument& xmlDoc, const std::string& attributeName, bool defaultValueIfNotFound )
{
	XMLAttribute attribute = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName );
	if( attribute.IsEmpty() )
		return defaultValueIfNotFound;

	return attribute.GetAttributeAsBool();
}


//-----------------------------------------------------------------------------------------------
inline char GetCharXMLAttribute( const XMLDocument& xmlDoc, const std::string& attributeName, char defaultValueIfNotFound )
{
	XMLAttribute attribute = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName );
	if( attribute.IsEmpty() )
		return defaultValueIfNotFound;

	std::string charAsString = attribute.GetAttributeAsString();
	if( charAsString.size() != 1 )
		return defaultValueIfNotFound;

	return charAsString[0];
}


//-----------------------------------------------------------------------------------------------
inline std::string GetStringXMLAttribute( const XMLDocument& xmlDoc, const std::string& attributeName, const std::string& defaultValueIfNotFound )
{
	XMLAttribute attribute = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName );
	if( attribute.IsEmpty() )
		return defaultValueIfNotFound;

	return attribute.GetAttributeAsString();
}


//-----------------------------------------------------------------------------------------------
inline Color GetColorXMLAttribute( const XMLDocument& xmlDoc, const std::string& attributeName, const Color& defaultValueIfNotFound )
{
	XMLAttribute attribute = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName );
	if( attribute.IsEmpty() )
		return defaultValueIfNotFound;

	std::string attributeValueAsString = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName ).GetAttributeAsString();

	std::vector<std::string> floatsAsStringsVector = GetVectorOfStringsFromSingleString( GetStringWithNoWhitespace( attributeValueAsString ), ',' );
	std::vector<float> attributeValues;
	for( unsigned int floatIndex = 0; floatIndex < floatsAsStringsVector.size(); ++floatIndex )
	{
		float floatValue = (float) atof( floatsAsStringsVector[ floatIndex ].c_str() );
		attributeValues.push_back( floatValue );
	}

	if( attributeValues.size() == 3 )
		return Color( attributeValues[0], attributeValues[1], attributeValues[2] );

	if( attributeValues.size() == 4 )
		return Color( attributeValues[0], attributeValues[1], attributeValues[2], attributeValues[3] );

	return defaultValueIfNotFound;
}


//-----------------------------------------------------------------------------------------------
inline Vector2 GetVector2XMLAttribute( const XMLDocument& xmlDoc, const std::string& attributeName, const Vector2& defaultValueIfNotFound )
{
	XMLAttribute attribute = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName );
	if( attribute.IsEmpty() )
		return defaultValueIfNotFound;

	std::string attributeValueAsString = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName ).GetAttributeAsString();

	std::vector<std::string> floatsAsStringsVector = GetVectorOfStringsFromSingleString( GetStringWithNoWhitespace( attributeValueAsString ), ',' );
	std::vector<float> attributeValues;
	for( unsigned int floatIndex = 0; floatIndex < floatsAsStringsVector.size(); ++floatIndex )
	{
		float floatValue = (float) atof( floatsAsStringsVector[ floatIndex ].c_str() );
		attributeValues.push_back( floatValue );
	}

	if( attributeValues.size() == 2 )
		return Vector2( attributeValues[0], attributeValues[1] );

	return defaultValueIfNotFound;
}


//-----------------------------------------------------------------------------------------------
inline Vector3 GetVector3XMLAttribute( const XMLDocument& xmlDoc, const std::string& attributeName, const Vector3& defaultValueIfNotFound )
{
	XMLAttribute attribute = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName );
	if( attribute.IsEmpty() )
		return defaultValueIfNotFound;

	std::string attributeValueAsString = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName ).GetAttributeAsString();

	std::vector<std::string> floatsAsStringsVector = GetVectorOfStringsFromSingleString( GetStringWithNoWhitespace( attributeValueAsString ), ',' );
	std::vector<float> attributeValues;
	for( unsigned int floatIndex = 0; floatIndex < floatsAsStringsVector.size(); ++floatIndex )
	{
		float floatValue = (float) atof( floatsAsStringsVector[ floatIndex ].c_str() );
		attributeValues.push_back( floatValue );
	}

	if( attributeValues.size() == 3 )
		return Vector3( attributeValues[0], attributeValues[1], attributeValues[2] );

	return defaultValueIfNotFound;
}


//-----------------------------------------------------------------------------------------------
inline Vector4 GetVector4XMLAttribute( const XMLDocument& xmlDoc, const std::string& attributeName, const Vector4& defaultValueIfNotFound )
{
	XMLAttribute attribute = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName );
	if( attribute.IsEmpty() )
		return defaultValueIfNotFound;

	std::string attributeValueAsString = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName ).GetAttributeAsString();

	std::vector<std::string> floatsAsStringsVector = GetVectorOfStringsFromSingleString( GetStringWithNoWhitespace( attributeValueAsString ), ',' );
	std::vector<float> attributeValues;
	for( unsigned int floatIndex = 0; floatIndex < floatsAsStringsVector.size(); ++floatIndex )
	{
		float floatValue = (float) atof( floatsAsStringsVector[ floatIndex ].c_str() );
		attributeValues.push_back( floatValue );
	}

	if( attributeValues.size() == 4 )
		return Vector4( attributeValues[0], attributeValues[1], attributeValues[2], attributeValues[3] );

	return defaultValueIfNotFound;
}


//-----------------------------------------------------------------------------------------------
inline IntVector2 GetIntVector2XMLAttribute( const XMLDocument& xmlDoc, const std::string& attributeName, const IntVector2& defaultValueIfNotFound )
{
	XMLAttribute attribute = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName );
	if( attribute.IsEmpty() )
		return defaultValueIfNotFound;

	std::string attributeValueAsString = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName ).GetAttributeAsString();

	std::vector<std::string> intsAsStringsVector = GetVectorOfStringsFromSingleString( GetStringWithNoWhitespace( attributeValueAsString ), ',' );
	std::vector<int> attributeValues;
	for( unsigned int intIndex = 0; intIndex < intsAsStringsVector.size(); ++intIndex )
	{
		int intValue = atoi( intsAsStringsVector[ intIndex ].c_str() );
		attributeValues.push_back( intValue );
	}

	if( attributeValues.size() == 2 )
		return IntVector2( attributeValues[0], attributeValues[1] );

	return defaultValueIfNotFound;
}


//-----------------------------------------------------------------------------------------------
inline IntVector3 GetIntVector3XMLAttribute( const XMLDocument& xmlDoc, const std::string& attributeName, const IntVector3& defaultValueIfNotFound )
{
	XMLAttribute attribute = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName );
	if( attribute.IsEmpty() )
		return defaultValueIfNotFound;

	std::string attributeValueAsString = xmlDoc.GetCurrentNode().GetAttributeByName( attributeName ).GetAttributeAsString();

	std::vector<std::string> intsAsStringsVector = GetVectorOfStringsFromSingleString( GetStringWithNoWhitespace( attributeValueAsString ), ',' );
	std::vector<int> attributeValues;
	for( unsigned int intIndex = 0; intIndex < intsAsStringsVector.size(); ++intIndex )
	{
		int intValue = atoi( intsAsStringsVector[ intIndex ].c_str() );
		attributeValues.push_back( intValue );
	}

	if( attributeValues.size() == 3 )
		return IntVector3( attributeValues[0], attributeValues[1], attributeValues[2] );

	return defaultValueIfNotFound;
}


//-----------------------------------------------------------------------------------------------
inline void ValidateXMLAttributes( const XMLDocument& xmlDoc, const std::string& requiredAttributeNames, const std::string& optionalAttributeNames )
{
	XMLNode xmlNode = xmlDoc.GetCurrentNode();

	std::vector<std::string> requiredAttributes = GetVectorOfStringsFromSingleString( GetStringWithNoWhitespace( requiredAttributeNames ), ',' );
	std::vector<std::string> optionalAttributes = GetVectorOfStringsFromSingleString( GetStringWithNoWhitespace( optionalAttributeNames ), ',' );
	std::vector<XMLAttribute> attributeList = xmlNode.GetAllAttributes();

	for( unsigned int attribIndex = 0; attribIndex < attributeList.size(); ++attribIndex )
	{
		bool foundAttribute = false;
		XMLAttribute attribute = attributeList[ attribIndex ];
		std::string attribName = attribute.GetAttributeName();

		std::vector<std::string>::iterator vectorIter = find( requiredAttributes.begin(), requiredAttributes.end(), attribName );
		if( vectorIter != requiredAttributes.end() )
		{
			foundAttribute = true;
			requiredAttributes.erase( vectorIter );
		}

		vectorIter = find( optionalAttributes.begin(), optionalAttributes.end(), attribName );
		if( vectorIter != optionalAttributes.end() )
		{
			foundAttribute = true;
		}

		if( !foundAttribute )
		{
			std::vector<std::string> lowercaseRequiredAttributes = GetVectorOfStringsFromSingleString( GetStringWithNoWhitespace( requiredAttributeNames ), ',' );
			std::vector<std::string> lowercaseOptionalAttributes = GetVectorOfStringsFromSingleString( GetStringWithNoWhitespace( optionalAttributeNames ), ',' );
			std::vector<std::string>::iterator requiredIter = find( lowercaseRequiredAttributes.begin(), lowercaseRequiredAttributes.end(), GetLowercaseString( attribName ) );
			std::vector<std::string>::iterator optionalIter = find( lowercaseOptionalAttributes.begin(), lowercaseOptionalAttributes.end(), GetLowercaseString( attribName ) );
			
			if( requiredIter != lowercaseRequiredAttributes.end() || optionalIter != lowercaseOptionalAttributes.end() )
			{
				std::string messageWindowText = "CASE MISMATCH ERROR\n\n";

				messageWindowText += "The attribute \'" + attribName + "\' in element \'" + xmlNode.GetNodeName() + "\' is not properly cased" + "\n\n";
				messageWindowText += "File Error Occurs: " + GetShortenedFileName( xmlDoc.GetFileName() ) + "\n\n";

				if( requiredIter != lowercaseRequiredAttributes.end() )
				{
					int requiredAttribIndex = requiredIter - lowercaseRequiredAttributes.begin();
					messageWindowText += "Correct Casing of Attribute: " + requiredAttributes[ requiredAttribIndex ];
				}
				else
				{
					int optionalAttribIndex = optionalIter - lowercaseOptionalAttributes.begin();
					messageWindowText += "Correct Casing of Attribute: " + optionalAttributes[ optionalAttribIndex ];
				}

				messageWindowText += "\n\nThe program will now close";

				ShowCursor( TRUE );
				MessageBoxA( 0, messageWindowText.c_str(), "Case Mismatch", MB_OK );
				std::exit( EXIT_FAILURE );
			}
			else
			{
				std::string messageWindowText = "GIVEN ATTRIBUTE IS NOT ALLOWED\n\n";

				messageWindowText += "The attribute \'" + attribName + "\' is not an allowed attribute of element \'" + xmlNode.GetNodeName() + "\'\n\n";
				messageWindowText += "File Error Occurs: " + GetShortenedFileName( xmlDoc.GetFileName() ) + "\n\n";

				messageWindowText += "Required Attributes: " + requiredAttributeNames;
				if( requiredAttributeNames == "" )
					messageWindowText += "<none>";

				messageWindowText += "\n\nOptional Attributes: " + optionalAttributeNames;
				if( optionalAttributeNames == "" )
					messageWindowText += "<none>";

				messageWindowText += "\n\nThe program will now close";

				ShowCursor( TRUE );
				MessageBoxA( 0, messageWindowText.c_str(), "Illegal Attribute", MB_OK );
				std::exit( EXIT_FAILURE );
			}
		}
	}

	if( requiredAttributes.size() != 0 )
	{
		std::string messageWindowText = "MISSING REQUIRED ATTRIBUTE(S)\n\n";

		messageWindowText += "The following required attribute(s) were not found in the element \'" + xmlNode.GetNodeName() + "\': ";

		for( unsigned int attribIndex = 0; attribIndex < requiredAttributes.size(); ++attribIndex )
		{
			messageWindowText += requiredAttributes[ attribIndex ];
			if( attribIndex < requiredAttributes.size() - 1 )
				messageWindowText += ", ";
		}

		messageWindowText += "\n\nFile Error(s) Occur: " + GetShortenedFileName( xmlDoc.GetFileName() ) + "\n\n";

		messageWindowText += "Required Attributes: " + requiredAttributeNames;
		if( requiredAttributeNames == "" )
			messageWindowText += "<none>";

		messageWindowText += "\n\nOptional Attributes: " + optionalAttributeNames;
		if( optionalAttributeNames == "" )
			messageWindowText += "<none>";

		messageWindowText += "\n\nThe program will now close";

		ShowCursor( TRUE );
		MessageBoxA( 0, messageWindowText.c_str(), "Required Attribute(s) Missing", MB_OK );
		std::exit( EXIT_FAILURE );
	}
}


//-----------------------------------------------------------------------------------------------
inline void ValidateXMLChildElements( const XMLDocument& xmlDoc, const std::string& requiredChildElementNames, const std::string& optionalChildElementNames )
{
	XMLNode xmlNode = xmlDoc.GetCurrentNode();

	std::vector<std::string> requiredChildElements = GetVectorOfStringsFromSingleString( GetStringWithNoWhitespace( requiredChildElementNames ), ',' );
	std::vector<std::string> remainingRequiredChildElements = requiredChildElements;
	std::vector<std::string> optionalChildElements = GetVectorOfStringsFromSingleString( GetStringWithNoWhitespace( optionalChildElementNames ), ',' );
	std::vector<XMLNode> childList = xmlNode.GetAllChildren();

	for( unsigned int childIndex = 0; childIndex < childList.size(); ++childIndex )
	{
		bool foundChild = false;
		XMLNode child = childList[ childIndex ];
		std::string childName = child.GetNodeName();

		std::vector<std::string>::iterator vectorIter = find( requiredChildElements.begin(), requiredChildElements.end(), childName );
		if( vectorIter != requiredChildElements.end() )
		{
			foundChild = true;
			vectorIter = find( remainingRequiredChildElements.begin(), remainingRequiredChildElements.end(), childName );
			if( vectorIter != remainingRequiredChildElements.end() )
				remainingRequiredChildElements.erase( vectorIter );
		}

		vectorIter = find( optionalChildElements.begin(), optionalChildElements.end(), childName );
		if( vectorIter != optionalChildElements.end() )
		{
			foundChild = true;
		}

		if( !foundChild )
		{
			std::vector<std::string> lowercaseRequiredChildElements = GetVectorOfStringsFromSingleString( GetStringWithNoWhitespace( requiredChildElementNames ), ',' );
			std::vector<std::string> lowercaseOptionalChildElements = GetVectorOfStringsFromSingleString( GetStringWithNoWhitespace( optionalChildElementNames ), ',' );
			std::vector<std::string>::iterator requiredIter = find( lowercaseRequiredChildElements.begin(), lowercaseRequiredChildElements.end(), GetLowercaseString( childName ) );
			std::vector<std::string>::iterator optionalIter = find( lowercaseOptionalChildElements.begin(), lowercaseOptionalChildElements.end(), GetLowercaseString( childName ) );

			if( requiredIter != lowercaseRequiredChildElements.end() || optionalIter != lowercaseOptionalChildElements.end() )
			{
				std::string messageWindowText = "CASE MISMATCH ERROR\n\n";

				messageWindowText += "The child element \'" + childName + "\' in element \'" + xmlNode.GetNodeName() + "\' is not properly cased" + "\n\n";
				messageWindowText += "File Error Occurs: " + GetShortenedFileName( xmlDoc.GetFileName() ) + "\n\n";

				if( requiredIter != lowercaseRequiredChildElements.end() )
				{
					int requiredChildIndex = requiredIter - lowercaseRequiredChildElements.begin();
					messageWindowText += "Correct Casing of Child Element: " + requiredChildElements[ requiredChildIndex ];
				}
				else
				{
					int optionalChildIndex = optionalIter - lowercaseOptionalChildElements.begin();
					messageWindowText += "Correct Casing of Child Element: " + optionalChildElements[ optionalChildIndex ];
				}

				messageWindowText += "\n\nThe program will now close";

				ShowCursor( TRUE );
				MessageBoxA( 0, messageWindowText.c_str(), "Case Mismatch", MB_OK );
				std::exit( EXIT_FAILURE );
			}
			else
			{
				std::string messageWindowText = "GIVEN CHILD ELEMENT IS NOT ALLOWED\n\n";

				messageWindowText += "The child element \'" + childName + "\' is not an allowed child element of element \'" + xmlNode.GetNodeName() + "\'\n\n";

				messageWindowText += "Required Child Elements: " + requiredChildElementNames;
				if( requiredChildElementNames == "" )
					messageWindowText += "<none>";

				messageWindowText += "\n\nFile Error Occurs: " + GetShortenedFileName( xmlDoc.GetFileName() ) + "\n\n";

				messageWindowText += "Optional Child Elements: " + optionalChildElementNames;
				if( optionalChildElementNames == "" )
					messageWindowText += "<none>";

				messageWindowText += "\n\nThe program will now close";

				ShowCursor( TRUE );
				MessageBoxA( 0, messageWindowText.c_str(), "Illegal Child Element", MB_OK );
				std::exit( EXIT_FAILURE );
			}
		}
	}

	if( remainingRequiredChildElements.size() != 0 )
	{
		std::string messageWindowText = "MISSING REQUIRED CHILD ELEMENT(S)\n\n";

		messageWindowText += "The following required child element(s) were not found in the element \'" + xmlNode.GetNodeName() + "\': ";

		for( unsigned int childIndex = 0; childIndex < remainingRequiredChildElements.size(); ++childIndex )
		{
			messageWindowText += remainingRequiredChildElements[ childIndex ];
			if( childIndex < remainingRequiredChildElements.size() - 1 )
				messageWindowText += ", ";
		}

		messageWindowText += "\n\nFile Error(s) Occur: " + GetShortenedFileName( xmlDoc.GetFileName() ) + "\n\n";

		messageWindowText += "Required Child Elements: " + requiredChildElementNames;
		if( requiredChildElementNames == "" )
			messageWindowText += "<none>";

		messageWindowText += "\n\nOptional Child Elements: " + optionalChildElementNames;
		if( optionalChildElementNames == "" )
			messageWindowText += "<none>";

		messageWindowText += "\n\nThe program will now close";

		ShowCursor( TRUE );
		MessageBoxA( 0, messageWindowText.c_str(), "Required Child Element(s) Missing", MB_OK );
		std::exit( EXIT_FAILURE );
	}
}


#endif // include_XMLParsingFunctions