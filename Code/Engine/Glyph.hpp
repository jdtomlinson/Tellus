#ifndef include_Glyph
#define include_Glyph
#pragma once

//-----------------------------------------------------------------------------------------------
#include "Vector2.hpp"


//-----------------------------------------------------------------------------------------------
class Glyph
{
public:
	Glyph() {}
	Glyph( unsigned int ucsIndex, unsigned int sheetNumber, const Vector2& texCoordMins, const Vector2& texCoordMaxs, float ttfA, float ttfB, float ttfC );

	unsigned int	m_ucsIndex;
	unsigned int	m_sheetNumber;
	Vector2			m_texCoordMins;
	Vector2			m_texCoordMaxs;
	float			m_ttfA;
	float			m_ttfB;
	float			m_ttfC;
};


//-----------------------------------------------------------------------------------------------
inline Glyph::Glyph( unsigned int ucsIndex, unsigned int sheetNumber, const Vector2& texCoordMins, const Vector2& texCoordMaxs, float ttfA, float ttfB, float ttfC )
	: m_ucsIndex( ucsIndex )
	, m_sheetNumber( sheetNumber )
	, m_texCoordMins( texCoordMins )
	, m_texCoordMaxs( texCoordMaxs )
	, m_ttfA( ttfA )
	, m_ttfB( ttfB )
	, m_ttfC( ttfC )
{

}


#endif // include_Glyph