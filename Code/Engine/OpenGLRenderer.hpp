#ifndef include_OpenGLRenderer
#define include_OpenGLRenderer
#pragma once

//-----------------------------------------------------------------------------------------------
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>
#include "Renderer.hpp"
#include "glext.h"
#include "Color.hpp"
#include "Vertex.hpp"
#include "Vector2.hpp"
#include "BitmapFont.hpp"
#include "MatrixStack44.hpp"


//-----------------------------------------------------------------------------------------------
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
extern PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;
extern PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;
extern PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM1FPROC glUniform1f;
extern PFNGLUNIFORM2FPROC glUniform2f;
extern PFNGLUNIFORM3FPROC glUniform3f;
extern PFNGLUNIFORM4FPROC glUniform4f;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLUSEPROGRAMPROC glUseProgram;


//-----------------------------------------------------------------------------------------------
class OpenGLRenderer
{
public:
	static void Initalize();
	static void PushMatrix();
	static void PopMatrix();
	static void EnableTexture2D();
	static void DisableTexture2D();
	static void SetActiveTexture( textureUnit texUnit );
	static void GenerateTextures( unsigned int* textures );
	static void SetTexture2DImage( int level, pixelDataFormat internalFormat, int width, int height, int border, pixelDataFormat bufferFormat, const void* pixels );
	static void BindTexture2D( unsigned int textureID );
	static void GenerateMipmapTexture2D();
	static void GenerateMipmapHint();
	static void PixelStore();
	static void Translatef( float translateX, float translateY, float translateZ );
	static void Rotatef( float angleDegree, float rotateX, float rotateY, float rotateZ );
	static void Scalef( float scaleX, float scaleY, float scaleZ );
	static void SetColor3f( float red, float green, float blue );
	static void SetColor4f( float red, float green, float blue, float alpha );
	static void SetLineWidth( float lineWidth );
	static void SetDepthMask( bool depthMaskOnOrOff );
	static void SetOrtho( float leftCoord, float rightCoord, float bottomCoord, float topCoord, float zNearDistance, float zFarDistance );
	static void SetPerspective( float fovyDegrees, float aspectRatio, float zNearDistance, float zFarDistance );
	static void BeginRender( renderType shape );
	static void EndRender();
	static void SetVertex2f( float vertX, float vertY );
	static void SetVertex3f( float vertX, float vertY, float vertZ );
	static void SetTexCoords2f( float coordX, float coordY );
	static void SetVBO( unsigned int* VBOid, const std::vector<Vertex>& vertices );
	static void LoadMatrix();
	static void RenderVertices( const std::vector<Vertex>& vertices, renderType shape );
	static void CreateColorFramebufferTexture2D( unsigned int* framebufferColorTexID, textureUnit texUnit, int textureWidth, int textureHeight );
	static void CreateDepthFramebufferTexture2D( unsigned int* framebufferDepthTexID, textureUnit texUnit, int textureWidth, int textureHeight );
	static void SetFBO( unsigned int* FBOid, unsigned int framebufferColorTexID, unsigned int framebufferDepthTexID );
	static void BindFramebuffer( unsigned int FBOid );
	static void DisableFramebuffer();
	static void MultMatrixf( const float* mat );
	static void GenerateBuffers( int size, unsigned int* buffers );
	static void DeleteBuffers( int size, unsigned int* buffers );
	static void BindBuffer( unsigned int buffer );
	static void SetBufferData( int size, const void* data );
	static void EnableClientState( arrayType aType );
	static void DisableClientState( arrayType aType );
	static void DrawArrays( renderType shape, int first, unsigned int count );
	static void EnableCullFace();
	static void CullFrontFaceDirection( frontFaceDirection dirForFontFace );
	static void CullFaceSide( faceSide frontOrBack );
	static void ClearColorBufferBit();
	static void ClearDepthBufferBit();
	static void SetClearColor( float red, float green, float blue, float alpha );
	static void SetClearDepth( float depth );
	static void EnableBlend();
	static void EnableDepthTest();
	static void DisableDepthTest();
	static void BlendFunction(  blendFuncParam sFactor, blendFuncParam dFactor  );
	static void SetTexture2DWrapS( textureWrap clampOrRepeat );
	static void SetTexture2DWrapT( textureWrap clampOrRepeat );
	static void SetTexture2DMagnificationFilter( textureFilter filter );
	static void SetTexture2DMinificationFilter( textureFilter filter );
	static void SetTexture2DMaxLevel( int param );
	static void UseShaderProgram( unsigned int shaderProgramID );
	static int GetUniformLocation( unsigned int shaderProgramID, const char* name );
	static void SetUniform1i( int uniformLocation, int val );
	static void SetUniform1f( int uniformLocation, float val );
	static void SetUniform2f( int uniformLocation, float val0, float val1 );
	static void SetUniform3f( int uniformLocation, float val0, float val1, float val2 );
	static void SetUniform4f( int uniformLocation, float val0, float val1, float val2, float val3 );
	static void SetModelViewProjectionMatrix( int uniformLocation );
	static void SetPositionAttribPointer( int attribLocation );
	static void SetColorAttribPointer( int attribLocation );
	static void SetTexCoordAttribPointer( int attribLocation );
	static void SetNormalAttribPointer( int attribLocation );
	static void SetTangentAttribPointer( int attribLocation );
	static void EnableAttribArray( int attribLocation );
	static void DisableAttribArray( int attribLocation );
	static void RenderText( char textChar, const BitmapFont& font, float fontCellHeight, const Vector2& screenPos );
	static void RenderText( char textChar, const BitmapFont& font, float fontCellHeight, const Vector2& screenPos, const Color& color );
	static void RenderText( const std::string& text, const BitmapFont& font, float fontCellHeight, const Vector2& screenPos );
	static void RenderText( const std::string& text, const BitmapFont& font, float fontCellHeight, const Vector2& screenPos, const Color& color );
	static void SetTextVertices( std::vector<Vertex>& vertices, const std::string& text, const BitmapFont& font, float fontCellHeight, const Vector2& screenPos );
	static void SetTextVertices( std::vector<Vertex>& vertices, const std::string& text, const BitmapFont& font, float fontCellHeight, const Vector2& screenPos, const Color& color );
	static float CalcTextWidth( char textChar, const BitmapFont& font, float fontCellHeight );
	static float CalcTextWidth( const std::string& text, const BitmapFont& font, float fontCellHeight );

private:
	static int GetBlendParameter( blendFuncParam param );

	static MatrixStack44	s_matrixStack;
};


#endif // include_OpenGLRenderer