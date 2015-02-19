#ifndef include_Mouse
#define include_Mouse
#pragma once

//-----------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Texture.hpp"
#include "Vector2.hpp"


//-----------------------------------------------------------------------------------------------
const float SECONDS_BEFORE_MOUSE_IS_IDLE = 1.f;


//-----------------------------------------------------------------------------------------------
class Mouse
{
public:
	Mouse();
	Mouse( const std::string& cursorTextureFileName );
	bool IsLeftButtonClicked() const;
	bool IsRightButtonClicked() const;
	bool IsLeftButtonDown() const;
	bool IsRightButtonDown() const;
	bool IsLeftButtonReleased() const;
	bool IsRightButtonReleased() const;
	bool IsIdle() const;
	Vector2 GetCursorPositionOnScreen() const;
	Vector2 GetCursorPositionOnWindow() const;
	void SetCursorPosition( const Vector2& setPosition );
	void Update( float deltaSeconds, HWND hWnd );
	void RenderCursor();

private:
	void UpdateCursorScreenPosition();
	void UpdateCursorWindowPosition( HWND hWnd );

	bool		m_leftButtonDown;
	bool		m_rightButtonDown;
	bool		m_isIdle;
	float		m_secondsSinceLastMovement;
	Vector2		m_screenPosition;
	Vector2		m_windowPosition;
	Texture*	m_cursorTexture;
};


#endif // include_Mouse