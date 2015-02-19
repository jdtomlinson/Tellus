#include "DeveloperConsole.hpp"
#include "OpenGLRenderer.hpp"
#include "StringFunctions.hpp"


//-----------------------------------------------------------------------------------------------
DeveloperConsole::DeveloperConsole( const Vector2& bottomLeftPosition, const Vector2& topRightPosition, const BitmapFont& font )
	: m_drawConsole( false )
	, m_bottomLeftPosition( bottomLeftPosition )
	, m_topRightPosition( topRightPosition )
	, m_font( font )
	, m_cursorPosition( 0 )
	, m_consoleTextEntryPosition( 0 )
	, m_drawCursor( true )
	, m_secondsSinceCursorRenderToggle( 0.f )
	, m_commandPromptLine( "", COMMAND_PROMPT_OUTLINE_COLOR )
{

}


//-----------------------------------------------------------------------------------------------
void DeveloperConsole::AddCommandFuncPtr( const std::string& functionName, const CommandFuncPtr functionPtr )
{
	m_commandFunctionPtrs.insert( std::pair<std::string, CommandFuncPtr>( GetLowercaseString( functionName ), functionPtr ) );
}


//-----------------------------------------------------------------------------------------------
void DeveloperConsole::Update( const Keyboard& keyboard, float deltaSeconds )
{
	CheckForKeyPress( keyboard );

	m_secondsSinceCursorRenderToggle += deltaSeconds;
	if( m_secondsSinceCursorRenderToggle > SECONDS_FOR_CURSOR_BLINK_TOGGLE )
	{
		m_secondsSinceCursorRenderToggle -= SECONDS_FOR_CURSOR_BLINK_TOGGLE;
		m_drawCursor = !m_drawCursor;
	}
}


//-----------------------------------------------------------------------------------------------
void DeveloperConsole::Render()
{
	OpenGLRenderer::PushMatrix();

	RenderConsoleBackground();
	RenderCommandPromptBorder();
	RenderCursor();
	RenderText();

	OpenGLRenderer::PopMatrix();
}


//-----------------------------------------------------------------------------------------------
void DeveloperConsole::CheckForKeyPress( const Keyboard& keyboard )
{
	if( keyboard.IsKeyPressedDown( KEY_TILDE ) )
	{
		m_commandPromptLine.m_text = "";
		m_cursorPosition = 0;
		return;
	}

	if( keyboard.IsKeyPressedDownAndWasNotBefore( KEY_ESCAPE ) )
	{
		if( m_commandPromptLine.m_text.size() > 0 )
		{
			m_commandPromptLine.m_text = "";
			m_cursorPosition = 0;
		}
		else
			m_drawConsole = false;

		return;
	}

	if( keyboard.IsKeyPressedDownAndWasNotBefore( KEY_ENTER ) && m_commandPromptLine.m_text.size() == 0 )
	{
		m_drawConsole = false;
		return;
	}

	CheckForCharDelete( keyboard );
	CheckForCursorMovement( keyboard );
	CheckForLogHistoryMovement( keyboard );
	CheckForCommandExecute( keyboard );

	for( unsigned int charIndex = CHAR_VALUES_START; charIndex < NUM_KEYBOARD_CHARS; ++charIndex )
	{
		if( keyboard.IsCharPressedDown( (unsigned char) charIndex ) )
		{
			m_commandPromptLine.m_text.insert( m_cursorPosition, 1, (unsigned char) charIndex );
			m_drawCursor = true;
			m_secondsSinceCursorRenderToggle = 0.f;
			++m_cursorPosition;
			return;
		}
	}
}


//-----------------------------------------------------------------------------------------------
void DeveloperConsole::CheckForCharDelete( const Keyboard& keyboard )
{
	if( keyboard.IsKeyPressedDownAndWasNotBefore( KEY_BACK ) || keyboard.IsKeyPressedDownAndWasNotBefore( KEY_DELETE ) || keyboard.IsCharPressedDown( 0x08 ) )
	{
		if( m_commandPromptLine.m_text.size() > 0 )
		{
			if( m_cursorPosition == 0 )
				return;

			if( m_cursorPosition == m_commandPromptLine.m_text.size() )
				m_commandPromptLine.m_text.pop_back();
			else
				m_commandPromptLine.m_text.erase( m_cursorPosition - 1, 1 );

			--m_cursorPosition;
		}
	}
}


