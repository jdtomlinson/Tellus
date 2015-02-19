#ifndef include_Renderer
#define include_Renderer
#pragma once

//-----------------------------------------------------------------------------------------------
#include "MatrixStack44.hpp"


//-----------------------------------------------------------------------------------------------
enum renderType
{
	LINES,
	TRIANGLES,
	QUADS,
};


//-----------------------------------------------------------------------------------------------
enum arrayType
{
	VERTEX_ARRAY,
	COLOR_ARRAY,
	TEXTURE_COORD_ARRAY,
	NORMAL_ARRAY,
};


//-----------------------------------------------------------------------------------------------
enum frontFaceDirection
{
	CLOCKWISE,
	COUNTER_CLOCKWISE,
};


//-----------------------------------------------------------------------------------------------
enum faceSide
{
	FRONT,
	BACK,
};


//-----------------------------------------------------------------------------------------------
enum textureWrap
{
	CLAMP,
	REPEAT,
};


//-----------------------------------------------------------------------------------------------
enum textureFilter
{
	NEAREST,
	LINEAR,
	NEAREST_MIPMAP_NEAREST,
	NEAREST_MIPMAP_LINEAR,
	LINEAR_MIPMAP_NEAREST,
	LINEAR_MIPMAP_LINEAR,
};


//-----------------------------------------------------------------------------------------------
enum pixelDataFormat
{
	LUMINANCE,
	RGB,
	RGBA,
};


//-----------------------------------------------------------------------------------------------
enum blendFuncParam
{
	ZERO,
	ONE,
	DST_COLOR,
	ONE_MINUS_DST_COLOR,
	SRC_ALPHA,
	ONE_MINUS_SRC_ALPHA,
};


//-----------------------------------------------------------------------------------------------
enum textureUnit
{
	TEXTURE0,
	TEXTURE1,
	TEXTURE2,
	TEXTURE3,
	TEXTURE4,
	TEXTURE5,
	TEXTURE6,
	TEXTURE7,
};


//-----------------------------------------------------------------------------------------------
class Renderer
{
public:
	Renderer() {}
	virtual void PushMatrix() = 0;
	virtual void PopMatrix() = 0;
	virtual void EnableTexture2D() = 0;
	virtual void DisableTexture2D() = 0;
	virtual void SetActiveTexture() = 0;
	virtual void GenerateTextures() = 0;
	virtual void SetTexture2DImage() = 0;
	virtual void BindTexture2D() = 0;
	virtual void GenerateMipmapTexture2D() = 0;
	virtual void GenerateMipmapHint() = 0;
	virtual void PixelStore() = 0;
	virtual void Translatef() = 0;
	virtual void Rotatef() = 0;
	virtual void Scalef() = 0;
	virtual void SetColor3f() = 0;
	virtual void SetColor4f() = 0;
	virtual void SetLineWidth() = 0;
	virtual void SetDepthMask() = 0;
	virtual void SetOrtho () = 0;
	virtual void SetPerspective() = 0;
	virtual void BeginRender() = 0;
	virtual void EndRender() = 0;
	virtual void SetVertex2f() = 0;
	virtual void SetVertex3f() = 0;
	virtual void SetTexCoords2f() = 0;
	virtual void SetVBO() = 0;
	virtual void RenderVertices() = 0;
	virtual void CreateColorFramebufferTexture2D() = 0;
	virtual void CreateDepthFramebufferTexture2D() = 0;
	virtual void SetFBO() = 0;
	virtual void BindFramebuffer() = 0;
	virtual void DisableFramebuffer() = 0;
	virtual void GenerateBuffers() = 0;
	virtual void DeleteBuffers() = 0;
	virtual void BindBuffer() = 0;
	virtual void SetBufferData() = 0;
	virtual void EnableClientState() = 0;
	virtual void DisableClientState() = 0;
	virtual void DrawArrays() = 0;
	virtual void EnableCullFace() = 0;
	virtual void CullFrontFaceDirection() = 0;
	virtual void CullFaceSide() = 0;
	virtual void ClearColorBufferBit() = 0;
	virtual void ClearDepthBufferBit() = 0;
	virtual void SetClearColor() = 0;
	virtual void SetClearDepth() = 0;
	virtual void EnableBlend() = 0;
	virtual void EnableDepthTest() = 0;
	virtual void BlendFunction() = 0;
	virtual void SetTexture2DWrapS() = 0;
	virtual void SetTexture2DWrapT() = 0;
	virtual void SetTexture2DMagnificationFilter() = 0;
	virtual void SetTexture2DMinificationFilter() = 0;
	virtual void SetTexture2DMaxLevel() = 0;
	virtual void UseShaderProgram() = 0;
	virtual int GetUniformLocation() { return 0; }
	virtual void SetUniform1i() = 0;
	virtual void SetUniform1f() = 0;
	virtual void SetUniform2f() = 0;
	virtual void SetUniform3f() = 0;
	virtual void SetUniform4f() = 0;
	virtual void SetModelViewProjectionMatrix() = 0;
	virtual void SetPositionAttribPointer() = 0;
	virtual void SetColorAttribPointer() = 0;
	virtual void SetTexCoordAttribPointer() = 0;
	virtual void SetNormalAttribPointer() = 0;
	virtual void SetTangentAttribPointer() = 0;
	virtual void EnableAttribArray() = 0;
	virtual void DisableAttribArray() = 0;
	virtual void RenderText() = 0;
	virtual float CalcTextWidth() { return 0.f; }

protected:
	static MatrixStack44	s_matrixStack;
};


#endif // include_Renderer