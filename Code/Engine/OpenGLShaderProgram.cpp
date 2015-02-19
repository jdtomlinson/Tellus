#include "OpenGLShaderProgram.hpp"
#include <vector>
#include "OpenGLRenderer.hpp"
#include "StringFunctions.hpp"


//-----------------------------------------------------------------------------------------------
OpenGLShaderProgram::OpenGLShaderProgram( const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName )
{
	CreateProgram( vertexShaderFileName, fragmentShaderFileName );

	m_modelViewProjectionMatUniformLocation = glGetUniformLocation( m_programID, "u_modelViewProjectionMatrix" );
}


//-----------------------------------------------------------------------------------------------
OpenGLShaderProgram::~OpenGLShaderProgram()
{
	glDeleteShader( m_vertexShaderID );
	glDeleteShader( m_fragmentShaderID );
	glDeleteProgram( m_programID );
}


//-----------------------------------------------------------------------------------------------
void OpenGLShaderProgram::CreateProgram( const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName )
{
	m_vertexShaderID = CreateShader( GL_VERTEX_SHADER, vertexShaderFileName );
	m_fragmentShaderID = CreateShader( GL_FRAGMENT_SHADER, fragmentShaderFileName );
	m_programID = glCreateProgram();
	glAttachShader( m_programID, m_vertexShaderID );
	glAttachShader( m_programID, m_fragmentShaderID );
	BindAttribLocations();
	glLinkProgram( m_programID );
	std::string programLog = GetProgramLinkerLog( m_programID );
	if( programLog == "" )
		return;

	OutputDebugStringA( programLog.c_str() );
	std::string text = GetLinkerErrorText( programLog, vertexShaderFileName, fragmentShaderFileName );
	ShowCursor( TRUE );
	MessageBoxA( 0, text.c_str(), "Linker Error Occurred", MB_OK );
	std::exit( EXIT_FAILURE );
}


//-----------------------------------------------------------------------------------------------
unsigned int OpenGLShaderProgram::CreateShader( int shaderType, const std::string& shaderFileName )
{
	unsigned int shaderID = glCreateShader( shaderType );
	std::string shaderCodeString = GetShaderCode( shaderFileName );
	if( shaderCodeString == "" )
	{
		std::string shortFileName = GetShortenedFileName( shaderFileName );
		std::string text = "Failed to open file " + shortFileName + "\nCheck file name or path.";
		std::string caption = "Can't open " + shortFileName;
		ShowCursor( TRUE );
		MessageBoxA( 0, text.c_str(), caption.c_str(), MB_OK );
		std::exit( EXIT_FAILURE );
	}

	const char* shaderCode = (const char*) shaderCodeString.c_str();
	glShaderSource( shaderID, 1, &shaderCode, 0 );
	glCompileShader( shaderID );
	std::string shaderLog = GetShaderCompileLog( shaderID );
	if( shaderLog == "" )
		return shaderID;

	EditShaderErrorLog( shaderLog, shaderFileName );
	OutputDebugStringA( shaderLog.c_str() );
	std::string shortFileName = GetShortenedFileName( shaderFileName );
	std::string errorText = GetCompileErrorText( shaderLog, shaderFileName );
	ShowCursor( TRUE );
	MessageBoxA( 0, errorText.c_str(), "Compile Error Occurred", MB_OK );
	std::exit( EXIT_FAILURE );
}


//-----------------------------------------------------------------------------------------------
void OpenGLShaderProgram::BindAttribLocations()
{
	glBindAttribLocation( m_programID, VERTEX_ATTRIB_POSITIONS, "a_vertex" );
	glBindAttribLocation( m_programID, VERTEX_ATTRIB_COLORS, "a_color" );
	glBindAttribLocation( m_programID, VERTEX_ATTRIB_TEX_COORDS, "a_texCoord" );
	glBindAttribLocation( m_programID, VERTEX_ATTRIB_NORMALS, "a_normal" );
	glBindAttribLocation( m_programID, VERTEX_ATTRIB_TANGENTS, "a_tangent" );
}