//-----------------------------------------------------------------------------------------------
void DeveloperConsole::CheckForCursorMovement( const Keyboard& keyboard )
{
	if( keyboard.IsKeyPressedDownAndWasNotBefore( KEY_LEFT_ARROW ) )
	{
		if( m_cursorPosition > 0 )
			--m_cursorPosition;
	}

	if( keyboard.IsKeyPressedDownAndWasNotBefore( KEY_RIGHT_ARROW ) )
	{
		if( m_cursorPosition < m_commandPromptLine.m_text.size() )
			++m_cursorPosition;
	}

	if( keyboard.IsKeyPressedDownAndWasNotBefore( KEY_HOME ) )
	{
		m_cursorPosition = 0;
	}

	if( keyboard.IsKeyPressedDownAndWasNotBefore( KEY_END ) )
	{
		m_cursorPosition = m_commandPromptLine.m_text.size();
	}
}


//-----------------------------------------------------------------------------------------------
void DeveloperConsole::CheckForLogHistoryMovement( const Keyboard& keyboard )
{
	if( keyboard.IsKeyPressedDownAndWasNotBefore( KEY_UP_ARROW ) )
	{
		if( m_consoleTextEntryPosition > 0 )
		{
			--m_consoleTextEntryPosition;
			m_commandPromptLine = m_consoleLogHistoryLines[ m_consoleTextEntryPosition ];
			m_cursorPosition = m_commandPromptLine.m_text.size();
		}
	}

	if( keyboard.IsKeyPressedDownAndWasNotBefore( KEY_DOWN_ARROW ) )
	{
		if( m_consoleTextEntryPosition < m_consoleLogHistoryLines.size() )
		{
			++m_consoleTextEntryPosition;

			if( m_consoleTextEntryPosition == m_consoleLogHistoryLines.size() )
			{
				m_commandPromptLine.m_text = "";
				m_cursorPosition = 0;
			}
			else
			{
				m_commandPromptLine = m_consoleLogHistoryLines[ m_consoleTextEntryPosition ];
				m_cursorPosition = m_commandPromptLine.m_text.size();
			}
		}
	}
}


//-----------------------------------------------------------------------------------------------
void DeveloperConsole::CheckForCommandExecute( const Keyboard& keyboard )
{
	if( keyboard.IsKeyPressedDownAndWasNotBefore( KEY_ENTER ) )
	{
		if( m_commandPromptLine.m_text.size() > 0 )
		{
			if( m_consoleLogHistoryLines.size() == 0 )
				m_consoleLogHistoryLines.push_back( m_commandPromptLine );
			else if( m_consoleLogHistoryLines.size() > 0 && m_commandPromptLine.m_text != m_consoleLogHistoryLines.back().m_text )
				m_consoleLogHistoryLines.push_back( m_commandPromptLine );

			while( m_commandPromptLine.m_text.size() > 0 && m_commandPromptLine.m_text[ 0 ] == ' ' )
				m_commandPromptLine.m_text.erase( 0, 1 );

			int firstSpacePos = m_commandPromptLine.m_text.find( ' ' );
			if( firstSpacePos == -1 )
				ExecuteConsoleCommand( m_commandPromptLine.m_text, "" );
			else
				ExecuteConsoleCommand( m_commandPromptLine.m_text.substr( 0, firstSpacePos ), m_commandPromptLine.m_text.substr( firstSpacePos + 1 ) );

			m_commandPromptLine.m_text = "";
			m_cursorPosition = 0;
			m_consoleTextEntryPosition = m_consoleLogHistoryLines.size();
		}
	}
}


