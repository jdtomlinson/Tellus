#ifndef include_TextBox
#define include_TextBox
#pragma once

//-----------------------------------------------------------------------------------------------
#include <string>
#include "Color.hpp"
#include "Widget.hpp"
#include "BitmapFont.hpp"


//-----------------------------------------------------------------------------------------------
const float TEXT_BOX_DEFAULT_BORDER_WIDTH = 3.f;
const Color TEXT_BOX_DEFAULT_BORDER_COLOR = Color::Black;
const Color TEXT_BOX_DEFAULT_BACKGROUND_COLOR = Color::White;
const Color TEXT_BOX_DEFAULT_FONT_COLOR = Color::Black;
const std::string TEXT_BOX_DEFAULT_FONT_GLYPH_SHEET_FILE_NAME = "Data/Fonts/MainFont_EN_00.png";
const std::string TEXT_BOX_DEFAULT_FONT_META_DATA_FILE_NAME = "Data/Fonts/MainFont_EN.FontDef.xml";


//-----------------------------------------------------------------------------------------------
class TextBox : public Widget
{
public:
	TextBox() {}
	TextBox( const Vector2& bottomLeftPosition, float width, float height );
	TextBox( const Vector2& bottomLeftPosition, float width, float height, const std::string& initText );
	void SetRestrictedCharacters( const std::string& restrictedCharacters );
	void SetBitmapFont( const BitmapFont& font );
	void SetFontHeight( float fontHeightPixels );
	std::string GetText() const;
	void SetText( const std::string& text );

private:
	void AllowAllCharInTextBox();
	void AllowNoCharInTextBox();
	void CheckForCharAdd( const Keyboard& keyboard );
	void CheckForCharDelete( const Keyboard& keyboard );
	void Update( float deltaSeconds, const Mouse& mouse, const Keyboard& keyboard );
	void RenderCursor();
	void Render();

	BitmapFont		m_font;
	std::string		m_text;
	bool			m_drawCursor;
	float			m_secondsSinceCursorRenderToggle;
	float			m_fontHeightPixels;
	float			m_borderWidth;
	Color			m_borderColor;
	Color			m_backgroundColor;
	Color			m_fontColor;
	bool			m_restrictedChar[ NUM_KEYBOARD_CHARS ];
};


#endif // include_TextBox