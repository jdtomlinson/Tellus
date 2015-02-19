#include "DebugGraphics.hpp"
#include "geometry.h"
#include "MathFunctions.hpp"
#include "OpenGLRenderer.hpp"


//-----------------------------------------------------------------------------------------------
DebugGraphicsPoint::DebugGraphicsPoint()
	: m_position()
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsPoint::DebugGraphicsPoint( const Vector3& position )
	: m_position( position )
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsPoint::DebugGraphicsPoint( const Vector3& position, const Color& color )
	: m_position( position )
	,m_color( color )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsPoint::DebugGraphicsPoint( const Vector3& position, bool drawForSingleFrame )
	: m_position( position )
	, m_color()
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsPoint::DebugGraphicsPoint( const Vector3& position, float secondsToDraw )
	: m_position( position )
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsPoint::DebugGraphicsPoint( const Vector3& position, depthSetting depthType )
	: m_position( position )
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsPoint::DebugGraphicsPoint( const Vector3& position, const Color& color, bool drawForSingleFrame )
	: m_position( position )
	, m_color( color )
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsPoint::DebugGraphicsPoint( const Vector3& position, const Color& color, float secondsToDraw )
	: m_position( position )
	, m_color( color )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsPoint::DebugGraphicsPoint( const Vector3& position, const Color& color, depthSetting depthType )
	: m_position( position )
	, m_color( color )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsPoint::DebugGraphicsPoint( const Vector3& position, bool drawForSingleFrame, depthSetting depthType )
	: m_position( position )
	, m_color()
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsPoint::DebugGraphicsPoint( const Vector3& position, float secondsToDraw, depthSetting depthType )
	: m_position( position )
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsPoint::DebugGraphicsPoint( const Vector3& position, const Color& color, bool drawForSingleFrame, depthSetting depthType )
	: m_position( position )
	, m_color( color )
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsPoint::DebugGraphicsPoint( const Vector3& position, const Color& color, float secondsToDraw, depthSetting depthType )
	: m_position( position )
	, m_color( color )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsPoint::UpdatePosition( const Vector3& position )
{
	m_position = position;
}


//-----------------------------------------------------------------------------------------------
Vector3 DebugGraphicsPoint::GetPosition()
{
	return m_position;
}


