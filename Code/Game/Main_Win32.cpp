#include <windows.h>
#include <math.h>
#include <cassert>
#include <crtdbg.h>
#include "Game.hpp"
#include "../Engine/Time.hpp"
#include "../Engine/Texture.hpp"
#include "../Engine/Material.hpp"
#include "../Engine/BitmapFont.hpp"
#include "../Engine/EngineCommon.hpp"
#include "../Engine/OpenGLRenderer.hpp"
#include "../Engine/DeveloperConsole.hpp"
#include "../Engine/ErrorWarningAssertions.hpp"
#pragma comment( lib, "opengl32" ) // Link in the OpenGL32.lib static library
#pragma comment( lib, "glu32" ) // Link in the GLU32.lib static library

//-----------------------------------------------------------------------------------------------
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;
const std::string MAIN_FONT_GLYPH_SHEET_FILE_NAME = "Data/Fonts/MainFont_EN_00.png";
const std::string MAIN_FONT_META_DATA_FILE_NAME = "Data/Fonts/MainFont_EN.FontDef.xml";


//-----------------------------------------------------------------------------------------------
Game g_game( (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT );
unsigned char* g_pixelData;
Texture* g_mainFontGlyphSheet;
BitmapFont g_consoleFont;
DeveloperConsole g_developerConsole;


//-----------------------------------------------------------------------------------------------
#define UNUSED(x) (void)(x);


//-----------------------------------------------------------------------------------------------
bool g_isQuitting = false;
bool g_isPerformingTest = false;
HWND g_hWnd = nullptr;
HDC g_displayDeviceContext = nullptr;
HGLRC g_openGLRenderingContext = nullptr;
const char* APP_NAME = "Tellus Heightmap Generator";


//-----------------------------------------------------------------------------------------------
LRESULT CALLBACK WindowsMessageHandlingProcedure( HWND windowHandle, UINT wmMessageCode, WPARAM wParam, LPARAM lParam )
{
	switch( wmMessageCode )
	{
		case WM_CLOSE:
		case WM_DESTROY:
		case WM_QUIT:
			g_isQuitting = true;
			return 0;

		case WM_KEYDOWN:
		{
			unsigned char asKey = (unsigned char) wParam;
			/*if( asKey == VK_ESCAPE && !g_developerConsole.m_drawConsole )
			{
				g_isQuitting = true;
				return 0;
			}*/

			bool wasProcessed = g_game.ProcessKeyDownEvent( asKey );
			if( wasProcessed )
			{
				return 0;
			}

			break;
		}
		case WM_KEYUP:
		{
			unsigned char asKey = (unsigned char) wParam;
			bool wasProcessed = g_game.ProcessKeyUpEvent( asKey );
			if( wasProcessed )
			{
				return 0;
			}

			break;
		}
		case WM_CHAR:
		{
			unsigned char asChar = (unsigned char) wParam;
			bool wasProcessed = g_game.ProcessCharDownEvent( asChar );
			if( wasProcessed )
			{
				return 0;
			}

			break;
		}
	}

	return DefWindowProc( windowHandle, wmMessageCode, wParam, lParam );
}


//-----------------------------------------------------------------------------------------------
void CreateOpenGLWindow( HINSTANCE applicationInstanceHandle )
{
	// Define a window class
	WNDCLASSEX windowClassDescription;
	memset( &windowClassDescription, 0, sizeof( windowClassDescription ) );
	windowClassDescription.cbSize = sizeof( windowClassDescription );
	windowClassDescription.style = CS_OWNDC; // Redraw on move, request own Display Context
	windowClassDescription.lpfnWndProc = static_cast< WNDPROC >( WindowsMessageHandlingProcedure ); // Assign a win32 message-handling function
	windowClassDescription.hInstance = GetModuleHandle( NULL );
	windowClassDescription.hIcon = NULL;
	windowClassDescription.hCursor = NULL;
	windowClassDescription.lpszClassName = TEXT( "Simple Window Class" );
	RegisterClassEx( &windowClassDescription );

	const DWORD windowStyleFlags = WS_CAPTION | WS_BORDER | WS_THICKFRAME | WS_SYSMENU | WS_OVERLAPPED;
	const DWORD windowStyleExFlags = WS_EX_APPWINDOW;

	RECT desktopRect;
	HWND desktopWindowHandle = GetDesktopWindow();
	GetClientRect( desktopWindowHandle, &desktopRect );

	RECT windowRect = { 50 + 0, 50 + 0, 50 + SCREEN_WIDTH, 50 + SCREEN_HEIGHT };
	AdjustWindowRectEx( &windowRect, windowStyleFlags, FALSE, windowStyleExFlags );

	WCHAR windowTitle[ 1024 ];
	MultiByteToWideChar( GetACP(), 0, APP_NAME, -1, windowTitle, sizeof(windowTitle)/sizeof(windowTitle[0]) );
	g_hWnd = CreateWindowEx(
		windowStyleExFlags,
		windowClassDescription.lpszClassName,
		windowTitle,
		windowStyleFlags,
		windowRect.left,
		windowRect.top,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		applicationInstanceHandle,
		NULL );

	ShowWindow( g_hWnd, SW_SHOW );
	SetForegroundWindow( g_hWnd );
	SetFocus( g_hWnd );

	g_displayDeviceContext = GetDC( g_hWnd );

	HCURSOR cursor = LoadCursor( NULL, IDC_ARROW );
	SetCursor( cursor );
	//ShowCursor( FALSE );

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	memset( &pixelFormatDescriptor, 0, sizeof( pixelFormatDescriptor ) );
	pixelFormatDescriptor.nSize			= sizeof( pixelFormatDescriptor );
	pixelFormatDescriptor.nVersion		= 1;
	pixelFormatDescriptor.dwFlags		= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDescriptor.iPixelType	= PFD_TYPE_RGBA;
	pixelFormatDescriptor.cColorBits	= 24;
	pixelFormatDescriptor.cDepthBits	= 24;
	pixelFormatDescriptor.cAccumBits	= 0;
	pixelFormatDescriptor.cStencilBits	= 8;

	int pixelFormatCode = ChoosePixelFormat( g_displayDeviceContext, &pixelFormatDescriptor );
	SetPixelFormat( g_displayDeviceContext, pixelFormatCode, &pixelFormatDescriptor );
	g_openGLRenderingContext = wglCreateContext( g_displayDeviceContext );
	wglMakeCurrent( g_displayDeviceContext, g_openGLRenderingContext );

	// Set up OpenGL states
	OpenGLRenderer::EnableBlend();
	OpenGLRenderer::EnableDepthTest();
	OpenGLRenderer::EnableCullFace();
	OpenGLRenderer::CullFrontFaceDirection( COUNTER_CLOCKWISE );
	OpenGLRenderer::BlendFunction( SRC_ALPHA, ONE_MINUS_SRC_ALPHA );
}


//-----------------------------------------------------------------------------------------------
void RunMessagePump()
{
	MSG queuedMessage;
	for( ;; )
	{
		const BOOL wasMessagePresent = PeekMessage( &queuedMessage, NULL, 0, 0, PM_REMOVE );
		if( !wasMessagePresent )
		{
			break;
		}

		TranslateMessage( &queuedMessage );
		DispatchMessage( &queuedMessage );
	}
}


//-----------------------------------------------------------------------------------------------
bool ConsoleFunctionClear( const ConsoleCommandArgs& )
{
	g_developerConsole.m_consoleLogLines.clear();
	return true;
}


//-----------------------------------------------------------------------------------------------
bool ConsoleFunctionQuit( const ConsoleCommandArgs& )
{
	g_isQuitting = true;
	return true;
}


//-----------------------------------------------------------------------------------------------
void Update()
{
	g_game.Update( g_hWnd );
}


//-----------------------------------------------------------------------------------------------
void Render()
{
	OpenGLRenderer::SetClearColor( 0.f, 0.4f, 0.6f, 1.f );
	OpenGLRenderer::SetClearDepth( 1.f );
	OpenGLRenderer::ClearColorBufferBit();
	OpenGLRenderer::ClearDepthBufferBit();

	g_game.Render();

	SwapBuffers( g_displayDeviceContext );
}


//-----------------------------------------------------------------------------------------------
void WaitUntilNextFrameTime()
{
	double timeNow = GetCurrentTimeSeconds();
	static double targetTime = timeNow;
	while( timeNow < targetTime )
	{
		timeNow = GetCurrentTimeSeconds();
	}
	targetTime = timeNow + FRAME_TIME_SECONDS;
}


//-----------------------------------------------------------------------------------------------
void RunFrame()
{
	RunMessagePump();
	Update();
	Render();
	WaitUntilNextFrameTime();
}


//-----------------------------------------------------------------------------------------------
void LoadTextures()
{
	g_mainFontGlyphSheet = Texture::CreateOrGetTexture( "Data/Fonts/MainFont_EN_00.png" );
}


//-----------------------------------------------------------------------------------------------
void LoadDeveloperConsole()
{
	g_consoleFont = BitmapFont( MAIN_FONT_GLYPH_SHEET_FILE_NAME, MAIN_FONT_META_DATA_FILE_NAME );
	g_developerConsole = DeveloperConsole( Vector2( 0.f, (float) SCREEN_HEIGHT * 0.25f ), Vector2( (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT ), g_consoleFont );
	g_developerConsole.AddCommandFuncPtr( "clear", ConsoleFunctionClear );
	g_developerConsole.AddCommandFuncPtr( "quit", ConsoleFunctionQuit );
}


//-----------------------------------------------------------------------------------------------
void DeleteTexture( Texture*& texture )
{
	delete texture;
	texture = nullptr;
}


//-----------------------------------------------------------------------------------------------
void UnloadTextures()
{
	DeleteTexture( g_mainFontGlyphSheet );
	Texture::DeconstructTexture();
}


//-----------------------------------------------------------------------------------------------
void Initialize( HINSTANCE applicationInstanceHandle )
{
	CreateOpenGLWindow( applicationInstanceHandle );
	OpenGLRenderer::Initalize();
	InitializeTime();
	LoadTextures();
	LoadDeveloperConsole();
	g_game.Initialize();
}


//-----------------------------------------------------------------------------------------------
void RunCommandlet( const std::string& commandName, const std::vector< std::string > args )
{
	std::string lowercaseCommandName = GetLowercaseString( commandName );
	if( lowercaseCommandName == "help" )
	{

	}
	else if( lowercaseCommandName == "test" )
	{
		if( args.size() != 0 )
			RECOVERABLE_ERROR( "The commandlet \"test\" doesn't use any arguments. All following arguments will be disregarded." );

		g_isPerformingTest = true;
	}
}


//-----------------------------------------------------------------------------------------------
void ParseCommandLineArgument( const std::string& commandLineString )
{
	std::vector< std::string > commands;
	std::vector< std::vector< std::string > > arguments;
	std::string currentCommand = "";
	std::string currentArgument = "";
	bool isBetweenQuotes = false;

	for( unsigned int charIndex = 0; charIndex < commandLineString.size(); ++charIndex )
	{
		char currentChar = commandLineString[ charIndex ];
		if( currentChar == '\"' )
		{
			isBetweenQuotes = !isBetweenQuotes;
			if( isBetweenQuotes )
				continue;
		}

		if( isBetweenQuotes || ( !isspace( currentChar ) && currentChar != '\"' ) )
		{
			currentArgument += currentChar;
			continue;
		}

		if( currentArgument.size() == 0 )
			continue;

		if( currentArgument[0] == '-' )
		{
			currentCommand = currentArgument.substr( 1 );
			commands.push_back( currentCommand );
			std::vector< std::string > newVector;
			arguments.push_back( newVector );
		}
		else if( arguments.size() > 0 )
		{
			int index = arguments.size() - 1;
			std::vector< std::string > args = arguments[ index ];
			args.push_back( currentArgument );
			arguments[ index ] = args;
		}

		currentArgument = "";
	}

	if( currentArgument.size() > 0 )
	{
		if( currentArgument[0] == '-' )
		{
			currentCommand = currentArgument.substr( 1 );
			commands.push_back( currentCommand );
			std::vector< std::string > newVector;
			arguments.push_back( newVector );
		}
		else if( arguments.size() > 0 )
		{
			int index = arguments.size() - 1;
			std::vector< std::string > args = arguments[ index ];
			args.push_back( currentArgument );
			arguments[ index ] = args;
		}
	}

	for( unsigned int commandIndex = 0; commandIndex < commands.size(); ++commandIndex )
	{
		std::string command = commands[ commandIndex ];
		std::vector< std::string > args = arguments[ commandIndex ];
		RunCommandlet( command, args );
	}
}


//-----------------------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE applicationInstanceHandle, HINSTANCE, LPSTR commandLineString, int )
{
	ParseCommandLineArgument( commandLineString );

	Initialize( applicationInstanceHandle );

	while( !g_isQuitting )	
	{
		RunFrame();
	}

	UnloadTextures();

#if defined( _WIN32 ) && defined( _DEBUG )
	assert( _CrtCheckMemory() );
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}