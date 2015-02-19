#ifndef include_ErrorWarningAssertions
#define include_ErrorWarningAssertions
#pragma once

/////////////////////////////////////////////////////////////////////////////////////////////////
// Based on code originally written by Squirrel Eiserloh 
/////////////////////////////////////////////////////////////////////////////////////////////////


//-----------------------------------------------------------------------------------------------
#include <string>


//-----------------------------------------------------------------------------------------------
enum SeverityLevel
{
	SEVERITY_INFORMATION,
	SEVERITY_QUESTION,
	SEVERITY_WARNING,
	SEVERITY_FATAL
};


//-----------------------------------------------------------------------------------------------
void DebuggerPrintf( const char* messageFormat, ... );
bool IsDebuggerAvailable();
void RecoverableError( const char* cppFileName, int cppLineNum, const std::string& errorMessage, const char* conditionText=nullptr );
__declspec( noreturn ) void FatalError( const char* cppFileName, int cppLineNum, const std::string& errorMessage, const char* conditionText=nullptr );
void SystemDialogue_Okay( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity );
bool SystemDialogue_OkayCancel( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity );
bool SystemDialogue_YesNo( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity );
int SystemDialogue_YesNoCancel( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity );


//-----------------------------------------------------------------------------------------------
#define FATAL_ERROR( errorMessageText )															\
{																								\
	FatalError( __FILE__, __LINE__, errorMessageText );											\
}


//-----------------------------------------------------------------------------------------------
#define FATAL_ASSERTION( condition, errorMessageText )											\
{																								\
	if( !condition )																			\
	{																							\
		const char* conditionText = #condition;													\
		FatalError( __FILE__, __LINE__, errorMessageText, conditionText );					\
	}																							\
}


//-----------------------------------------------------------------------------------------------
#define RECOVERABLE_ERROR( errorMessageText )													\
{																								\
	RecoverableError( __FILE__, __LINE__, errorMessageText );									\
}


//-----------------------------------------------------------------------------------------------
#define RECOVERABLE_ASSERTION( condition, errorMessageText )									\
{																								\
	if( !condition )																			\
	{																							\
		const char* conditionText = #condition;													\
		RecoverableError( __FILE__, __LINE__, errorMessageText, conditionText );				\
	}																							\
}


#endif // include_ErrorWarningAssertions