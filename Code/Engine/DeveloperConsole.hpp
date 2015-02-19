#ifndef include_DeveloperConsole
#define include_DeveloperConsole
#pragma once

//-----------------------------------------------------------------------------------------------
#include <map>
#include <string>
#include <vector>
#include "Color.hpp"
#include "Vertex.hpp"
#include "Vector2.hpp"
#include "Keyboard.hpp"
#include "Material.hpp"
#include "BitmapFont.hpp"
#include "ConsoleLogLine.hpp"
#include "ConsoleCommandArgs.hpp"
#include "OpenGLShaderProgram.hpp"


//-----------------------------------------------------------------------------------------------
typedef bool (*CommandFuncPtr)(const ConsoleCommandArgs& args);


//-----------------------------------------------------------------------------------------------
const float CURSOR_BLINKS_PER_SECOND = 1.5f;
const float SECONDS_FOR_CURSOR_BLINK_TOGGLE = 1.f / ( 2.f * CURSOR_BLINKS_PER_SECOND );
const float CURSOR_LINE_WIDTH = 1.f;
const float FONT_CELL_HEIGHT_PIXELS = 30.f;
const float COMMAND_PROMPT_HEIGHT_PIXELS = FONT_CELL_HEIGHT_PIXELS * 1.2f;
const float COMMAND_PROMPT_OUTLINE_LINE_WIDTH = 3.f;
const float COMMAND_PROMPT_TEXT_SPACING = 7.f;
const float FONT_SHADOW_OFFSET_PIXELS_X = 2.f;
const float FONT_SHADOW_OFFSET_PIXELS_Y = -2.f;
const Color CONSOLE_BACKGROUND_COLOR = Color( 0.1f, 0.1f, 0.1f, 0.7f );
const Color COMMAND_PROMPT_OUTLINE_COLOR = Color::White;
const Color FUNCTION_NOT_FOUND_LINE_COLOR = Color::Red;
const Color FUNCTION_UNSUCCESSFUL_LINE_COLOR = Color::Yellow;
const Color FUNCTION_SUCCESS_LINE_COLOR = Color::White;
const Color FONT_SHADOW_COLOR = Color::Black;


//-----------------------------------------------------------------------------------------------
class DeveloperConsole
{
public:
	DeveloperConsole() {}
	DeveloperConsole( const Vector2& bottomLeftPosition, const Vector2& topRightPosition, const BitmapFont& font );
	void AddCommandFuncPtr( const std::string& functionName, const CommandFuncPtr functionPtr );
	void Update( const Keyboard& keyboard, float deltaSeconds );
	void Render();

	bool							m_drawConsole;
	std::vector<ConsoleLogLine>		m_consoleLogLines;

private:
	void CheckForKeyPress( const Keyboard& keyboard );
	void CheckForCharDelete( const Keyboard& keyboard );
	void CheckForCursorMovement( const Keyboard& keyboard );
	void CheckForLogHistoryMovement( const Keyboard& keyboard );
	void CheckForCommandExecute( const Keyboard& keyboard );
	void ExecuteConsoleCommand( const std::string& consoleCommandName, const std::string& argsString );
	void RenderConsoleBackground();
	void RenderCommandPromptBorder();
	void RenderCursor();
	void RenderText();

	Vector2									m_bottomLeftPosition;
	Vector2									m_topRightPosition;
	BitmapFont								m_font;
	unsigned int							m_cursorPosition;
	unsigned int							m_consoleTextEntryPosition;
	bool									m_drawCursor;
	float									m_secondsSinceCursorRenderToggle;
	ConsoleLogLine							m_commandPromptLine;
	std::vector<ConsoleLogLine>				m_consoleLogHistoryLines;
	std::map<std::string, CommandFuncPtr>	m_commandFunctionPtrs;
};


#endif // include_DeveloperConsole