//-----------------------------------------------------------------------------------------------
void DeveloperConsole::ExecuteConsoleCommand( const std::string& consoleCommandName, const std::string& argsString )
{
	std::map<std::string, CommandFuncPtr>::iterator mapIter;
	mapIter = m_commandFunctionPtrs.find( GetLowercaseString( consoleCommandName ) );
	if( mapIter == m_commandFunctionPtrs.end() )
	{
		ConsoleLogLine funcNotFoundLine( "Could not find function: " + consoleCommandName, FUNCTION_NOT_FOUND_LINE_COLOR );
		m_consoleLogLines.push_back( funcNotFoundLine );
		return;
	}

	ConsoleCommandArgs commandArgs( argsString );
	bool commandSuccess = mapIter->second( commandArgs );
	if( commandSuccess )
	{
		if( consoleCommandName == "clear" )
			return;

		ConsoleLogLine funcSuccessLine( consoleCommandName + " " + argsString, FUNCTION_SUCCESS_LINE_COLOR );
		m_consoleLogLines.push_back( funcSuccessLine );
	}
	else
	{
		ConsoleLogLine funcUnsuccessfulLine( "Function \"" + consoleCommandName + "\" failed" , FUNCTION_UNSUCCESSFUL_LINE_COLOR );
		m_consoleLogLines.push_back( funcUnsuccessfulLine );
	}
}


//-----------------------------------------------------------------------------------------------
void DeveloperConsole::RenderConsoleBackground()
{
	OpenGLRenderer::DisableTexture2D();
	OpenGLRenderer::SetColor4f( CONSOLE_BACKGROUND_COLOR.r, CONSOLE_BACKGROUND_COLOR.g, CONSOLE_BACKGROUND_COLOR.b, CONSOLE_BACKGROUND_COLOR.a );
	OpenGLRenderer::BeginRender( QUADS );
	{
		OpenGLRenderer::SetVertex2f( m_bottomLeftPosition.x, m_bottomLeftPosition.y );
		OpenGLRenderer::SetVertex2f( m_topRightPosition.x, m_bottomLeftPosition.y );
		OpenGLRenderer::SetVertex2f( m_topRightPosition.x, m_topRightPosition.y );
		OpenGLRenderer::SetVertex2f( m_bottomLeftPosition.x, m_topRightPosition.y );
	}
	OpenGLRenderer::EndRender();
}


//-----------------------------------------------------------------------------------------------
void DeveloperConsole::RenderCommandPromptBorder()
{
	OpenGLRenderer::DisableTexture2D();
	OpenGLRenderer::SetLineWidth( COMMAND_PROMPT_OUTLINE_LINE_WIDTH );
	OpenGLRenderer::SetColor4f( COMMAND_PROMPT_OUTLINE_COLOR.r, COMMAND_PROMPT_OUTLINE_COLOR.g, COMMAND_PROMPT_OUTLINE_COLOR.b, COMMAND_PROMPT_OUTLINE_COLOR.a );
	OpenGLRenderer::BeginRender( LINES );
	{
		// Command Prompt Outline
		OpenGLRenderer::SetVertex2f( m_bottomLeftPosition.x, m_bottomLeftPosition.y );
		OpenGLRenderer::SetVertex2f( m_topRightPosition.x, m_bottomLeftPosition.y );

		OpenGLRenderer::SetVertex2f( m_bottomLeftPosition.x, m_bottomLeftPosition.y + COMMAND_PROMPT_HEIGHT_PIXELS );
		OpenGLRenderer::SetVertex2f( m_topRightPosition.x, m_bottomLeftPosition.y + COMMAND_PROMPT_HEIGHT_PIXELS );

		// Command Prompt Arrow
		OpenGLRenderer::SetVertex2f( m_bottomLeftPosition.x + COMMAND_PROMPT_TEXT_SPACING, m_bottomLeftPosition.y + COMMAND_PROMPT_TEXT_SPACING );
		OpenGLRenderer::SetVertex2f( m_bottomLeftPosition.x + ( COMMAND_PROMPT_HEIGHT_PIXELS - COMMAND_PROMPT_TEXT_SPACING ), m_bottomLeftPosition.y + ( COMMAND_PROMPT_HEIGHT_PIXELS * 0.5f ) );

		OpenGLRenderer::SetVertex2f( m_bottomLeftPosition.x + ( COMMAND_PROMPT_HEIGHT_PIXELS - COMMAND_PROMPT_TEXT_SPACING ), m_bottomLeftPosition.y + ( COMMAND_PROMPT_HEIGHT_PIXELS * 0.5f ) );
		OpenGLRenderer::SetVertex2f( m_bottomLeftPosition.x + COMMAND_PROMPT_TEXT_SPACING, m_bottomLeftPosition.y + ( COMMAND_PROMPT_HEIGHT_PIXELS - COMMAND_PROMPT_TEXT_SPACING ) );
	}
	OpenGLRenderer::EndRender();
}


