#ifndef include_DebugGraphics
#define include_DebugGraphics
#pragma once

//-----------------------------------------------------------------------------------------------
#include <vector>
#include "AABB3.hpp"
#include "Color.hpp"
#include "Vertex.hpp"
#include "Vector3.hpp"
#include "Material.hpp"


//-----------------------------------------------------------------------------------------------
enum depthSetting
{
	DEPTH_ON,
	DEPTH_OFF,
	DUAL_DEPTH,
};


//-----------------------------------------------------------------------------------------------
const float LINE_WIDTH = 5.f;
const float DEBUG_POINT_LINE_LENGTH = 0.1f;
const float DEBUG_ARROW_HEAD_LENGTH = 0.1f;
const float DUAL_DEPTH_ALPHA = 0.4f;
const depthSetting DEFAULT_DEPTH = DEPTH_ON;
const std::string VERTEX_SHADER_STRING = "Data/Shaders/Simple_No_Texture_330.vertex.glsl";
const std::string FRAGMENT_SHADER_STRING = "Data/Shaders/Simple_No_Texture_330.fragment.glsl";


//-----------------------------------------------------------------------------------------------
class DebugGraphics
{
public:
	DebugGraphics() {}
	virtual void Update( float ) {}
	virtual void Render() {}

protected:
	bool					m_drawOneFrame;
	bool					m_removeAfterTime;
	bool					m_stopRender;
	float					m_secondsToDraw;
	depthSetting			m_depthSetting;
};


//-----------------------------------------------------------------------------------------------
class DebugGraphicsPoint : public DebugGraphics
{
public:
	DebugGraphicsPoint();
	DebugGraphicsPoint( const Vector3& position );
	DebugGraphicsPoint( const Vector3& position, const Color& color );
	DebugGraphicsPoint( const Vector3& position, bool drawForSingleFrame );
	DebugGraphicsPoint( const Vector3& position, float secondsToDraw );
	DebugGraphicsPoint( const Vector3& position, depthSetting depthType );
	DebugGraphicsPoint( const Vector3& position, const Color& color, bool drawForSingleFrame );
	DebugGraphicsPoint( const Vector3& position, const Color& color, float secondsToDraw );
	DebugGraphicsPoint( const Vector3& position, const Color& color, depthSetting depthType );
	DebugGraphicsPoint( const Vector3& position, bool drawForSingleFrame, depthSetting depthType );
	DebugGraphicsPoint( const Vector3& position, float secondsToDraw, depthSetting depthType );
	DebugGraphicsPoint( const Vector3& position, const Color& color, bool drawForSingleFrame, depthSetting depthType );
	DebugGraphicsPoint( const Vector3& position, const Color& color, float secondsToDraw, depthSetting depthType );
	void UpdatePosition( const Vector3& position );
	Vector3 GetPosition();
	Color GetColor();
	void Update( float deltaSeconds );
	void Render();

private:
	void RenderPoint();

	Vector3					m_position;
	Color					m_color;
};


//-----------------------------------------------------------------------------------------------
class DebugGraphicsLine : public DebugGraphics
{
public:
	DebugGraphicsLine();
	DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition );
	DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, const Color& startColor, const Color& endColor );
	DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, bool drawForSingleFrame );
	DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, float secondsToDraw );
	DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, depthSetting depthType );
	DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, const Color& startColor, const Color& endColor, bool drawForSingleFrame );
	DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, const Color& startColor, const Color& endColor, float secondsToDraw );
	DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, const Color& startColor, const Color& endColor, depthSetting depthType );
	DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, bool drawForSingleFrame, depthSetting depthType );
	DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, float secondsToDraw, depthSetting depthType );
	DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, const Color& startColor, const Color& endColor, bool drawForSingleFrame, depthSetting depthType );
	DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, const Color& startColor, const Color& endColor, float secondsToDraw, depthSetting depthType );
	void Update( float deltaSeconds );
	void Render();

private:
	Vector3					m_startPosition;
	Vector3					m_endPosition;
	Color					m_startColor;
	Color					m_endColor;
};


