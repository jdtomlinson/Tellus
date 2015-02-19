#include "Material.hpp"


//-----------------------------------------------------------------------------------------------
Material::Material( const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName )
{
	m_glShaderProgram = new OpenGLShaderProgram( vertexShaderFileName, fragmentShaderFileName );
}


//-----------------------------------------------------------------------------------------------
Material::~Material()
{
	delete m_glShaderProgram;
}


//-----------------------------------------------------------------------------------------------
void Material::Enable()
{
	OpenGLRenderer::UseShaderProgram( m_glShaderProgram->m_programID );

	BindTextures();
	SendUniformValues();
	SendAttribValues();
	EnableAttribArrays();
}


//-----------------------------------------------------------------------------------------------
void Material::Disable()
{
	OpenGLRenderer::UseShaderProgram( 0 );
	UnbindTextures();

	OpenGLRenderer::DisableAttribArray( VERTEX_ATTRIB_POSITIONS );
	OpenGLRenderer::DisableAttribArray( VERTEX_ATTRIB_COLORS );
	OpenGLRenderer::DisableAttribArray( VERTEX_ATTRIB_TEX_COORDS );
	OpenGLRenderer::DisableAttribArray( VERTEX_ATTRIB_NORMALS );
	OpenGLRenderer::DisableAttribArray( VERTEX_ATTRIB_TANGENTS );
}


//-----------------------------------------------------------------------------------------------
void Material::AddTexture( Texture* texture, std::string textureUniformName, textureUnit activeTextureLayer )
{
	int uniformLocation = OpenGLRenderer::GetUniformLocation( m_glShaderProgram->m_programID, textureUniformName.c_str() );
	TextureInfo textureInfo( texture, uniformLocation, activeTextureLayer );
	m_textures.push_back( textureInfo );
}


//-----------------------------------------------------------------------------------------------
void Material::SetUniform( const std::string& uniformName, int val )
{
	int uniformLocation = GetUniformLocation( uniformName );
	OpenGLRenderer::SetUniform1i( uniformLocation, val );
}


//-----------------------------------------------------------------------------------------------
void Material::SetUniform( const std::string& uniformName, bool isTrue )
{
	int uniformLocation = GetUniformLocation( uniformName );

	if( isTrue )
		OpenGLRenderer::SetUniform1i( uniformLocation, 1 );
	else
		OpenGLRenderer::SetUniform1i( uniformLocation, 0 );
}


//-----------------------------------------------------------------------------------------------
void Material::SetUniform( const std::string& uniformName, float val )
{
	int uniformLocation = GetUniformLocation( uniformName );
	OpenGLRenderer::SetUniform1f( uniformLocation, val );
}


//-----------------------------------------------------------------------------------------------
void Material::SetUniform( const std::string& uniformName, const Vector2& vec )
{
	int uniformLocation = GetUniformLocation( uniformName );
	OpenGLRenderer::SetUniform2f( uniformLocation, vec.x, vec.y );
}


//-----------------------------------------------------------------------------------------------
void Material::SetUniform( const std::string& uniformName, const Vector3& vec )
{
	int uniformLocation = GetUniformLocation( uniformName );
	OpenGLRenderer::SetUniform3f( uniformLocation, vec.x, vec.y, vec.z );
}


//-----------------------------------------------------------------------------------------------
void Material::SetUniform( const std::string& uniformName, const Vector4& vec )
{
	int uniformLocation = GetUniformLocation( uniformName );
	OpenGLRenderer::SetUniform4f( uniformLocation, vec.x, vec.y, vec.z, vec.w );
}


//-----------------------------------------------------------------------------------------------
void Material::SetUniform( const std::string& uniformName, const Color& color )
{
	int uniformLocation = GetUniformLocation( uniformName );
	OpenGLRenderer::SetUniform4f( uniformLocation, color.r, color.g, color.b, color.a );
}


//-----------------------------------------------------------------------------------------------
unsigned int Material::GetShaderProgramID()
{
	return m_glShaderProgram->m_programID;
}


//-----------------------------------------------------------------------------------------------
void Material::BindTextures()
{
	for( unsigned int textureInfoIndex = 0; textureInfoIndex < m_textures.size(); ++textureInfoIndex )
	{
		TextureInfo textureInfo = m_textures[ textureInfoIndex ];
		if( textureInfo.m_texture != nullptr )
		{
			OpenGLRenderer::SetActiveTexture( textureInfo.m_activeTextureLayer );
			OpenGLRenderer::BindTexture2D( textureInfo.m_texture->m_openglTextureID );
			OpenGLRenderer::SetUniform1i( textureInfo.m_uniformLocation, textureInfo.m_activeTextureLayer );
		}
		/*else
		{
			OpenGLRenderer::BindTexture2D( 0 );
		}*/
	}
}


//-----------------------------------------------------------------------------------------------
void Material::UnbindTextures()
{
	for( unsigned int textureInfoIndex = 0; textureInfoIndex < m_textures.size(); ++textureInfoIndex )
	{
		TextureInfo textureInfo = m_textures[ textureInfoIndex ];
		OpenGLRenderer::SetActiveTexture( textureInfo.m_activeTextureLayer );
		OpenGLRenderer::BindTexture2D( 0 );
	}

	OpenGLRenderer::SetActiveTexture( TEXTURE0 );
}


//-----------------------------------------------------------------------------------------------
int Material::GetUniformLocation( const std::string& uniformName )
{
	std::map<std::string, int>::iterator mapIter;
	mapIter = m_uniformLocationsByName.find( uniformName );
	if( mapIter != m_uniformLocationsByName.end() )
		return mapIter->second;

	int uniformLocation = OpenGLRenderer::GetUniformLocation( m_glShaderProgram->m_programID, uniformName.c_str() );
	m_uniformLocationsByName.insert( std::pair<std::string, int>( uniformName, uniformLocation ) );
	return uniformLocation;
}


//-----------------------------------------------------------------------------------------------
void Material::SendUniformValues()
{
	OpenGLRenderer::SetModelViewProjectionMatrix( m_glShaderProgram->m_modelViewProjectionMatUniformLocation );
}


//-----------------------------------------------------------------------------------------------
void Material::SendAttribValues()
{
	OpenGLRenderer::SetPositionAttribPointer( VERTEX_ATTRIB_POSITIONS );
	OpenGLRenderer::SetColorAttribPointer( VERTEX_ATTRIB_COLORS );
	OpenGLRenderer::SetTexCoordAttribPointer( VERTEX_ATTRIB_TEX_COORDS );
	OpenGLRenderer::SetNormalAttribPointer( VERTEX_ATTRIB_NORMALS );
	OpenGLRenderer::SetTangentAttribPointer( VERTEX_ATTRIB_TANGENTS );
}


//-----------------------------------------------------------------------------------------------
void Material::EnableAttribArrays()
{
	OpenGLRenderer::EnableAttribArray( VERTEX_ATTRIB_POSITIONS );
	OpenGLRenderer::EnableAttribArray( VERTEX_ATTRIB_COLORS );
	OpenGLRenderer::EnableAttribArray( VERTEX_ATTRIB_TEX_COORDS );
	OpenGLRenderer::EnableAttribArray( VERTEX_ATTRIB_NORMALS );
	OpenGLRenderer::EnableAttribArray( VERTEX_ATTRIB_TANGENTS );
}