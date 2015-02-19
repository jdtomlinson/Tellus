#include "Button.hpp"
#include "EventSystem.hpp"
#include "OpenGLRenderer.hpp"


//-----------------------------------------------------------------------------------------------
Button::Button( const Vector2& bottomLeftPosition, float width, float height, const std::string& eventToFireWhenPressed, const std::string& buttonUpTextureFileName, const std::string& buttonOverTextureFileName, const std::string& buttonDownTextureFileName )
	: m_state( BUTTON_STATE_UP )
	, m_eventNameToFire( eventToFireWhenPressed )
{
	m_screenPositionBottomLeft = bottomLeftPosition;
	m_widthPixels = width;
	m_heightPixels = height;
	m_upTexture = Texture::CreateOrGetTexture( buttonUpTextureFileName );
	m_overTexture = Texture::CreateOrGetTexture( buttonOverTextureFileName );
	m_downTexture = Texture::CreateOrGetTexture( buttonDownTextureFileName );
}


//-----------------------------------------------------------------------------------------------
void Button::Update( float deltaSeconds, const Mouse& mouse, const Keyboard& keyboard )
{
	Widget::Update( deltaSeconds, mouse, keyboard );

	if( m_state == BUTTON_STATE_DOWN && mouse.IsLeftButtonReleased() )
		EventSystem::FireEvent( m_eventNameToFire );

	Vector2 cursorPosition = mouse.GetCursorPositionOnWindow();
	Vector2 screenPositionTopRight( m_screenPositionBottomLeft.x + m_widthPixels, m_screenPositionBottomLeft.y + m_heightPixels );
	if( cursorPosition.x > m_screenPositionBottomLeft.x && cursorPosition.x < screenPositionTopRight.x )
	{
		if( cursorPosition.y > m_screenPositionBottomLeft.y && cursorPosition.y < screenPositionTopRight.y )
		{
			if( mouse.IsLeftButtonClicked() || ( mouse.IsLeftButtonDown() && m_state == BUTTON_STATE_DOWN ) )
				m_state = BUTTON_STATE_DOWN;
			else
				m_state = BUTTON_STATE_OVER;

			return;
		}
	}

	m_state = BUTTON_STATE_UP;
}


//-----------------------------------------------------------------------------------------------
void Button::Render()
{
	OpenGLRenderer::EnableTexture2D();

	Texture* textureToBind = nullptr;
	if( m_state == BUTTON_STATE_UP )
		textureToBind = m_upTexture;
	else if( m_state == BUTTON_STATE_OVER )
		textureToBind = m_overTexture;
	else if( m_state == BUTTON_STATE_DOWN )
		textureToBind = m_downTexture;

	if( textureToBind != nullptr )
		OpenGLRenderer::BindTexture2D( textureToBind->m_openglTextureID );

	OpenGLRenderer::SetColor4f( 1.f, 1.f, 1.f, 1.f );
	OpenGLRenderer::BeginRender( QUADS );
	{
		OpenGLRenderer::SetTexCoords2f( 0.f, 1.f );
		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x, m_screenPositionBottomLeft.y );

		OpenGLRenderer::SetTexCoords2f( 1.f, 1.f );
		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x + m_widthPixels, m_screenPositionBottomLeft.y );

		OpenGLRenderer::SetTexCoords2f( 1.f, 0.f );
		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x + m_widthPixels, m_screenPositionBottomLeft.y + m_heightPixels );

		OpenGLRenderer::SetTexCoords2f( 0.f, 0.f );
		OpenGLRenderer::SetVertex2f( m_screenPositionBottomLeft.x, m_screenPositionBottomLeft.y + m_heightPixels );
	}
	OpenGLRenderer::EndRender();

	OpenGLRenderer::BindTexture2D( 0 );
	OpenGLRenderer::DisableTexture2D();
}