//-----------------------------------------------------------------------------------------------
class DebugGraphicsAxis : public DebugGraphics
{
public:
	DebugGraphicsAxis();
	DebugGraphicsAxis( const Vector3& position, float length );
	DebugGraphicsAxis( const Vector3& position, float length, bool drawForSingleFrame );
	DebugGraphicsAxis( const Vector3& position, float length, float secondsToDraw );
	DebugGraphicsAxis( const Vector3& position, float length, depthSetting depthType );
	DebugGraphicsAxis( const Vector3& position, float length, bool drawForSingleFrame, depthSetting depthType );
	DebugGraphicsAxis( const Vector3& position, float length, float secondsToDraw, depthSetting depthType );
	void Update( float deltaSeconds );
	void Render();

private:
	Vector3					m_position;
	float					m_length;
};


//-----------------------------------------------------------------------------------------------
class DebugGraphicsArrow : public DebugGraphics
{
public:
	DebugGraphicsArrow();
	DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition );
	DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, const Color& color );
	DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, bool drawForSingleFrame );
	DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, float secondsToDraw );
	DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, depthSetting depthType );
	DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, const Color& color, bool drawForSingleFrame );
	DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, const Color& color, float secondsToDraw );
	DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, const Color& color, depthSetting depthType );
	DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, bool drawForSingleFrame, depthSetting depthType );
	DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, float secondsToDraw, depthSetting depthType );
	DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, const Color& color, bool drawForSingleFrame, depthSetting depthType );
	DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, const Color& color, float secondsToDraw, depthSetting depthType );
	void Update( float deltaSeconds );
	void Render();

private:
	void RenderArrow();

	Vector3					m_startPosition;
	Vector3					m_endPosition;
	Color					m_color;
};


//-----------------------------------------------------------------------------------------------
class DebugGraphicsAABB3 : public DebugGraphics
{
public:
	DebugGraphicsAABB3();
	DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength );
	DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, const Color& lineColor, const Color& faceColor );
	DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, bool drawForSingleFrame );
	DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, float secondsToDraw );
	DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, depthSetting depthType );
	DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, const Color& lineColor, const Color& faceColor, bool drawForSingleFrame );
	DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, const Color& lineColor, const Color& faceColor, float secondsToDraw );
	DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, const Color& lineColor, const Color& faceColor, depthSetting depthType );
	DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, bool drawForSingleFrame, depthSetting depthType );
	DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, float secondsToDraw, depthSetting depthType );
	DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, const Color& lineColor, const Color& faceColor, bool drawForSingleFrame, depthSetting depthType );
	DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, const Color& lineColor, const Color& faceColor, float secondsToDraw, depthSetting depthType );
	void Update( float deltaSeconds );
	void Render();

private:
	void RenderAABB3Lines();
	void RenderAABB3Faces();

	AABB3					m_boundingBox;
	Color					m_lineColor;
	Color					m_faceColor;
};


//-----------------------------------------------------------------------------------------------
class DebugGraphicsSphere : public DebugGraphics
{
public:
	DebugGraphicsSphere();
	DebugGraphicsSphere( const Vector3& position, float radius );
	DebugGraphicsSphere( const Vector3& position, float radius, const Color& color );
	DebugGraphicsSphere( const Vector3& position, float radius, bool drawForSingleFrame );
	DebugGraphicsSphere( const Vector3& position, float radius, float secondsToDraw );
	DebugGraphicsSphere( const Vector3& position, float radius, depthSetting depthType );
	DebugGraphicsSphere( const Vector3& position, float radius, const Color& color, bool drawForSingleFrame );
	DebugGraphicsSphere( const Vector3& position, float radius, const Color& color, float secondsToDraw );
	DebugGraphicsSphere( const Vector3& position, float radius, const Color& color, depthSetting depthType );
	DebugGraphicsSphere( const Vector3& position, float radius, bool drawForSingleFrame, depthSetting depthType );
	DebugGraphicsSphere( const Vector3& position, float radius, float secondsToDraw, depthSetting depthType );
	DebugGraphicsSphere( const Vector3& position, float radius, const Color& color, bool drawForSingleFrame, depthSetting depthType );
	DebugGraphicsSphere( const Vector3& position, float radius, const Color& color, float secondsToDraw, depthSetting depthType );
	void Update( float deltaSeconds );
	void Render();

private:
	Vector3					m_position;
	float					m_radius;
	Color					m_color;
};


#endif