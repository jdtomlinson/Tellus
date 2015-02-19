#include "BitmapFont.hpp"
#include "XMLDocument.hpp"
#include "XMLParsingFunctions.hpp"


//-----------------------------------------------------------------------------------------------
BitmapFont::BitmapFont( const std::string& glyphSheetFileName, const std::string& xmlMetaDataFileName )
{
	m_glyphSheet = Texture::CreateOrGetTexture( glyphSheetFileName );

	XMLDocument fontInfo( xmlMetaDataFileName );
	fontInfo.SetCurrentNodeToChild( "FontDefinition" );
	fontInfo.SetCurrentNodeToChild( "FontInfo" );
	m_fontName = GetStringXMLAttribute( fontInfo, "name", "null" );

	while( !fontInfo.GetCurrentNode().IsNull() )
	{
		fontInfo.SetCurrentNodeToNextSibling();

		unsigned int ucsIndex = GetUnsignedIntXMLAttribute( fontInfo, "ucsIndex", 0 );
		unsigned int sheetNumber = GetUnsignedIntXMLAttribute( fontInfo, "sheet", 0 );
		float ttfA = GetFloatXMLAttribute( fontInfo, "ttfA", 0.f );
		float ttfB = GetFloatXMLAttribute( fontInfo, "ttfB", 0.f );
		float ttfC = GetFloatXMLAttribute( fontInfo, "ttfC", 0.f );

		Vector2 texCoordMins = GetVector2XMLAttribute( fontInfo, "texCoordMins", Vector2( 0.f, 0.f ) );
		Vector2 texCoordMaxs = GetVector2XMLAttribute( fontInfo, "texCoordMaxs", Vector2( 0.f, 0.f ) );

		m_glyphData[ ucsIndex ] = Glyph( ucsIndex, sheetNumber, texCoordMins, texCoordMaxs, ttfA, ttfB, ttfC );
	}
}