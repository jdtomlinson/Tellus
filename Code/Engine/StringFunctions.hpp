#ifndef include_StringFunctions
#define include_StringFunctions
#pragma once

//-----------------------------------------------------------------------------------------------
#include <vector>
#include <sstream>
#include <algorithm>


//-----------------------------------------------------------------------------------------------
inline std::string GetStringWithNoWhitespace( const std::string& str )
{
	std::string returnString = str;
	returnString.erase( std::remove( returnString.begin(), returnString.end(), ' ' ), returnString.end() );
	return returnString;
}


//-----------------------------------------------------------------------------------------------
inline std::string GetLowercaseString( const std::string& str )
{
	std::string returnString = str;
	for( unsigned int charIndex = 0; charIndex < returnString.size(); ++charIndex )
	{
		if( returnString[ charIndex ] >= 'A' && returnString[ charIndex ] <= 'Z' )
		{
			returnString[ charIndex ] -= ( 'A' - 'a' );
		}
	}

	return returnString;
}


//-----------------------------------------------------------------------------------------------
inline std::string GetUppercaseString( const std::string& str )
{
	std::string returnString = str;
	for( unsigned int charIndex = 0; charIndex < returnString.size(); ++charIndex )
	{
		if( returnString[ charIndex ] >= 'a' && returnString[ charIndex ] <= 'z' )
		{
			returnString[ charIndex ] += ( 'A' - 'a' );
		}
	}

	return returnString;
}


//-----------------------------------------------------------------------------------------------
inline std::string ConvertNumberToString( int number )
{
	return static_cast< std::ostringstream* >( &( std::ostringstream() << number ) )->str();
}


//-----------------------------------------------------------------------------------------------
inline std::string ConvertNumberToString( float number )
{
	return static_cast< std::ostringstream* >( &( std::ostringstream() << number ) )->str();
}


//-----------------------------------------------------------------------------------------------
inline std::vector<std::string> GetVectorOfStringsFromSingleString( const std::string& listString, const char separatorChar )
{
	std::string stringObject = "";
	std::vector<std::string> stringVector;

	for( unsigned int charIndex = 0; charIndex < listString.size(); ++charIndex )
	{
		if( listString[ charIndex ] == separatorChar )
		{
			stringVector.push_back( stringObject );
			stringObject = "";
		}
		else
		{
			stringObject += listString[ charIndex ];
		}
	}

	if( stringObject != "" )
	{
		stringVector.push_back( stringObject );
	}

	return stringVector;
}


//-----------------------------------------------------------------------------------------------
inline std::string GetShortenedFileName( const std::string& fileName )
{
	unsigned int lastSlashPoition = fileName.find_last_of( "/" );
	if( lastSlashPoition == std::string::npos )
		return "";

	return fileName.substr( lastSlashPoition + 1 );
}


#endif // include_StringFunctions