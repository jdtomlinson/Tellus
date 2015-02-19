#ifndef include_BitmapFont
#define include_BitmapFont
#pragma once

//-----------------------------------------------------------------------------------------------
#include "Glyph.hpp"
#include "pugixml.hpp"
#include "Texture.hpp"
#include "EngineCommon.hpp"


//-----------------------------------------------------------------------------------------------
class BitmapFont
{
public:
	BitmapFont() {}
	BitmapFont( const std::string& glyphSheetFileName, const std::string& xmlMetaDataFileName );

	Texture*		m_glyphSheet;
	Glyph			m_glyphData[ NUM_VIRTUAL_KEYS ];
	std::string		m_fontName;
};


#endif // include_BitmapFont