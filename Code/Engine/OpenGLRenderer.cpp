#include "OpenGLRenderer.hpp"
#include <vector>
#include "EngineCommon.hpp"


//-----------------------------------------------------------------------------------------------
PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
PFNGLBUFFERDATAPROC glBufferData = nullptr;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;
PFNGLACTIVETEXTUREPROC glActiveTexture = nullptr;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = nullptr;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = nullptr;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = nullptr;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = nullptr;
PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = nullptr;
PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = nullptr;
PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = nullptr;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = nullptr;
PFNGLUNIFORM1IPROC glUniform1i = nullptr;
PFNGLUNIFORM1FPROC glUniform1f = nullptr;
PFNGLUNIFORM2FPROC glUniform2f = nullptr;
PFNGLUNIFORM3FPROC glUniform3f = nullptr;
PFNGLUNIFORM4FPROC glUniform4f = nullptr;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;
PFNGLCREATESHADERPROC glCreateShader = nullptr;
PFNGLDELETESHADERPROC glDeleteShader = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
PFNGLATTACHSHADERPROC glAttachShader = nullptr;
PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
PFNGLUSEPROGRAMPROC glUseProgram = nullptr;


//-----------------------------------------------------------------------------------------------
MatrixStack44 OpenGLRenderer::s_matrixStack;


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::Initalize()
{
	glGenBuffers = (PFNGLGENBUFFERSPROC) wglGetProcAddress( "glGenBuffers" );
	glBindBuffer = (PFNGLBINDBUFFERPROC) wglGetProcAddress( "glBindBuffer" );
	glBufferData = (PFNGLBUFFERDATAPROC) wglGetProcAddress( "glBufferData" );
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) wglGetProcAddress( "glDeleteBuffers" );
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) wglGetProcAddress( "glVertexAttribPointer" );
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) wglGetProcAddress( "glEnableVertexAttribArray" );
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) wglGetProcAddress( "glDisableVertexAttribArray" );
	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress( "glGenerateMipmap" );
	glActiveTexture = (PFNGLACTIVETEXTUREPROC) wglGetProcAddress( "glActiveTexture" );
	glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress( "glGenFramebuffers" );
	glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress( "glBindFramebuffer" );
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) wglGetProcAddress( "glGetAttribLocation" );
	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC) wglGetProcAddress( "glBindAttribLocation" );
	glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress( "glFramebufferTexture2D" );
	glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC) wglGetProcAddress( "glVertexAttrib2fv" );
	glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC) wglGetProcAddress( "glVertexAttrib3fv" );
	glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC) wglGetProcAddress( "glVertexAttrib4fv" );
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress( "glGetUniformLocation" );
	glUniform1i = (PFNGLUNIFORM1IPROC) wglGetProcAddress( "glUniform1i" );
	glUniform1f = (PFNGLUNIFORM1FPROC) wglGetProcAddress( "glUniform1f" );
	glUniform2f = (PFNGLUNIFORM2FPROC) wglGetProcAddress( "glUniform2f" );
	glUniform3f = (PFNGLUNIFORM3FPROC) wglGetProcAddress( "glUniform3f" );
	glUniform4f = (PFNGLUNIFORM4FPROC) wglGetProcAddress( "glUniform4f" );
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) wglGetProcAddress( "glUniformMatrix4fv" );
	glCreateShader = (PFNGLCREATESHADERPROC) wglGetProcAddress( "glCreateShader" );
	glDeleteShader = (PFNGLDELETESHADERPROC) wglGetProcAddress( "glDeleteShader" );
	glShaderSource = (PFNGLSHADERSOURCEPROC) wglGetProcAddress( "glShaderSource" );
	glCompileShader = (PFNGLCOMPILESHADERPROC) wglGetProcAddress( "glCompileShader" );
	glGetShaderiv = (PFNGLGETSHADERIVPROC) wglGetProcAddress( "glGetShaderiv" );
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) wglGetProcAddress( "glGetShaderInfoLog" );
	glCreateProgram = (PFNGLCREATEPROGRAMPROC) wglGetProcAddress( "glCreateProgram" );
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC) wglGetProcAddress( "glDeleteProgram" );
	glAttachShader = (PFNGLATTACHSHADERPROC) wglGetProcAddress( "glAttachShader" );
	glLinkProgram = (PFNGLLINKPROGRAMPROC) wglGetProcAddress( "glLinkProgram" );
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC) wglGetProcAddress( "glGetProgramiv" );
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) wglGetProcAddress( "glGetProgramInfoLog" );
	glUseProgram = (PFNGLUSEPROGRAMPROC) wglGetProcAddress( "glUseProgram" );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::PushMatrix()
{
	s_matrixStack.PushMatrix();
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::PopMatrix()
{
	s_matrixStack.PopMatrix();
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::EnableTexture2D()
{
	glEnable( GL_TEXTURE_2D );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::DisableTexture2D()
{
	glDisable( GL_TEXTURE_2D );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetActiveTexture( textureUnit texUnit )
{
	if( texUnit == TEXTURE0 )
		glActiveTexture( GL_TEXTURE0 );
	else if( texUnit == TEXTURE1 )
		glActiveTexture( GL_TEXTURE1 );
	else if( texUnit == TEXTURE2 )
		glActiveTexture( GL_TEXTURE2 );
	else if( texUnit == TEXTURE3 )
		glActiveTexture( GL_TEXTURE3 );
	else if( texUnit == TEXTURE4 )
		glActiveTexture( GL_TEXTURE4 );
	else if( texUnit == TEXTURE5 )
		glActiveTexture( GL_TEXTURE5 );
	else if( texUnit == TEXTURE6 )
		glActiveTexture( GL_TEXTURE6 );
	else if( texUnit == TEXTURE7 )
		glActiveTexture( GL_TEXTURE7 );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::GenerateTextures( unsigned int* textures )
{
	glGenTextures( 1, textures );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetTexture2DImage( int level, pixelDataFormat internalFormat, int width, int height, int border, pixelDataFormat bufferFormat, const void* pixels )
{
	GLenum interForm = RGB;
	GLenum buffForm = RGB;

	if( internalFormat == LUMINANCE )
		interForm = GL_LUMINANCE;
	else if( internalFormat == RGB )
		interForm = GL_RGB;
	else if( internalFormat == RGBA )
		interForm = GL_RGBA;

	if( bufferFormat == LUMINANCE )
		buffForm = GL_LUMINANCE;
	else if( bufferFormat == RGB )
		buffForm = GL_RGB;
	else if( bufferFormat == RGBA )
		buffForm = GL_RGBA;

	glTexImage2D( GL_TEXTURE_2D, level, interForm, width, height, border, buffForm, GL_UNSIGNED_BYTE, pixels );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::BindTexture2D( unsigned int textureID )
{
	glBindTexture( GL_TEXTURE_2D, textureID );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::GenerateMipmapTexture2D()
{
	glGenerateMipmap( GL_TEXTURE_2D );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::GenerateMipmapHint()
{
	glHint( GL_GENERATE_MIPMAP_HINT, GL_NICEST );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::PixelStore()
{
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::Translatef( float translateX, float translateY, float translateZ )
{
	s_matrixStack.ApplyTranslation( translateX, translateY, translateZ );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::Rotatef( float angleDegree, float rotateX, float rotateY, float rotateZ )
{
	s_matrixStack.ApplyRotation( angleDegree, rotateX, rotateY, rotateZ );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::Scalef( float scaleX, float scaleY, float scaleZ )
{
	s_matrixStack.ApplyScale( scaleX, scaleY, scaleZ );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetColor3f( float red, float green, float blue )
{
	glColor3f( red, green, blue );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetColor4f( float red, float green, float blue, float alpha )
{
	glColor4f( red, green, blue, alpha );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetLineWidth( float lineWidth )
{
	glLineWidth( lineWidth );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetDepthMask( bool depthMaskOnOrOff )
{
	if( depthMaskOnOrOff )
		glDepthMask( GL_TRUE );
	else
		glDepthMask( GL_FALSE );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetOrtho( float leftCoord, float rightCoord, float bottomCoord, float topCoord, float zNearDistance, float zFarDistance )
{
	s_matrixStack.ApplyOrtho( leftCoord, rightCoord, bottomCoord, topCoord, zNearDistance, zFarDistance );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetPerspective( float fovyDegrees, float aspectRatio, float zNearDistance, float zFarDistance )
{
	s_matrixStack.ApplyPerspective( fovyDegrees, aspectRatio, zNearDistance, zFarDistance );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::BeginRender( renderType shape )
{
	LoadMatrix();

	if( shape == LINES )
		glBegin( GL_LINES );
	else if( shape == TRIANGLES )
		glBegin( GL_TRIANGLES );
	else if( shape == QUADS )
		glBegin( GL_QUADS );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::EndRender()
{
	glEnd();
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetVertex2f( float vertX, float vertY )
{
	glVertex2f( vertX, vertY );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetVertex3f( float vertX, float vertY, float vertZ )
{
	glVertex3f( vertX, vertY, vertZ );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetTexCoords2f( float coordX, float coordY )
{
	glTexCoord2f( coordX, coordY );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetVBO( unsigned int* VBOid, const std::vector<Vertex>& vertices )
{
	if( vertices.size() == 0 )
		return;

	glDeleteBuffers( 1, VBOid );

	glGenBuffers( 1, VBOid );
	glBindBuffer( GL_ARRAY_BUFFER, *VBOid );
	glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( Vertex ), &vertices.front(), GL_STATIC_DRAW );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::LoadMatrix()
{
	glLoadMatrixf( s_matrixStack.GetCurrentMatrix().m_entries );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::RenderVertices( const std::vector<Vertex>& vertices, renderType shape )
{
	glEnable( GL_CULL_FACE );
	glFrontFace( GL_CCW );
	glCullFace( GL_BACK );

	DrawArrays( shape, 0, vertices.size() );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::CreateColorFramebufferTexture2D( unsigned int* framebufferColorTexID, textureUnit texUnit, int textureWidth, int textureHeight )
{
	SetActiveTexture( texUnit );
	glGenTextures( 1, framebufferColorTexID );
	glBindTexture( GL_TEXTURE_2D, *framebufferColorTexID );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::CreateDepthFramebufferTexture2D( unsigned int* framebufferDepthTexID, textureUnit texUnit, int textureWidth, int textureHeight )
{
	SetActiveTexture( texUnit );
	glGenTextures( 1, framebufferDepthTexID );
	glBindTexture( GL_TEXTURE_2D, *framebufferDepthTexID );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, textureWidth, textureHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetFBO( unsigned int* FBOid, unsigned int framebufferColorTexID, unsigned int framebufferDepthTexID )
{
	glGenFramebuffers( 1, FBOid );
	glBindFramebuffer( GL_FRAMEBUFFER, *FBOid );

	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferColorTexID, 0 );
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, framebufferDepthTexID, 0);
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::BindFramebuffer( unsigned int FBOid )
{
	glBindFramebuffer( GL_FRAMEBUFFER, FBOid );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::DisableFramebuffer()
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::MultMatrixf( const float* mat )
{
	glMultMatrixf( mat );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::GenerateBuffers( int size, unsigned int* buffers )
{
	glGenBuffers( size, buffers );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::DeleteBuffers( int size, unsigned int* buffers )
{
	glDeleteBuffers( size, buffers );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::BindBuffer( unsigned int buffer )
{
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetBufferData( int size, const void* data )
{
	glBufferData( GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::EnableClientState( arrayType aType )
{
	if( aType == VERTEX_ARRAY )
		glEnableClientState( GL_VERTEX_ARRAY );
	else if( aType == COLOR_ARRAY )
		glEnableClientState( GL_COLOR_ARRAY );
	else if( aType == TEXTURE_COORD_ARRAY )
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	else if( aType == NORMAL_ARRAY )
		glEnableClientState( GL_NORMAL_ARRAY );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::DisableClientState( arrayType aType )
{
	if( aType == VERTEX_ARRAY )
		glDisableClientState( GL_VERTEX_ARRAY );
	else if( aType == COLOR_ARRAY )
		glDisableClientState( GL_COLOR_ARRAY );
	else if( aType == TEXTURE_COORD_ARRAY )
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	else if( aType == NORMAL_ARRAY )
		glDisableClientState( GL_NORMAL_ARRAY );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::DrawArrays( renderType shape, int first, unsigned int count )
{
	if( shape == LINES )
		glDrawArrays( GL_LINES, first, count );
	else if( shape == TRIANGLES )
		glDrawArrays( GL_TRIANGLES, first, count );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::EnableCullFace()
{
	glEnable( GL_CULL_FACE );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::CullFrontFaceDirection( frontFaceDirection dirForFrontFace )
{
	if( dirForFrontFace == CLOCKWISE )
		glFrontFace( GL_CW );
	else if( dirForFrontFace == COUNTER_CLOCKWISE )
		glFrontFace( GL_CCW );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::CullFaceSide( faceSide frontOrBack )
{
	if( frontOrBack == FRONT )
		glCullFace( GL_FRONT );
	else if( frontOrBack == BACK )
		glCullFace( GL_BACK );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::ClearColorBufferBit()
{
	glClear( GL_COLOR_BUFFER_BIT );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::ClearDepthBufferBit()
{
	glClear( GL_DEPTH_BUFFER_BIT );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetClearColor( float red, float green, float blue, float alpha )
{
	glClearColor( red, green, blue, alpha );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetClearDepth( float depth )
{
	glClearDepth( depth );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::EnableBlend()
{
	glEnable( GL_BLEND );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::EnableDepthTest()
{
	glEnable( GL_DEPTH_TEST );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::DisableDepthTest()
{
	glDisable( GL_DEPTH_TEST );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::BlendFunction( blendFuncParam sFactor, blendFuncParam dFactor )
{
	int sFact = GetBlendParameter( sFactor );
	int dFact = GetBlendParameter( dFactor );

	glBlendFunc( sFact, dFact );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetTexture2DWrapS( textureWrap clampOrRepeat )
{
	if( clampOrRepeat == CLAMP )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	else if( clampOrRepeat == REPEAT )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetTexture2DWrapT( textureWrap clampOrRepeat )
{
	if( clampOrRepeat == CLAMP )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	else if( clampOrRepeat == REPEAT )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetTexture2DMagnificationFilter( textureFilter filter )
{
	if( filter == NEAREST )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	else if( filter == LINEAR )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	else if( filter == NEAREST_MIPMAP_NEAREST )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST );
	else if( filter == NEAREST_MIPMAP_LINEAR )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR );
	else if( filter == LINEAR_MIPMAP_NEAREST )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST );
	else if( filter == LINEAR_MIPMAP_LINEAR )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetTexture2DMinificationFilter( textureFilter filter )
{
	if( filter == NEAREST )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	else if( filter == LINEAR )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	else if( filter == NEAREST_MIPMAP_NEAREST )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );
	else if( filter == NEAREST_MIPMAP_LINEAR )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR );
	else if( filter == LINEAR_MIPMAP_NEAREST )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
	else if( filter == LINEAR_MIPMAP_LINEAR )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetTexture2DMaxLevel( int param )
{
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, param );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::UseShaderProgram( unsigned int shaderProgramID )
{
	glUseProgram( shaderProgramID );
}


//-----------------------------------------------------------------------------------------------
STATIC int OpenGLRenderer::GetUniformLocation( unsigned int shaderProgramID, const char* name )
{
	return glGetUniformLocation( shaderProgramID, name );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetUniform1i( int uniformLocation, int val )
{
	glUniform1i( uniformLocation, val );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetUniform1f( int uniformLocation, float val )
{
	glUniform1f( uniformLocation, val );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetUniform2f( int uniformLocation, float val0, float val1 )
{
	glUniform2f( uniformLocation, val0, val1 );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetUniform3f( int uniformLocation, float val0, float val1, float val2 )
{
	glUniform3f( uniformLocation, val0, val1, val2 );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetUniform4f( int uniformLocation, float val0, float val1, float val2, float val3 )
{
	glUniform4f( uniformLocation, val0, val1, val2, val3 );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetModelViewProjectionMatrix( int uniformLocation )
{
	glUniformMatrix4fv( uniformLocation, 1, GL_FALSE, s_matrixStack.GetCurrentMatrix().m_entries );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetPositionAttribPointer( int attribLocation )
{
	glVertexAttribPointer( attribLocation, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (float*) offsetof( Vertex, m_position ) );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetColorAttribPointer( int attribLocation )
{
	glVertexAttribPointer( attribLocation, 4, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (float*) offsetof( Vertex, m_color ) );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetTexCoordAttribPointer( int attribLocation )
{
	glVertexAttribPointer( attribLocation, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (float*) offsetof( Vertex, m_texCoords ) );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetNormalAttribPointer( int attribLocation )
{
	glVertexAttribPointer( attribLocation, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (float*) offsetof( Vertex, m_normal ) );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetTangentAttribPointer( int attribLocation )
{
	glVertexAttribPointer( attribLocation, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (float*) offsetof( Vertex, m_tangent ) );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::EnableAttribArray( int attribLocation )
{
	glEnableVertexAttribArray( attribLocation );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::DisableAttribArray( int attribLocation )
{
	glDisableVertexAttribArray( attribLocation );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::RenderText( char textChar, const BitmapFont& font, float fontCellHeight, const Vector2& screenPos )
{
	RenderText( textChar, font, fontCellHeight, screenPos, Color( 1.f, 1.f, 1.f, 1.f ) );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::RenderText( char textChar, const BitmapFont& font, float fontCellHeight, const Vector2& screenPos, const Color& color )
{
	glColor4f( color.r, color.g, color.b, color.a );
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, font.m_glyphSheet->m_openglTextureID );

	glBegin( GL_QUADS );
	{
		Glyph glyph = font.m_glyphData[ textChar ];
		Vector2 bottomLeftCoords( screenPos.x + fontCellHeight * glyph.m_ttfA, screenPos.y );
		Vector2 topRightCoords( screenPos.x + fontCellHeight * ( glyph.m_ttfA + glyph.m_ttfB ), screenPos.y + fontCellHeight );

		glTexCoord2f( glyph.m_texCoordMins.x, glyph.m_texCoordMaxs.y );
		glVertex2f( bottomLeftCoords.x, bottomLeftCoords.y );

		glTexCoord2f( glyph.m_texCoordMaxs.x, glyph.m_texCoordMaxs.y );
		glVertex2f( topRightCoords.x, bottomLeftCoords.y );

		glTexCoord2f( glyph.m_texCoordMaxs.x, glyph.m_texCoordMins.y );
		glVertex2f( topRightCoords.x, topRightCoords.y );

		glTexCoord2f( glyph.m_texCoordMins.x, glyph.m_texCoordMins.y );
		glVertex2f( bottomLeftCoords.x, topRightCoords.y );
	}
	glEnd();

	glDisable( GL_TEXTURE_2D );
	glColor4f( 1.f, 1.f, 1.f, 1.f );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::RenderText( const std::string& text, const BitmapFont& font, float fontCellHeight, const Vector2& screenPos )
{
	RenderText( text, font, fontCellHeight, screenPos, Color( 1.f, 1.f, 1.f, 1.f ) );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::RenderText( const std::string& text, const BitmapFont& font, float fontCellHeight, const Vector2& screenPos, const Color& color )
{
	float bottomLeftCoordX = screenPos.x;

	glColor4f( color.r, color.g, color.b, color.a );
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, font.m_glyphSheet->m_openglTextureID );

	glBegin( GL_QUADS );
	{
		for( unsigned int charIndex = 0; charIndex < text.size(); ++charIndex )
		{
			unsigned char textChar = text[ charIndex ];
			Glyph glyph = font.m_glyphData[ textChar ];
			Vector2 bottomLeftCoords( bottomLeftCoordX + fontCellHeight * glyph.m_ttfA, screenPos.y );
			Vector2 topRightCoords( bottomLeftCoordX + fontCellHeight * ( glyph.m_ttfA + glyph.m_ttfB ), screenPos.y + fontCellHeight );

			glTexCoord2f( glyph.m_texCoordMins.x, glyph.m_texCoordMaxs.y );
			glVertex2f( bottomLeftCoords.x, bottomLeftCoords.y );

			glTexCoord2f( glyph.m_texCoordMaxs.x, glyph.m_texCoordMaxs.y );
			glVertex2f( topRightCoords.x, bottomLeftCoords.y );

			glTexCoord2f( glyph.m_texCoordMaxs.x, glyph.m_texCoordMins.y );
			glVertex2f( topRightCoords.x, topRightCoords.y );

			glTexCoord2f( glyph.m_texCoordMins.x, glyph.m_texCoordMins.y );
			glVertex2f( bottomLeftCoords.x, topRightCoords.y );

			bottomLeftCoordX += fontCellHeight * ( glyph.m_ttfA + glyph.m_ttfB + glyph.m_ttfC );
		}
	}
	glEnd();

	glDisable( GL_TEXTURE_2D );
	glColor4f( 1.f, 1.f, 1.f, 1.f );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetTextVertices( std::vector<Vertex>& vertices, const std::string& text, const BitmapFont& font, float fontCellHeight, const Vector2& screenPos )
{
	SetTextVertices( vertices, text, font, fontCellHeight, screenPos, Color( 1.f, 1.f, 1.f, 1.f ) );
}


//-----------------------------------------------------------------------------------------------
STATIC void OpenGLRenderer::SetTextVertices( std::vector<Vertex>& vertices, const std::string& text, const BitmapFont& font, float fontCellHeight, const Vector2& screenPos, const Color& color )
{
	float bottomLeftCoordX = screenPos.x;

	for( unsigned int charIndex = 0; charIndex < text.size(); ++charIndex )
	{
		Glyph glyph = font.m_glyphData[ text[ charIndex ] ];
		Vector2 bottomLeftCoords( bottomLeftCoordX + fontCellHeight * glyph.m_ttfA, screenPos.y );
		Vector2 topRightCoords( bottomLeftCoordX + fontCellHeight * ( glyph.m_ttfA + glyph.m_ttfB ), screenPos.y + fontCellHeight );

		vertices.push_back( Vertex( Vector3( bottomLeftCoords.x, bottomLeftCoords.y, 0.f ), color, Vector2( glyph.m_texCoordMins.x, glyph.m_texCoordMaxs.y ), Vector3( 0.f, 0.f, 0.f ) ) );
		vertices.push_back( Vertex( Vector3( topRightCoords.x, bottomLeftCoords.y, 0.f ), color, Vector2( glyph.m_texCoordMaxs.x, glyph.m_texCoordMaxs.y ), Vector3( 0.f, 0.f, 0.f ) ) );
		vertices.push_back( Vertex( Vector3( bottomLeftCoords.x, topRightCoords.y, 0.f ), color, Vector2( glyph.m_texCoordMins.x, glyph.m_texCoordMins.y ), Vector3( 0.f, 0.f, 0.f ) ) );

		vertices.push_back( Vertex( Vector3( topRightCoords.x, topRightCoords.y, 0.f ), color, Vector2( glyph.m_texCoordMaxs.x, glyph.m_texCoordMins.y ), Vector3( 0.f, 0.f, 0.f ) ) );
		vertices.push_back( Vertex( Vector3( bottomLeftCoords.x, topRightCoords.y, 0.f ), color, Vector2( glyph.m_texCoordMins.x, glyph.m_texCoordMins.y ), Vector3( 0.f, 0.f, 0.f ) ) );
		vertices.push_back( Vertex( Vector3( topRightCoords.x, bottomLeftCoords.y, 0.f ), color, Vector2( glyph.m_texCoordMaxs.x, glyph.m_texCoordMaxs.y ), Vector3( 0.f, 0.f, 0.f ) ) );

		bottomLeftCoordX += fontCellHeight * ( glyph.m_ttfA + glyph.m_ttfB + glyph.m_ttfC );
	}
}


//-----------------------------------------------------------------------------------------------
STATIC float OpenGLRenderer::CalcTextWidth( char textChar, const BitmapFont& font, float fontCellHeight )
{
	Glyph glyph = font.m_glyphData[ textChar ];
	return fontCellHeight * ( glyph.m_ttfA + glyph.m_ttfB + glyph.m_ttfC );
}


//-----------------------------------------------------------------------------------------------
STATIC float OpenGLRenderer::CalcTextWidth( const std::string& text, const BitmapFont& font, float fontCellHeight )
{
	float textWidth = 0.f;

	for( unsigned int charIndex = 0; charIndex < text.size(); ++charIndex )
	{
		unsigned char textChar = text[ charIndex ];
		Glyph glyph = font.m_glyphData[ textChar ];
		textWidth += fontCellHeight * ( glyph.m_ttfA + glyph.m_ttfB + glyph.m_ttfC );
	}

	return textWidth;
}


//-----------------------------------------------------------------------------------------------
STATIC int OpenGLRenderer::GetBlendParameter( blendFuncParam param )
{
	if( param == ZERO )
		return GL_ZERO;
	if( param == ONE )
		return GL_ONE;
	if( param == DST_COLOR )
		return GL_DST_COLOR;
	if( param == ONE_MINUS_DST_COLOR )
		return GL_ONE_MINUS_DST_COLOR;
	if( param == SRC_ALPHA )
		return GL_SRC_ALPHA;
	if( param == ONE_MINUS_SRC_ALPHA )
		return GL_ONE_MINUS_SRC_ALPHA;

	return GL_ZERO;
}