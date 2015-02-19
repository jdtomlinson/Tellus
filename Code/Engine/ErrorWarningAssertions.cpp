#include "ErrorWarningAssertions.hpp"
#include <stdarg.h>
#include <iostream>
#include <windows.h>
#include "StringFunctions.hpp"


/////////////////////////////////////////////////////////////////////////////////////////////////
// Based on code originally written by Squirrel Eiserloh 
/////////////////////////////////////////////////////////////////////////////////////////////////


//-----------------------------------------------------------------------------------------------
void DebuggerPrintf( const char* messageFormat, ... )
{
	const int MESSAGE_MAX_LENGTH = 2048;
	char messageLiteral[ MESSAGE_MAX_LENGTH ];
	va_list variableArgumentList;
	va_start( variableArgumentList, messageFormat );
	vsnprintf_s( messageLiteral, MESSAGE_MAX_LENGTH, _TRUNCATE, messageFormat, variableArgumentList );
	va_end( variableArgumentList );
	messageLiteral[ MESSAGE_MAX_LENGTH - 1 ] = '\0';

	if( IsDebuggerAvailable() )
	{
		OutputDebugStringA( messageLiteral );
	}

	std::cout << messageLiteral;
}


//-----------------------------------------------------------------------------------------------
bool IsDebuggerAvailable()
{
	typedef BOOL (CALLBACK IsDebugFuncType)();

	HINSTANCE hInstanceKernel32 = GetModuleHandle( TEXT( "KERNEL32" ) );
	if( !hInstanceKernel32 )
		return false;

	IsDebugFuncType* isDebuggerPresentFunc = (IsDebugFuncType*) GetProcAddress( hInstanceKernel32, "IsDebuggerPresent" );
	if( !isDebuggerPresentFunc )
		return false;

	BOOL isDebuggerAvailable = isDebuggerPresentFunc();
	return( isDebuggerAvailable == TRUE );
}


//-----------------------------------------------------------------------------------------------
__declspec( noreturn ) void FatalError( const char* cppFileName, int cppLineNum, const std::string& errorMessage, const char* conditionText )
{
	std::string fullMessageTitle =  "Fatal Error";
	std::string fullMessageText = errorMessage;
	fullMessageText += "\n\nThe application will now close.\n";
	bool isDebuggerPresent = ( IsDebuggerPresent() == TRUE );

	if( conditionText )
	{
		fullMessageText += "\n---------- Debugging Details Follow ----------\n";
		fullMessageText += "\nThis error was caused by a run-time condition check from line " + ConvertNumberToString( cppLineNum ) +" of:\n" + cppFileName + "\n\nThe condition asserted which failed was:\n  \"" + conditionText + "\"\n";
	}

	DebuggerPrintf( "%s(%d): %s", cppFileName, cppLineNum, fullMessageText.c_str() ); // Use this specific format so Visual Studio users can double-click to jump to file-and-line of error

	if( isDebuggerPresent )
	{
		fullMessageText += "\nDEBUGGER DETECTED!\nWould you like to break and debug?\n  (No to quit)\n";
		bool isAnswerYes = SystemDialogue_YesNo( fullMessageTitle, fullMessageText, SEVERITY_FATAL );
		ShowCursor( TRUE );
		if( isAnswerYes )
		{
			__debugbreak();
		}
	}
	else
	{
		SystemDialogue_Okay( fullMessageTitle, fullMessageText, SEVERITY_FATAL );
		ShowCursor( TRUE );
	}

	exit( -1 );
}


