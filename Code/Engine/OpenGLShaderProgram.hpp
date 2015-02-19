#ifndef include_OpenGLShaderProgram
#define include_OpenGLShaderProgram
#pragma once

//-----------------------------------------------------------------------------------------------
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <string>
#include "glext.h"


//-----------------------------------------------------------------------------------------------
enum
{
	VERTEX_ATTRIB_POSITIONS = 1,
	VERTEX_ATTRIB_COLORS,
	VERTEX_ATTRIB_TEX_COORDS,
	VERTEX_ATTRIB_NORMALS,
	VERTEX_ATTRIB_TANGENTS,
};


//-----------------------------------------------------------------------------------------------
class OpenGLShaderProgram
{
public:
	OpenGLShaderProgram() {}
	OpenGLShaderProgram( const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName );
	~OpenGLShaderProgram();

	unsigned int	m_programID;
	int				m_modelViewProjectionMatUniformLocation;

private:
	void CreateProgram( const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName );
	unsigned int CreateShader( int shaderType, const std::string& shaderFileName );
	void BindAttribLocations();
	std::string GetShaderCode( const std::string& shaderFileName );
	std::string GetShaderCompileLog( int shader );
	std::string GetProgramLinkerLog( int program );
	void EditShaderErrorLog( std::string& infoLog, const std::string& shaderFileName );
	std::string GetCompileErrorText( const std::string& infoLog, const std::string& shaderFileName );
	std::string GetLinkerErrorText( const std::string& infoLog, const std::string& vertexFileName, const std::string& fragmentFileName );

	unsigned int	m_vertexShaderID;
	unsigned int	m_fragmentShaderID;
};


#endif // include_OpenGLShaderProgram