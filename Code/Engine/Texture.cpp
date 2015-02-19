#include "Texture.hpp"
#include "EngineCommon.hpp"
#include "OpenGLRenderer.hpp"


//-----------------------------------------------------------------------------------------------
#define STBI_HEADER_FILE_ONLY
#include "stb_image.c"


//-----------------------------------------------------------------------------------------------
std::map< std::string, Texture* > Texture::s_textureRegistry;


//-----------------------------------------------------------------------------------------------
Texture::Texture( const std::string& imageFilePath )
	: m_openglTextureID( 0 )
	, m_size( 0, 0 )
{
	int numComponents = 0; // Filled in for us to indicate how many color/alpha components the image had (e.g. 3=RGB, 4=RGBA)
	int numComponentsRequested = 0; // don't care; we support 3 (RGB) or 4 (RGBA)
	unsigned char* imageData = stbi_load( imageFilePath.c_str(), &m_size.x, &m_size.y, &numComponents, numComponentsRequested );
	if( imageData == nullptr )
		return;

	// Enable texturing
	OpenGLRenderer::EnableTexture2D();

	// Tell OpenGL that our pixel data is single-byte aligned
	OpenGLRenderer::PixelStore();

	// Ask OpenGL for an unused texName (ID number) to use for this texture
	OpenGLRenderer::GenerateTextures( &m_openglTextureID );

	// Tell OpenGL to bind (set) this as the currently active texture
	OpenGLRenderer::BindTexture2D( m_openglTextureID );

	// Set texture clamp vs. wrap (repeat)
	OpenGLRenderer::SetTexture2DWrapS( REPEAT ); // GL_CLAMP or GL_REPEAT
	OpenGLRenderer::SetTexture2DWrapT( REPEAT ); // GL_CLAMP or GL_REPEAT

	// Set magnification (texel > pixel) and minification (texel < pixel) filters
	OpenGLRenderer::SetTexture2DMagnificationFilter( LINEAR ); // one of: GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_LINEAR
	OpenGLRenderer::SetTexture2DMinificationFilter( LINEAR_MIPMAP_LINEAR ); // one of: GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_LINEAR

	//OpenGLRenderer::SetTexture2DMaxLevel( 5 );

	pixelDataFormat bufferFormat = RGBA; // the format our source pixel data is currently in; any of: GL_RGB, GL_RGBA, GL_LUMINANCE, GL_LUMINANCE_ALPHA, ...
	if( numComponents == 1 )
		bufferFormat = LUMINANCE;
	else if( numComponents == 3 )
		bufferFormat = RGB;

	pixelDataFormat internalFormat = bufferFormat; // the format we want the texture to me on the card; allows us to translate into a different texture format as we upload to OpenGL

	OpenGLRenderer::SetTexture2DImage(	// Upload this pixel data to our new OpenGL texture
		0,							// Which mipmap level to use as the "root" (0 = the highest-quality, full-res image), if mipmaps are enabled
		internalFormat,				// Type of texel format we want OpenGL to use for this texture internally on the video card
		m_size.x,					// Texel-width of image; for maximum compatibility, use 2^N + 2^B, where N is some integer in the range [3,10], and B is the border thickness [0,1]
		m_size.y,					// Texel-height of image; for maximum compatibility, use 2^M + 2^B, where M is some integer in the range [3,10], and B is the border thickness [0,1]
		0,							// Border size, in texels (must be 0 or 1)
		bufferFormat,				// Pixel format describing the composition of the pixel data in buffer
		imageData );				// Location of the actual pixel data bytes/buffer

	OpenGLRenderer::GenerateMipmapHint();
	OpenGLRenderer::GenerateMipmapTexture2D();

	stbi_image_free( imageData );

	s_textureRegistry[ imageFilePath ] = this;
}


//-----------------------------------------------------------------------------------------------
STATIC void Texture::DeconstructTexture()
{
	s_textureRegistry.clear();
}


//-----------------------------------------------------------------------------------------------
STATIC Texture* Texture::GetTextureByName( const std::string& imageFilePath )
{
	std::map< std::string, Texture* >::iterator foundEntryIter;
	foundEntryIter = s_textureRegistry.find( imageFilePath );
	if( foundEntryIter == s_textureRegistry.end() )
	{
		return nullptr;
	}

	Texture* foundTexture = foundEntryIter->second;
	return foundTexture;
}


//-----------------------------------------------------------------------------------------------
STATIC Texture* Texture::CreateOrGetTexture( const std::string& imageFilePath )
{
	Texture* texture = GetTextureByName( imageFilePath );
	if( !texture )
	{
		texture = new Texture( imageFilePath );
	}

	return texture;
}