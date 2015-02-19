#ifndef include_Button
#define include_Button
#pragma once

//-----------------------------------------------------------------------------------------------
#include "Widget.hpp"
#include "Texture.hpp"


//-----------------------------------------------------------------------------------------------
enum ButtonState
{
	BUTTON_STATE_UP,
	BUTTON_STATE_OVER,
	BUTTON_STATE_DOWN,
};


//-----------------------------------------------------------------------------------------------
class Button : public Widget
{
public:
	Button() {}
	Button( const Vector2& bottomLeftPosition, float width, float height, const std::string& eventToFireWhenPressed, const std::string& buttonUpTextureFileName, const std::string& buttonOverTextureFileName, const std::string& buttonDownTextureFileName );

protected:
	void Update( float deltaSeconds, const Mouse& mouse, const Keyboard& keyboard );
	void Render();

	Texture*	m_upTexture;
	Texture*	m_overTexture;
	Texture*	m_downTexture;
	ButtonState	m_state;
	std::string	m_eventNameToFire;
};


#endif // include_Button