//-----------------------------------------------------------------------------------------------
Color DebugGraphicsPoint::GetColor()
{
	return m_color;
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsPoint::Update( float deltaSeconds )
{
	if( m_removeAfterTime && m_secondsToDraw <= 0.f )
		m_stopRender;

	if( m_removeAfterTime && m_secondsToDraw > 0.f )
		m_secondsToDraw -= deltaSeconds;
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsPoint::Render()
{
	if( m_stopRender )
		return;

	OpenGLRenderer::PushMatrix();

	OpenGLRenderer::SetLineWidth( LINE_WIDTH );

	if( m_depthSetting == DUAL_DEPTH )
	{
		OpenGLRenderer::DisableDepthTest();
		OpenGLRenderer::SetColor4f( 1.f, 1.f, 1.f, DUAL_DEPTH_ALPHA );
		RenderPoint();
		OpenGLRenderer::EnableDepthTest();
	}
	
	if( m_depthSetting == DEPTH_OFF )
	{
		OpenGLRenderer::DisableDepthTest();
		OpenGLRenderer::SetColor4f( m_color.r, m_color.g, m_color.b, m_color.a );
		RenderPoint();
		OpenGLRenderer::EnableDepthTest();
	}

	if( m_depthSetting == DEPTH_ON || m_depthSetting == DUAL_DEPTH )
	{
		OpenGLRenderer::SetColor4f( m_color.r, m_color.g, m_color.b, m_color.a );
		RenderPoint();
	}

	OpenGLRenderer::PopMatrix();

	if( m_drawOneFrame )
		m_stopRender = true;
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsPoint::RenderPoint()
{
	OpenGLRenderer::BeginRender( LINES );
	{
		OpenGLRenderer::SetVertex3f( m_position.x + DEBUG_POINT_LINE_LENGTH, m_position.y + DEBUG_POINT_LINE_LENGTH, m_position.z + DEBUG_POINT_LINE_LENGTH );
		OpenGLRenderer::SetVertex3f( m_position.x - DEBUG_POINT_LINE_LENGTH, m_position.y - DEBUG_POINT_LINE_LENGTH, m_position.z - DEBUG_POINT_LINE_LENGTH );
		
		OpenGLRenderer::SetVertex3f( m_position.x + DEBUG_POINT_LINE_LENGTH, m_position.y - DEBUG_POINT_LINE_LENGTH, m_position.z + DEBUG_POINT_LINE_LENGTH );
		OpenGLRenderer::SetVertex3f( m_position.x - DEBUG_POINT_LINE_LENGTH, m_position.y + DEBUG_POINT_LINE_LENGTH, m_position.z - DEBUG_POINT_LINE_LENGTH );
		
		OpenGLRenderer::SetVertex3f( m_position.x - DEBUG_POINT_LINE_LENGTH, m_position.y + DEBUG_POINT_LINE_LENGTH, m_position.z + DEBUG_POINT_LINE_LENGTH );
		OpenGLRenderer::SetVertex3f( m_position.x + DEBUG_POINT_LINE_LENGTH, m_position.y - DEBUG_POINT_LINE_LENGTH, m_position.z - DEBUG_POINT_LINE_LENGTH );
		
		OpenGLRenderer::SetVertex3f( m_position.x - DEBUG_POINT_LINE_LENGTH, m_position.y - DEBUG_POINT_LINE_LENGTH, m_position.z + DEBUG_POINT_LINE_LENGTH );
		OpenGLRenderer::SetVertex3f( m_position.x + DEBUG_POINT_LINE_LENGTH, m_position.y + DEBUG_POINT_LINE_LENGTH, m_position.z - DEBUG_POINT_LINE_LENGTH );
	}
	OpenGLRenderer::EndRender();
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsLine::DebugGraphicsLine()
	: m_startPosition()
	, m_endPosition()
	, m_startColor()
	, m_endColor()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsLine::DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_startColor()
	, m_endColor()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsLine::DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, const Color& startColor, const Color& endColor )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_startColor( startColor )
	, m_endColor( endColor )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsLine::DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, bool drawForSingleFrame )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_startColor()
	, m_endColor()
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsLine::DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, float secondsToDraw )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_startColor()
	, m_endColor()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsLine::DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, depthSetting depthType )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_startColor()
	, m_endColor()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsLine::DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, const Color& startColor, const Color& endColor, bool drawForSingleFrame )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_startColor( startColor )
	, m_endColor( endColor )
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsLine::DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, const Color& startColor, const Color& endColor, float secondsToDraw )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_startColor( startColor )
	, m_endColor( endColor )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsLine::DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, const Color& startColor, const Color& endColor, depthSetting depthType )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_startColor( startColor )
	, m_endColor( endColor )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsLine::DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, bool drawForSingleFrame, depthSetting depthType )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_startColor()
	, m_endColor()
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsLine::DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, float secondsToDraw, depthSetting depthType )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_startColor()
	, m_endColor()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsLine::DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, const Color& startColor, const Color& endColor, bool drawForSingleFrame, depthSetting depthType )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_startColor( startColor )
	, m_endColor( endColor )
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsLine::DebugGraphicsLine( const Vector3& startPosition, const Vector3& endPosition, const Color& startColor, const Color& endColor, float secondsToDraw, depthSetting depthType )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_startColor( startColor )
	, m_endColor( endColor )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsLine::Update( float deltaSeconds )
{
	if( m_removeAfterTime && m_secondsToDraw <= 0.f )
		m_stopRender;

	if( m_removeAfterTime && m_secondsToDraw > 0.f )
		m_secondsToDraw -= deltaSeconds;
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsLine::Render()
{
	if( m_stopRender )
		return;

	OpenGLRenderer::PushMatrix();

	OpenGLRenderer::SetLineWidth( LINE_WIDTH );

	if( m_depthSetting == DUAL_DEPTH )
	{
		OpenGLRenderer::DisableDepthTest();
		OpenGLRenderer::SetColor4f( 1.f, 1.f, 1.f, DUAL_DEPTH_ALPHA );

		OpenGLRenderer::BeginRender( LINES );
		{
			OpenGLRenderer::SetVertex3f( m_startPosition.x, m_startPosition.y, m_startPosition.z );
			OpenGLRenderer::SetVertex3f( m_endPosition.x, m_endPosition.y, m_endPosition.z );
		}
		OpenGLRenderer::EndRender();

		OpenGLRenderer::EnableDepthTest();
	}

	if( m_depthSetting == DEPTH_OFF )
	{
		OpenGLRenderer::DisableDepthTest();

		OpenGLRenderer::BeginRender( LINES );
		{
			OpenGLRenderer::SetColor4f( m_startColor.r, m_startColor.g, m_startColor.b, m_startColor.a );
			OpenGLRenderer::SetVertex3f( m_startPosition.x, m_startPosition.y, m_startPosition.z );

			OpenGLRenderer::SetColor4f( m_endColor.r, m_endColor.g, m_endColor.b, m_endColor.a );
			OpenGLRenderer::SetVertex3f( m_endPosition.x, m_endPosition.y, m_endPosition.z );
		}
		OpenGLRenderer::EndRender();

		OpenGLRenderer::EnableDepthTest();
	}

	if( m_depthSetting == DEPTH_ON || m_depthSetting == DUAL_DEPTH )
	{
		OpenGLRenderer::BeginRender( LINES );
		{
			OpenGLRenderer::SetColor4f( m_startColor.r, m_startColor.g, m_startColor.b, m_startColor.a );
			OpenGLRenderer::SetVertex3f( m_startPosition.x, m_startPosition.y, m_startPosition.z );

			OpenGLRenderer::SetColor4f( m_endColor.r, m_endColor.g, m_endColor.b, m_endColor.a );
			OpenGLRenderer::SetVertex3f( m_endPosition.x, m_endPosition.y, m_endPosition.z );
		}
		OpenGLRenderer::EndRender();
	}

	OpenGLRenderer::PopMatrix();

	if( m_drawOneFrame )
		m_stopRender = true;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAxis::DebugGraphicsAxis()
	: m_position()
	, m_length( 0.f )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAxis::DebugGraphicsAxis( const Vector3& position, float length )
	: m_position( position )
	, m_length( length )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAxis::DebugGraphicsAxis( const Vector3& position, float length, bool drawForSingleFrame )
	: m_position( position )
	, m_length( length )
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAxis::DebugGraphicsAxis( const Vector3& position, float length, float secondsToDraw )
	: m_position( position )
	, m_length( length )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAxis::DebugGraphicsAxis( const Vector3& position, float length, depthSetting depthType )
	: m_position( position )
	, m_length( length )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAxis::DebugGraphicsAxis( const Vector3& position, float length, bool drawForSingleFrame, depthSetting depthType )
	: m_position( position )
	, m_length( length )
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAxis::DebugGraphicsAxis( const Vector3& position, float length, float secondsToDraw, depthSetting depthType )
	: m_position( position )
	, m_length( length )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsAxis::Update( float deltaSeconds )
{
	if( m_removeAfterTime && m_secondsToDraw <= 0.f )
		m_stopRender;

	if( m_removeAfterTime && m_secondsToDraw > 0.f )
		m_secondsToDraw -= deltaSeconds;
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsAxis::Render()
{
	if( m_stopRender )
		return;

	OpenGLRenderer::PushMatrix();

	OpenGLRenderer::Translatef( m_position.x, m_position.y, m_position.z );
	OpenGLRenderer::SetLineWidth( LINE_WIDTH );

	if( m_depthSetting == DUAL_DEPTH )
	{
		OpenGLRenderer::DisableDepthTest();
		OpenGLRenderer::SetColor4f( 1.f, 1.f, 1.f, DUAL_DEPTH_ALPHA );

		OpenGLRenderer::BeginRender( LINES );
		{
			OpenGLRenderer::SetVertex3f( 0.f, 0.f, 0.f );
			OpenGLRenderer::SetVertex3f( m_length, 0.f, 0.f );

			OpenGLRenderer::SetVertex3f( 0.f, 0.f, 0.f );
			OpenGLRenderer::SetVertex3f( 0.f, m_length, 0.f );

			OpenGLRenderer::SetVertex3f( 0.f, 0.f, 0.f );
			OpenGLRenderer::SetVertex3f( 0.f, 0.f, m_length );
		}
		OpenGLRenderer::EndRender();

		OpenGLRenderer::EnableDepthTest();
	}

	if( m_depthSetting == DEPTH_OFF )
	{
		OpenGLRenderer::DisableDepthTest();

		OpenGLRenderer::BeginRender( LINES );
		{
			OpenGLRenderer::SetColor3f( 1.f, 0.f, 0.f );
			OpenGLRenderer::SetVertex3f( 0.f, 0.f, 0.f );
			OpenGLRenderer::SetVertex3f( m_length, 0.f, 0.f );

			OpenGLRenderer::SetColor3f( 0.f, 1.f, 0.f );
			OpenGLRenderer::SetVertex3f( 0.f, 0.f, 0.f );
			OpenGLRenderer::SetVertex3f( 0.f, m_length, 0.f );

			OpenGLRenderer::SetColor3f( 0.f, 0.f, 1.f );
			OpenGLRenderer::SetVertex3f( 0.f, 0.f, 0.f );
			OpenGLRenderer::SetVertex3f( 0.f, 0.f, m_length );
		}
		OpenGLRenderer::EndRender();

		OpenGLRenderer::EnableDepthTest();
	}

	if( m_depthSetting == DEPTH_ON || m_depthSetting == DUAL_DEPTH )
	{
		OpenGLRenderer::BeginRender( LINES );
		{
			OpenGLRenderer::SetColor3f( 1.f, 0.f, 0.f );
			OpenGLRenderer::SetVertex3f( 0.f, 0.f, 0.f );
			OpenGLRenderer::SetVertex3f( m_length, 0.f, 0.f );

			OpenGLRenderer::SetColor3f( 0.f, 1.f, 0.f );
			OpenGLRenderer::SetVertex3f( 0.f, 0.f, 0.f );
			OpenGLRenderer::SetVertex3f( 0.f, m_length, 0.f );

			OpenGLRenderer::SetColor3f( 0.f, 0.f, 1.f );
			OpenGLRenderer::SetVertex3f( 0.f, 0.f, 0.f );
			OpenGLRenderer::SetVertex3f( 0.f, 0.f, m_length );
		}
		OpenGLRenderer::EndRender();
	}

	OpenGLRenderer::PopMatrix();

	if( m_drawOneFrame )
		m_stopRender = true;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsArrow::DebugGraphicsArrow()
	: m_startPosition()
	, m_endPosition()
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsArrow::DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsArrow::DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, const Color& color )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_color( color )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsArrow::DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, bool drawForSingleFrame )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_color()
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsArrow::DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, float secondsToDraw )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsArrow::DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, depthSetting depthType )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsArrow::DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, const Color& color, bool drawForSingleFrame )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_color( color )
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsArrow::DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, const Color& color, float secondsToDraw )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_color( color )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsArrow::DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, const Color& color, depthSetting depthType )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_color( color )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsArrow::DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, bool drawForSingleFrame, depthSetting depthType )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_color()
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsArrow::DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, float secondsToDraw, depthSetting depthType )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsArrow::DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, const Color& color, bool drawForSingleFrame, depthSetting depthType )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_color( color )
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsArrow::DebugGraphicsArrow( const Vector3& startPosition, const Vector3& endPosition, const Color& color, float secondsToDraw, depthSetting depthType )
	: m_startPosition( startPosition )
	, m_endPosition( endPosition )
	, m_color( color )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsArrow::RenderArrow()
{
	Vector3 kBB = m_startPosition - m_endPosition;
	kBB.Normalize();
	Vector3 iBB = CrossProduct( Vector3( 0.f, 1.f, 0.f ), kBB );
	if( kBB == Vector3( 0.f, -1.f, 0.f ) || kBB == Vector3( 0.f, 1.f, 0.f ) )
		iBB = CrossProduct( Vector3( 1.f, 0.f, 0.f ), kBB );
	iBB.Normalize();
	Vector3 jBB = CrossProduct( kBB, iBB );
	float rotateMatrix[16];

	rotateMatrix[0] = iBB.x;
	rotateMatrix[1] = iBB.y;
	rotateMatrix[2] = iBB.z;
	rotateMatrix[3] = 0.f;
	rotateMatrix[4] = jBB.x;
	rotateMatrix[5] = jBB.y;
	rotateMatrix[6] = jBB.z;
	rotateMatrix[7] = 0.f;
	rotateMatrix[8] = kBB.x;
	rotateMatrix[9] = kBB.y;
	rotateMatrix[10] = kBB.z;
	rotateMatrix[11] = 0.f;
	rotateMatrix[12] = 0.f;
	rotateMatrix[13] = 0.f;
	rotateMatrix[14] = 0.f;
	rotateMatrix[15] = 1.f;

	OpenGLRenderer::BeginRender( LINES );
	{
		OpenGLRenderer::SetVertex3f( m_startPosition.x, m_startPosition.y, m_startPosition.z );
		OpenGLRenderer::SetVertex3f( m_endPosition.x, m_endPosition.y, m_endPosition.z );
	}
	OpenGLRenderer::EndRender();

	OpenGLRenderer::Translatef( m_endPosition.x, m_endPosition.y, m_endPosition.z );
	OpenGLRenderer::MultMatrixf( rotateMatrix );

	OpenGLRenderer::BeginRender( LINES );
	{
		OpenGLRenderer::SetVertex3f( 0.f, 0.f, 0.f );
		OpenGLRenderer::SetVertex3f( -DEBUG_ARROW_HEAD_LENGTH, -DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH );

		OpenGLRenderer::SetVertex3f( 0.f, 0.f, 0.f );
		OpenGLRenderer::SetVertex3f( DEBUG_ARROW_HEAD_LENGTH, -DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH );

		OpenGLRenderer::SetVertex3f( 0.f, 0.f, 0.f );
		OpenGLRenderer::SetVertex3f( -DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH );

		OpenGLRenderer::SetVertex3f( 0.f, 0.f, 0.f );
		OpenGLRenderer::SetVertex3f( DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH );

		OpenGLRenderer::SetVertex3f( -DEBUG_ARROW_HEAD_LENGTH, -DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH );
		OpenGLRenderer::SetVertex3f( DEBUG_ARROW_HEAD_LENGTH, -DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH );

		OpenGLRenderer::SetVertex3f( -DEBUG_ARROW_HEAD_LENGTH, -DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH );
		OpenGLRenderer::SetVertex3f( -DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH );

		OpenGLRenderer::SetVertex3f( -DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH );
		OpenGLRenderer::SetVertex3f( DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH );

		OpenGLRenderer::SetVertex3f( DEBUG_ARROW_HEAD_LENGTH, -DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH );
		OpenGLRenderer::SetVertex3f( DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH, DEBUG_ARROW_HEAD_LENGTH );
	}
	OpenGLRenderer::EndRender();
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsArrow::Update( float deltaSeconds )
{
	if( m_removeAfterTime && m_secondsToDraw <= 0.f )
		m_stopRender;

	if( m_removeAfterTime && m_secondsToDraw > 0.f )
		m_secondsToDraw -= deltaSeconds;
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsArrow::Render()
{
	if( m_stopRender )
		return;

	OpenGLRenderer::PushMatrix();

	OpenGLRenderer::SetLineWidth( LINE_WIDTH );

	if( m_depthSetting == DUAL_DEPTH )
	{
		OpenGLRenderer::DisableDepthTest();
		OpenGLRenderer::SetColor4f( 1.f, 1.f, 1.f, DUAL_DEPTH_ALPHA );
		RenderArrow();
		OpenGLRenderer::EnableDepthTest();
	}

	if( m_depthSetting == DEPTH_OFF )
	{
		OpenGLRenderer::DisableDepthTest();
		OpenGLRenderer::SetColor4f( m_color.r, m_color.g, m_color.b, m_color.a );
		RenderArrow();
		OpenGLRenderer::EnableDepthTest();
	}

	if( m_depthSetting == DEPTH_ON || m_depthSetting == DUAL_DEPTH )
	{
		OpenGLRenderer::SetColor4f( m_color.r, m_color.g, m_color.b, m_color.a );
		RenderArrow();
	}

	OpenGLRenderer::PopMatrix();

	if( m_drawOneFrame )
		m_stopRender = true;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAABB3::DebugGraphicsAABB3()
	: m_boundingBox()
	, m_lineColor()
	, m_faceColor()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAABB3::DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength )
	: m_boundingBox( position, xAxisLength, yAxisLength, zAxisLength )
	, m_lineColor()
	, m_faceColor()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAABB3::DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, const Color& lineColor, const Color& faceColor )
	: m_boundingBox( position, xAxisLength, yAxisLength, zAxisLength )
	, m_lineColor( lineColor )
	, m_faceColor( faceColor )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAABB3::DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, bool drawForSingleFrame )
	: m_boundingBox( position, xAxisLength, yAxisLength, zAxisLength )
	, m_lineColor()
	, m_faceColor()
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAABB3::DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, float secondsToDraw )
	: m_boundingBox( position, xAxisLength, yAxisLength, zAxisLength )
	, m_lineColor()
	, m_faceColor()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAABB3::DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, depthSetting depthType )
	: m_boundingBox( position, xAxisLength, yAxisLength, zAxisLength )
	, m_lineColor()
	, m_faceColor()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAABB3::DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, const Color& lineColor, const Color& faceColor, bool drawForSingleFrame )
	: m_boundingBox( position, xAxisLength, yAxisLength, zAxisLength )
	, m_lineColor( lineColor )
	, m_faceColor( faceColor )
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAABB3::DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, const Color& lineColor, const Color& faceColor, float secondsToDraw )
	: m_boundingBox( position, xAxisLength, yAxisLength, zAxisLength )
	, m_lineColor( lineColor )
	, m_faceColor( faceColor )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAABB3::DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, const Color& lineColor, const Color& faceColor, depthSetting depthType )
	: m_boundingBox( position, xAxisLength, yAxisLength, zAxisLength )
	, m_lineColor( lineColor )
	, m_faceColor( faceColor )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAABB3::DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, bool drawForSingleFrame, depthSetting depthType )
	: m_boundingBox( position, xAxisLength, yAxisLength, zAxisLength )
	, m_lineColor()
	, m_faceColor()
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAABB3::DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, float secondsToDraw, depthSetting depthType )
	: m_boundingBox( position, xAxisLength, yAxisLength, zAxisLength )
	, m_lineColor()
	, m_faceColor()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAABB3::DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, const Color& lineColor, const Color& faceColor, bool drawForSingleFrame, depthSetting depthType )
	: m_boundingBox( position, xAxisLength, yAxisLength, zAxisLength )
	, m_lineColor( lineColor )
	, m_faceColor( faceColor )
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsAABB3::DebugGraphicsAABB3( const Vector3& position, float xAxisLength, float yAxisLength, float zAxisLength, const Color& lineColor, const Color& faceColor, float secondsToDraw, depthSetting depthType )
	: m_boundingBox( position, xAxisLength, yAxisLength, zAxisLength )
	, m_lineColor( lineColor )
	, m_faceColor( faceColor )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsAABB3::RenderAABB3Lines()
{
	float xMin = -m_boundingBox.m_xAxisHalfLength;
	float xMax = m_boundingBox.m_xAxisHalfLength;
	float yMin = -m_boundingBox.m_yAxisHalfLength;
	float yMax = m_boundingBox.m_yAxisHalfLength;
	float zMin = -m_boundingBox.m_zAxisHalfLength;
	float zMax = m_boundingBox.m_zAxisHalfLength;

	OpenGLRenderer::BeginRender( LINES );
	{
		OpenGLRenderer::SetVertex3f( xMin, yMin, zMin );
		OpenGLRenderer::SetVertex3f( xMin, yMax, zMin );

		OpenGLRenderer::SetVertex3f( xMin, yMin, zMin );
		OpenGLRenderer::SetVertex3f( xMin, yMin, zMax );

		OpenGLRenderer::SetVertex3f( xMax, yMin, zMin );
		OpenGLRenderer::SetVertex3f( xMax, yMax, zMin );

		OpenGLRenderer::SetVertex3f( xMax, yMin, zMin );
		OpenGLRenderer::SetVertex3f( xMax, yMin, zMax );

		OpenGLRenderer::SetVertex3f( xMin, yMin, zMin );
		OpenGLRenderer::SetVertex3f( xMax, yMin, zMin );

		OpenGLRenderer::SetVertex3f( xMin, yMax, zMin );
		OpenGLRenderer::SetVertex3f( xMax, yMax, zMin );

		OpenGLRenderer::SetVertex3f( xMin, yMax, zMin );
		OpenGLRenderer::SetVertex3f( xMin, yMax, zMax );

		OpenGLRenderer::SetVertex3f( xMax, yMax, zMin );
		OpenGLRenderer::SetVertex3f( xMax, yMax, zMax );

		OpenGLRenderer::SetVertex3f( xMin, yMin, zMax );
		OpenGLRenderer::SetVertex3f( xMax, yMin, zMax );

		OpenGLRenderer::SetVertex3f( xMin, yMin, zMax );
		OpenGLRenderer::SetVertex3f( xMin, yMax, zMax );

		OpenGLRenderer::SetVertex3f( xMax, yMin, zMax );
		OpenGLRenderer::SetVertex3f( xMax, yMax, zMax );

		OpenGLRenderer::SetVertex3f( xMin, yMax, zMax );
		OpenGLRenderer::SetVertex3f( xMax, yMax, zMax );
	}
	OpenGLRenderer::EndRender();
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsAABB3::RenderAABB3Faces()
{
	float xMin = -m_boundingBox.m_xAxisHalfLength;
	float xMax = m_boundingBox.m_xAxisHalfLength;
	float yMin = -m_boundingBox.m_yAxisHalfLength;
	float yMax = m_boundingBox.m_yAxisHalfLength;
	float zMin = -m_boundingBox.m_zAxisHalfLength;
	float zMax = m_boundingBox.m_zAxisHalfLength;

	OpenGLRenderer::BeginRender( QUADS );
	{
		OpenGLRenderer::SetVertex3f( xMin, yMin, zMin );
		OpenGLRenderer::SetVertex3f( xMin, yMin, zMax );
		OpenGLRenderer::SetVertex3f( xMin, yMax, zMax );
		OpenGLRenderer::SetVertex3f( xMin, yMax, zMin );

		OpenGLRenderer::SetVertex3f( xMax, yMin, zMin );
		OpenGLRenderer::SetVertex3f( xMax, yMax, zMin );
		OpenGLRenderer::SetVertex3f( xMax, yMax, zMax );
		OpenGLRenderer::SetVertex3f( xMax, yMin, zMax );

		OpenGLRenderer::SetVertex3f( xMin, yMin, zMin );
		OpenGLRenderer::SetVertex3f( xMax, yMin, zMin );
		OpenGLRenderer::SetVertex3f( xMax, yMin, zMax );
		OpenGLRenderer::SetVertex3f( xMin, yMin, zMax );

		OpenGLRenderer::SetVertex3f( xMin, yMax, zMin );
		OpenGLRenderer::SetVertex3f( xMin, yMax, zMax );
		OpenGLRenderer::SetVertex3f( xMax, yMax, zMax );
		OpenGLRenderer::SetVertex3f( xMax, yMax, zMin );

		OpenGLRenderer::SetVertex3f( xMin, yMin, zMin );
		OpenGLRenderer::SetVertex3f( xMin, yMax, zMin );
		OpenGLRenderer::SetVertex3f( xMax, yMax, zMin );
		OpenGLRenderer::SetVertex3f( xMax, yMin, zMin );

		OpenGLRenderer::SetVertex3f( xMin, yMin, zMax );
		OpenGLRenderer::SetVertex3f( xMax, yMin, zMax );
		OpenGLRenderer::SetVertex3f( xMax, yMax, zMax );
		OpenGLRenderer::SetVertex3f( xMin, yMax, zMax );
	}
	OpenGLRenderer::EndRender();
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsAABB3::Update( float deltaSeconds )
{
	if( m_removeAfterTime && m_secondsToDraw <= 0.f )
		m_stopRender;

	if( m_removeAfterTime && m_secondsToDraw > 0.f )
		m_secondsToDraw -= deltaSeconds;
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsAABB3::Render()
{
	if( m_stopRender )
		return;

	OpenGLRenderer::PushMatrix();

	OpenGLRenderer::Translatef( m_boundingBox.m_centerPosition.x, m_boundingBox.m_centerPosition.y, m_boundingBox.m_centerPosition.z );
	OpenGLRenderer::SetLineWidth( LINE_WIDTH );

	if( m_depthSetting == DUAL_DEPTH )
	{
		OpenGLRenderer::DisableDepthTest();
		OpenGLRenderer::SetColor4f( 1.f, 1.f, 1.f, DUAL_DEPTH_ALPHA );
		RenderAABB3Lines();

		OpenGLRenderer::SetColor4f( 1.f, 1.f, 1.f, DUAL_DEPTH_ALPHA );
		RenderAABB3Faces();
		OpenGLRenderer::EnableDepthTest();
	}

	if( m_depthSetting == DEPTH_OFF )
	{
		OpenGLRenderer::DisableDepthTest();
		OpenGLRenderer::SetColor4f( m_lineColor.r, m_lineColor.g, m_lineColor.b, m_lineColor.a );
		RenderAABB3Lines();

		OpenGLRenderer::SetColor4f( m_faceColor.r, m_faceColor.g, m_faceColor.b, m_faceColor.a );
		RenderAABB3Faces();
		OpenGLRenderer::EnableDepthTest();
	}

	if( m_depthSetting == DEPTH_ON || m_depthSetting == DUAL_DEPTH )
	{
		OpenGLRenderer::SetColor4f( m_lineColor.r, m_lineColor.g, m_lineColor.b, m_lineColor.a );
		RenderAABB3Lines();

		OpenGLRenderer::SetColor4f( m_faceColor.r, m_faceColor.g, m_faceColor.b, m_faceColor.a );
		RenderAABB3Faces();
	}

	OpenGLRenderer::PopMatrix();

	if( m_drawOneFrame )
		m_stopRender = true;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsSphere::DebugGraphicsSphere()
	: m_position()
	, m_radius( 0.f )
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsSphere::DebugGraphicsSphere( const Vector3& position, float radius )
	: m_position( position )
	, m_radius( radius )
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsSphere::DebugGraphicsSphere( const Vector3& position, float radius, const Color& color )
	: m_position( position )
	, m_radius( radius )
	, m_color( color )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsSphere::DebugGraphicsSphere( const Vector3& position, float radius, bool drawForSingleFrame )
	: m_position( position )
	, m_radius( radius )
	, m_color()
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsSphere::DebugGraphicsSphere( const Vector3& position, float radius, float secondsToDraw )
	: m_position( position )
	, m_radius( radius )
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsSphere::DebugGraphicsSphere( const Vector3& position, float radius, depthSetting depthType )
	: m_position( position )
	, m_radius( radius )
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsSphere::DebugGraphicsSphere( const Vector3& position, float radius, const Color& color, bool drawForSingleFrame )
	: m_position( position )
	, m_radius( radius )
	, m_color( color )
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsSphere::DebugGraphicsSphere( const Vector3& position, float radius, const Color& color, float secondsToDraw )
	: m_position( position )
	, m_radius( radius )
	, m_color( color )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = DEFAULT_DEPTH;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsSphere::DebugGraphicsSphere( const Vector3& position, float radius, const Color& color, depthSetting depthType )
	: m_position( position )
	, m_radius( radius )
	, m_color( color )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsSphere::DebugGraphicsSphere( const Vector3& position, float radius, bool drawForSingleFrame, depthSetting depthType )
	: m_position( position )
	, m_radius( radius )
	, m_color()
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsSphere::DebugGraphicsSphere( const Vector3& position, float radius, float secondsToDraw, depthSetting depthType )
	: m_position( position )
	, m_radius( radius )
	, m_color()
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsSphere::DebugGraphicsSphere( const Vector3& position, float radius, const Color& color, bool drawForSingleFrame, depthSetting depthType )
	: m_position( position )
	, m_radius( radius )
	, m_color( color )
{
	m_drawOneFrame = drawForSingleFrame;
	m_stopRender = false;
	m_removeAfterTime = false;
	m_secondsToDraw = 0.f;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
DebugGraphicsSphere::DebugGraphicsSphere( const Vector3& position, float radius, const Color& color, float secondsToDraw, depthSetting depthType )
	: m_position( position )
	, m_radius( radius )
	, m_color( color )
{
	m_drawOneFrame = false;
	m_stopRender = false;
	m_removeAfterTime = true;
	m_secondsToDraw = secondsToDraw;
	m_depthSetting = depthType;
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsSphere::Update( float deltaSeconds )
{
	if( m_removeAfterTime && m_secondsToDraw <= 0.f )
		m_stopRender;

	if( m_removeAfterTime && m_secondsToDraw > 0.f )
		m_secondsToDraw -= deltaSeconds;
}


//-----------------------------------------------------------------------------------------------
void DebugGraphicsSphere::Render()
{
	if( m_stopRender )
		return;

	OpenGLRenderer::PushMatrix();

	OpenGLRenderer::Translatef( m_position.x, m_position.y, m_position.z );

	if( m_depthSetting == DUAL_DEPTH )
	{
		OpenGLRenderer::DisableDepthTest();
		OpenGLRenderer::SetColor4f( 1.f, 1.f, 1.f, DUAL_DEPTH_ALPHA );
		renderWireSphere( m_radius, 10, 10 );
		OpenGLRenderer::EnableDepthTest();
	}

	if( m_depthSetting == DEPTH_OFF )
	{
		OpenGLRenderer::DisableDepthTest();
		OpenGLRenderer::SetColor4f( m_color.r, m_color.g, m_color.b, m_color.a );
		renderWireSphere( m_radius, 10, 10 );
		OpenGLRenderer::EnableDepthTest();
	}

	if( m_depthSetting == DEPTH_ON || m_depthSetting == DUAL_DEPTH )
	{
		OpenGLRenderer::SetColor4f( m_color.r, m_color.g, m_color.b, m_color.a );
		renderWireSphere( m_radius, 10, 10 );
	}

	OpenGLRenderer::PopMatrix();

	if( m_drawOneFrame )
		m_stopRender = true;
}