#ifndef include_Material
#define include_Material
#pragma once

//-----------------------------------------------------------------------------------------------
#include <map>
#include <string>
#include "Color.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "OpenGLRenderer.hpp"
#include "OpenGLShaderProgram.hpp"


//-----------------------------------------------------------------------------------------------
struct TextureInfo
{
	TextureInfo() {}
	TextureInfo( Texture* texture, int uniformLocation, textureUnit activeTextureLayer ) : m_texture( texture ), m_uniformLocation( uniformLocation ), m_activeTextureLayer( activeTextureLayer ) {}

	Texture*		m_texture;
	int				m_uniformLocation;
	textureUnit		m_activeTextureLayer;
};


//-----------------------------------------------------------------------------------------------
class Material
{
public:
	Material() {}
	Material( const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName );
	~Material();
	void Enable();
	void Disable();
	void AddTexture( Texture* texture, std::string textureUniformName, textureUnit activeTextureLayer );
	void SetUniform( const std::string& uniformName, int val );
	void SetUniform( const std::string& uniformName, bool isTrue );
	void SetUniform( const std::string& uniformName, float val );
	void SetUniform( const std::string& uniformName, const Vector2& vec );
	void SetUniform( const std::string& uniformName, const Vector3& vec );
	void SetUniform( const std::string& uniformName, const Vector4& vec );
	void SetUniform( const std::string& uniformName, const Color& color );
	unsigned int GetShaderProgramID();

private:
	void BindTextures();
	void UnbindTextures();
	int GetUniformLocation( const std::string& uniformName );
	void SendUniformValues();
	void SendAttribValues();
	void EnableAttribArrays();

	OpenGLShaderProgram*		m_glShaderProgram;
	std::vector<TextureInfo>	m_textures;
	std::map<std::string, int>	m_uniformLocationsByName;
};


#endif // include_Material