//-----------------------------------------------------------------------------------------------
void RecoverableError( const char* cppFileName, int cppLineNum, const std::string& errorMessage, const char* conditionText )
{
	std::string fullMessageTitle = "Recoverable Warning";
	std::string fullMessageText = errorMessage;
	bool isDebuggerPresent = (IsDebuggerPresent() == TRUE);

	if( isDebuggerPresent )
	{
		fullMessageText += "\n\nDEBUGGER DETECTED!\nWould you like to continue running?\n  (Cancel to debug, No to quit)\n";
	}
	else
	{
		fullMessageText += "\n\nWould you like to continue running?\n  (No to quit)\n";
	}

	if( conditionText )
	{
		fullMessageText += "\n---------- Debugging Details Follow ----------\n";
		fullMessageText += "\nThis error was caused by a run-time condition check from line " + ConvertNumberToString( cppLineNum ) + " of:\n" + cppFileName + "\n\nThe condition asserted which failed was:\n  \"" + conditionText + "\"\n";
	}

	DebuggerPrintf( "%s(%d): %s", cppFileName, cppLineNum, fullMessageText.c_str() ); // Use this specific format so Visual Studio users can double-click to jump to file-and-line of error

	if( isDebuggerPresent )
	{
		int answerCode = SystemDialogue_YesNoCancel( fullMessageTitle, fullMessageText, SEVERITY_WARNING );
		ShowCursor( TRUE );
		if( answerCode == 0 ) // "NO"
		{
			exit( -1 );
		}
		else if( answerCode == -1 ) // "CANCEL"
		{
			__debugbreak();
		}
	}
	else
	{
		bool isAnswerYes = SystemDialogue_YesNo( fullMessageTitle, fullMessageText, SEVERITY_WARNING );
		ShowCursor( TRUE );
		if( !isAnswerYes )
		{
			exit( -1 );
		}
	}
}


//-----------------------------------------------------------------------------------------------
UINT GetWindowsMessageBoxIconFlagForSeverityLevel( SeverityLevel severity )
{
	switch( severity )
	{
		case SEVERITY_INFORMATION:		return MB_ICONASTERISK;
		case SEVERITY_QUESTION:			return MB_ICONQUESTION;
		case SEVERITY_WARNING:			return MB_ICONEXCLAMATION;
		case SEVERITY_FATAL:			return MB_ICONHAND;
		default:						return MB_ICONEXCLAMATION;
	}
}


//-----------------------------------------------------------------------------------------------
void SystemDialogue_Okay( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity )
{
	ShowCursor( TRUE );
	UINT dialogueIconTypeFlag = GetWindowsMessageBoxIconFlagForSeverityLevel( severity );
	MessageBoxA( NULL, messageText.c_str(), messageTitle.c_str(), MB_OK | dialogueIconTypeFlag | MB_TOPMOST );
	ShowCursor( FALSE );
}


//-----------------------------------------------------------------------------------------------
bool SystemDialogue_OkayCancel( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity )
{
	bool isAnswerOkay = true;

	ShowCursor( TRUE );
	UINT dialogueIconTypeFlag = GetWindowsMessageBoxIconFlagForSeverityLevel( severity );
	int buttonClicked = MessageBoxA( NULL, messageText.c_str(), messageTitle.c_str(), MB_OKCANCEL | dialogueIconTypeFlag | MB_TOPMOST );
	isAnswerOkay = (buttonClicked == IDOK);
	ShowCursor( FALSE );

	return isAnswerOkay;
}


//-----------------------------------------------------------------------------------------------
bool SystemDialogue_YesNo( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity )
{
	bool isAnswerYes = true;

	ShowCursor( TRUE );
	UINT dialogueIconTypeFlag = GetWindowsMessageBoxIconFlagForSeverityLevel( severity );
	int buttonClicked = MessageBoxA( NULL, messageText.c_str(), messageTitle.c_str(), MB_YESNO | dialogueIconTypeFlag | MB_TOPMOST );
	isAnswerYes = (buttonClicked == IDYES);
	ShowCursor( FALSE );

	return isAnswerYes;
}


//-----------------------------------------------------------------------------------------------
int SystemDialogue_YesNoCancel( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity )
{
	int answerCode = 1;

	ShowCursor( TRUE );
	UINT dialogueIconTypeFlag = GetWindowsMessageBoxIconFlagForSeverityLevel( severity );
	int buttonClicked = MessageBoxA( NULL, messageText.c_str(), messageTitle.c_str(), MB_YESNOCANCEL | dialogueIconTypeFlag | MB_TOPMOST );
	answerCode = (buttonClicked == IDYES ? 1 : (buttonClicked == IDNO ? 0 : -1) );
	ShowCursor( FALSE );

	return answerCode;
}