//-----------------------------------------------------------------------------------------------
void DeveloperConsole::RenderCursor()
{
	if( !m_drawCursor )
		return;

	std::string text = m_commandPromptLine.m_text;
	if( m_cursorPosition < m_commandPromptLine.m_text.size() )
		text = m_commandPromptLine.m_text.substr( 0, m_cursorPosition );

	float cursorPositionX = OpenGLRenderer::CalcTextWidth( text, m_font, FONT_CELL_HEIGHT_PIXELS ) + m_bottomLeftPosition.x + COMMAND_PROMPT_HEIGHT_PIXELS + CURSOR_LINE_WIDTH + FONT_SHADOW_OFFSET_PIXELS_X;
	float cursorBottomPositionY = m_bottomLeftPosition.y + COMMAND_PROMPT_OUTLINE_LINE_WIDTH;

	OpenGLRenderer::DisableTexture2D();
	OpenGLRenderer::SetLineWidth( CURSOR_LINE_WIDTH );
	OpenGLRenderer::SetColor4f( COMMAND_PROMPT_OUTLINE_COLOR.r, COMMAND_PROMPT_OUTLINE_COLOR.g, COMMAND_PROMPT_OUTLINE_COLOR.b, COMMAND_PROMPT_OUTLINE_COLOR.a );
	OpenGLRenderer::BeginRender( LINES );
	{
		OpenGLRenderer::SetVertex2f( cursorPositionX, cursorBottomPositionY );
		OpenGLRenderer::SetVertex2f( cursorPositionX, cursorBottomPositionY + ( FONT_CELL_HEIGHT_PIXELS - COMMAND_PROMPT_OUTLINE_LINE_WIDTH ) );
	}
	OpenGLRenderer::EndRender();
}


//-----------------------------------------------------------------------------------------------
void DeveloperConsole::RenderText()
{
	// Command Prompt Text
	OpenGLRenderer::RenderText( m_commandPromptLine.m_text, m_font, FONT_CELL_HEIGHT_PIXELS, Vector2( m_bottomLeftPosition.x + COMMAND_PROMPT_HEIGHT_PIXELS + FONT_SHADOW_OFFSET_PIXELS_X, m_bottomLeftPosition.y + ( COMMAND_PROMPT_OUTLINE_LINE_WIDTH * 0.5f ) + FONT_SHADOW_OFFSET_PIXELS_Y ), FONT_SHADOW_COLOR );
	OpenGLRenderer::RenderText( m_commandPromptLine.m_text, m_font, FONT_CELL_HEIGHT_PIXELS, Vector2( m_bottomLeftPosition.x + COMMAND_PROMPT_HEIGHT_PIXELS, m_bottomLeftPosition.y + ( COMMAND_PROMPT_OUTLINE_LINE_WIDTH * 0.5f ) ), m_commandPromptLine.m_color );

	// Console Log Text
	float textLineBottomY = m_bottomLeftPosition.y + COMMAND_PROMPT_HEIGHT_PIXELS + COMMAND_PROMPT_OUTLINE_LINE_WIDTH;

	std::vector<ConsoleLogLine>::reverse_iterator revIter;
	for( revIter = m_consoleLogLines.rbegin(); revIter != m_consoleLogLines.rend(); ++revIter )
	{
		if( ( textLineBottomY + FONT_CELL_HEIGHT_PIXELS ) > m_topRightPosition.y )
			break;

		OpenGLRenderer::RenderText( revIter->m_text, m_font, FONT_CELL_HEIGHT_PIXELS, Vector2( m_bottomLeftPosition.x + COMMAND_PROMPT_TEXT_SPACING + FONT_SHADOW_OFFSET_PIXELS_X, textLineBottomY + FONT_SHADOW_OFFSET_PIXELS_Y ), FONT_SHADOW_COLOR );
		OpenGLRenderer::RenderText( revIter->m_text, m_font, FONT_CELL_HEIGHT_PIXELS, Vector2( m_bottomLeftPosition.x + COMMAND_PROMPT_TEXT_SPACING, textLineBottomY ), revIter->m_color );
		textLineBottomY += FONT_CELL_HEIGHT_PIXELS;
	}
}