//-----------------------------------------------------------------------------------------------
std::string OpenGLShaderProgram::GetShaderCode( const std::string& shaderFileString )
{
	std::string shaderCode = "";
	FILE* shaderFile;
	errno_t checkForOpen;
	char* shaderFileName = (char*) shaderFileString.c_str();
	checkForOpen = fopen_s( &shaderFile, shaderFileName, "rb" );
	if( checkForOpen != 0 )
		return "";

	while( !feof( shaderFile ) )
	{
		char shaderCodeChar;
		fread( &shaderCodeChar, sizeof( char ), 1, shaderFile );
		shaderCode += shaderCodeChar;
	}
	shaderCode = std::string( shaderCode.begin(), shaderCode.end() - 1 );

	return shaderCode;
}


//-----------------------------------------------------------------------------------------------
std::string OpenGLShaderProgram::GetShaderCompileLog( int shader )
{
	int isCompiled = 0;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &isCompiled );
	if( isCompiled != GL_FALSE )
		return "";

	int maxLength = 0;
	glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );
	std::vector<char> infoLog(maxLength);
	glGetShaderInfoLog( shader, maxLength, &maxLength, &infoLog[0] );
	std::string infoLogString = std::string( infoLog.begin(), infoLog.end() );
	return infoLogString;
}


//-----------------------------------------------------------------------------------------------
std::string OpenGLShaderProgram::GetProgramLinkerLog( int program )
{
	int isLinked = 0;
	glGetProgramiv( program, GL_LINK_STATUS, &isLinked );
	if( isLinked != GL_FALSE )
		return "";

	int maxLength = 0;
	glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );
	std::vector<char> infoLog(maxLength);
	glGetProgramInfoLog( program, maxLength, &maxLength, &infoLog[0] );
	std::string infoLogString = std::string( infoLog.begin(), infoLog.end() );
	return infoLogString;
}


//-----------------------------------------------------------------------------------------------
void OpenGLShaderProgram::EditShaderErrorLog( std::string& infoLog, const std::string& shaderFileName )
{
	unsigned int fileNamePos = infoLog.find( "0(" );
	while( fileNamePos != std::string::npos )
	{
		infoLog.erase( fileNamePos, 1 );
		infoLog.insert( fileNamePos, shaderFileName );

		fileNamePos = infoLog.find( "0(" );
	}
}


//-----------------------------------------------------------------------------------------------
std::string OpenGLShaderProgram::GetCompileErrorText( const std::string& infoLog, const std::string& shaderFileName )
{
	std::string messageWindowText = "COMPILE ERROR OCCURRED\n\n";

	std::string fileName = GetShortenedFileName( shaderFileName );
	messageWindowText += "File Error(s) Occurred In:\n" + fileName + "\n\n";
	
	messageWindowText += "Error Info (Line):\n";
	std::string copyLog = infoLog;
	unsigned int errorStart = copyLog.find( '(' );
	while( errorStart != std::string::npos )
	{
		unsigned int errorEnd = copyLog.find( 10 );
		messageWindowText += copyLog.substr( errorStart, ( errorEnd - errorStart ) + 1 );
		copyLog.erase( copyLog.begin(), copyLog.begin() + errorEnd + 1 );
		errorStart = copyLog.find( '(' );
	}
	
	messageWindowText += "\nThe Program Will Now Close";
	return messageWindowText;
}


//-----------------------------------------------------------------------------------------------
std::string OpenGLShaderProgram::GetLinkerErrorText( const std::string& infoLog, const std::string& vertexFileName, const std::string& fragmentFileName )
{
	std::string messageWindowText = "LINKER ERROR OCCURRED\n\n";
	messageWindowText += "Failed to link vertex shader with fragment shader.\n\n";

	std::string shortVertexFileName = GetShortenedFileName( vertexFileName );
	messageWindowText += "Vertex Shader: " + shortVertexFileName + "\n";
	std::string shortFragmentFileName = GetShortenedFileName( fragmentFileName );
	messageWindowText += "Fragment Shader: " + shortFragmentFileName + "\n\n";

	messageWindowText += "Error Info:\n";
	std::string copyLog = infoLog;
	unsigned int errorStart = copyLog.find( '(' );
	if( errorStart != std::string::npos )
	{
		copyLog.erase( copyLog.begin(), copyLog.begin() + errorStart );
		copyLog.erase( copyLog.end() - 1 );
		messageWindowText += copyLog + "\n";
	}

	messageWindowText += "The Program Will Now Close";
	return messageWindowText;
}