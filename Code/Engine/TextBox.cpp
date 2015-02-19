#include "TextBox.hpp"
#include "OpenGLRenderer.hpp"


//-----------------------------------------------------------------------------------------------
TextBox::TextBox( const Vector2& bottomLeftPosition, float width, float height )
	: m_text( "" )
	, m_drawCursor( false )
	, m_secondsSinceCursorRenderToggle( 0.f )
	, m_fontHeightPixels( height )
	, m_borderWidth( TEXT_BOX_DEFAULT_BORDER_WIDTH )
	, m_borderColor( TEXT_BOX_DEFAULT_BORDER_COLOR )
	, m_backgroundColor( TEXT_BOX_DEFAULT_BACKGROUND_COLOR )
	, m_fontColor( TEXT_BOX_DEFAULT_FONT_COLOR )
	, m_font( TEXT_BOX_DEFAULT_FONT_GLYPH_SHEET_FILE_NAME, TEXT_BOX_DEFAULT_FONT_META_DATA_FILE_NAME )
{
	m_screenPositionBottomLeft = bottomLeftPosition;
	m_widthPixels = width;
	m_heightPixels = height;
	AllowAllCharInTextBox();
}


//-----------------------------------------------------------------------------------------------
TextBox::TextBox( const Vector2& bottomLeftPosition, float width, float height, const std::string& initText )
	: m_text( initText )
	, m_drawCursor( false )
	, m_secondsSinceCursorRenderToggle( 0.f )
	, m_fontHeightPixels( height )
	, m_borderWidth( TEXT_BOX_DEFAULT_BORDER_WIDTH )
	, m_borderColor( TEXT_BOX_DEFAULT_BORDER_COLOR )
	, m_backgroundColor( TEXT_BOX_DEFAULT_BACKGROUND_COLOR )
	, m_fontColor( TEXT_BOX_DEFAULT_FONT_COLOR )
	, m_font( TEXT_BOX_DEFAULT_FONT_GLYPH_SHEET_FILE_NAME, TEXT_BOX_DEFAULT_FONT_META_DATA_FILE_NAME )
{
	m_screenPositionBottomLeft = bottomLeftPosition;
	m_widthPixels = width;
	m_heightPixels = height;
	AllowAllCharInTextBox();
}


//-----------------------------------------------------------------------------------------------
void TextBox::SetRestrictedCharacters( const std::string& restrictedCharacters )
{
	AllowNoCharInTextBox();

	bool allowChar = true;
	for( unsigned int charIndex = 0; charIndex < restrictedCharacters.size(); ++charIndex )
	{
		unsigned char restrictedChar = restrictedCharacters[ charIndex ];

		if( restrictedChar != '-' && restrictedChar != '^' && restrictedChar != '\\' )
		{
			m_restrictedChar[ restrictedChar ] = allowChar;
			continue;
		}

		if( restrictedChar == '^' )
		{
			allowChar = !allowChar;
		}
		else if( restrictedChar == '-' )
		{
			if( charIndex > 0 && charIndex < restrictedCharacters.size() - 1 )
			{
				unsigned char firstChar = restrictedCharacters[ charIndex - 1 ];
				unsigned char lastChar = restrictedCharacters[ charIndex + 1 ];

				for( unsigned char rangedCharIndex = firstChar; rangedCharIndex <= lastChar; ++rangedCharIndex )
				{
					m_restrictedChar[ rangedCharIndex ] = allowChar;
				}
			}
		}
		else if( restrictedChar == '\\' )
		{
			if( charIndex < restrictedCharacters.size() - 1 )
			{
				unsigned char nextRestrictedChar = restrictedCharacters[ charIndex + 1 ];
				if( nextRestrictedChar == '-' || nextRestrictedChar == '^' || nextRestrictedChar == '\\' )
				{
					m_restrictedChar[ nextRestrictedChar ] = allowChar;
					++charIndex;
				}
			}

			continue;
		}
	}
}


//-----------------------------------------------------------------------------------------------
void TextBox::SetBitmapFont( const BitmapFont& font )
{
	m_font = font;
}


//-----------------------------------------------------------------------------------------------
void TextBox::SetFontHeight( float fontHeightPixels )
{
	m_fontHeightPixels = fontHeightPixels;
}


//-----------------------------------------------------------------------------------------------
std::string TextBox::GetText() const
{
	return m_text;
}


//-----------------------------------------------------------------------------------------------
void TextBox::SetText( const std::string& text )
{
	m_text = text;
}


//-----------------------------------------------------------------------------------------------
void TextBox::AllowAllCharInTextBox()
{
	for( unsigned int charIndex = 0; charIndex < NUM_KEYBOARD_CHARS; ++charIndex )
	{
		m_restrictedChar[ charIndex ] = true;
	}
}


//-----------------------------------------------------------------------------------------------
void TextBox::AllowNoCharInTextBox()
{
	for( unsigned int charIndex = 0; charIndex < NUM_KEYBOARD_CHARS; ++charIndex )
	{
		m_restrictedChar[ charIndex ] = false;
	}
}


