#ifndef include_ConsoleLogLine
#define include_ConsoleLogLine
#pragma once

//-----------------------------------------------------------------------------------------------
#include <string>
#include "Color.hpp"


//-----------------------------------------------------------------------------------------------
class ConsoleLogLine
{
public:
	ConsoleLogLine() {}
	ConsoleLogLine( const std::string& text, const Color& color ) : m_text( text ), m_color( color ) {}

	std::string		m_text;
	Color			m_color;
};


#endif // include_ConsoleLogLine