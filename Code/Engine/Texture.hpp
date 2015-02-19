#ifndef include_Texture
#define include_Texture
#pragma once

//-----------------------------------------------------------------------------------------------
#include <map>
#include <string>
#include "IntVector2.hpp"


//-----------------------------------------------------------------------------------------------
class Texture
{
public:
	Texture( const std::string& imageFilePath );
	static void DeconstructTexture();
	static Texture* GetTextureByName( const std::string& imageFilePath );
	static Texture* CreateOrGetTexture( const std::string& imageFilePath );
	static void SetTexMagFilterToLinear();
	static void SetTexMagFilterToNearest();

	unsigned int								m_openglTextureID;
	IntVector2									m_size;
	static std::map< std::string, Texture* >	s_textureRegistry;
};


#endif // include_Texture