//-----------------------------------------------------------------------------------------------
void TextBox::CheckForCharAdd( const Keyboard& keyboard )
{
	for( unsigned int charIndex = CHAR_VALUES_START; charIndex < NUM_KEYBOARD_CHARS; ++charIndex )
	{
		unsigned char checkChar = (unsigned char) charIndex;
		if( keyboard.IsCharPressedDown( checkChar ) && m_restrictedChar[ charIndex ] )
		{
			std::string tentativeText = m_text;
			tentativeText.push_back( checkChar );
			float tentativeTextWidth = OpenGLRenderer::CalcTextWidth( tentativeText, m_font, m_fontHeightPixels );
			if( tentativeTextWidth < m_widthPixels )
				m_text = tentativeText;

			return;
		}
	}
}


//-----------------------------------------------------------------------------------------------
void TextBox::CheckForCharDelete( const Keyboard& keyboard )
{
	if( keyboard.IsKeyPressedDownAndWasNotBefore( KEY_BACK ) || keyboard.IsKeyPressedDownAndWasNotBefore( KEY_DELETE ) || keyboard.IsCharPressedDown( 0x08 ) )
	{
		if( m_text.size() > 0 )
		{
			m_text.pop_back();
		}
	}
}


//-----------------------------------------------------------------------------------------------
void TextBox::Update( float deltaSeconds, const Mouse& mouse, const Keyboard& keyboard )
{
	Widget::Update( deltaSeconds, mouse, keyboard );

	if( !m_isInFocus )
		return;

	m_secondsSinceCursorRenderToggle += deltaSeconds;
	if( m_secondsSinceCursorRenderToggle > 0.75f )
	{
		m_secondsSinceCursorRenderToggle -= 0.75f;
		m_drawCursor = !m_drawCursor;
	}

	CheckForCharAdd( keyboard );
	CheckForCharDelete( keyboard );
}


//-----------------------------------------------------------------------------------------------
void TextBox::RenderCursor()
{
	if( !m_drawCursor || !m_isInFocus )
		return;

	float cursorPositionX = OpenGLRenderer::CalcTextWidth( m_text, m_font, m_fontHeightPixels ) + m_screenPositionBottomLeft.x + 4.f;
	float cursorBottomPositionY = m_screenPositionBottomLeft.y + m_fontHeightPixels * 0.1f;

	OpenGLRenderer::DisableTexture2D();
	OpenGLRenderer::SetLineWidth( 1.f );
	OpenGLRenderer::SetColor4f( 0.f, 0.f, 0.f, 1.f );
	OpenGLRenderer::BeginRender( LINES );
	{
		OpenGLRenderer::SetVertex2f( cursorPositionX, cursorBottomPositionY );
		OpenGLRenderer::SetVertex2f( cursorPositionX, cursorBottomPositionY + ( m_fontHeightPixels * 0.8f ) );
	}
	OpenGLRenderer::EndRender();
}


//-----------------------------------------------------------------------------------------------
void TextBox::Render()
{
	OpenGLRenderer::PushMatrix();

	OpenGLRenderer::SetColor4f( m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a );
	OpenGLRenderer::BeginRender( QUADS );
	{
		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x, m_screenPositionBottomLeft.y );
		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x + m_widthPixels, m_screenPositionBottomLeft.y );
		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x + m_widthPixels, m_screenPositionBottomLeft.y + m_heightPixels );
		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x, m_screenPositionBottomLeft.y + m_heightPixels );
	}
	OpenGLRenderer::EndRender();

	OpenGLRenderer::SetLineWidth( m_borderWidth );
	OpenGLRenderer::SetColor4f( m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a );
	OpenGLRenderer::BeginRender( LINES );
	{
		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x - ( m_borderWidth * 0.5f ), m_screenPositionBottomLeft.y + m_heightPixels );
		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x + m_widthPixels + ( m_borderWidth * 0.5f ), m_screenPositionBottomLeft.y + m_heightPixels );

		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x - ( m_borderWidth * 0.5f ), m_screenPositionBottomLeft.y );
		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x + m_widthPixels + ( m_borderWidth * 0.5f ), m_screenPositionBottomLeft.y );

		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x, m_screenPositionBottomLeft.y + m_heightPixels );
		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x, m_screenPositionBottomLeft.y );

		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x + m_widthPixels, m_screenPositionBottomLeft.y + m_heightPixels );
		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x + m_widthPixels, m_screenPositionBottomLeft.y );
	}
	OpenGLRenderer::EndRender();

	Vector2 textPosition( m_screenPositionBottomLeft.x + 2.f, m_screenPositionBottomLeft.y - 1.f );
	OpenGLRenderer::RenderText( m_text, m_font, m_fontHeightPixels, textPosition, m_fontColor );

	RenderCursor();

	OpenGLRenderer::PopMatrix();
}