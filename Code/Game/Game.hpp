#ifndef include_Game
#define include_Game
#pragma once

//-----------------------------------------------------------------------------------------------
#include <string>
#include <vector>
#include "World.hpp"
#include "GameCommon.hpp"
#include "../Engine/Mouse.hpp"
#include "../Engine/Camera.hpp"
#include "../Engine/Vertex.hpp"
#include "../Engine/Texture.hpp"
#include "../Engine/Vector2.hpp"
#include "../Engine/Keyboard.hpp"
#include "../Engine/Material.hpp"
#include "../Engine/BitmapFont.hpp"
#include "../Engine/DebugGraphics.hpp"
#include "../Engine/OpenGLRenderer.hpp"
#include "../Engine/ConsoleCommandArgs.hpp"


//-----------------------------------------------------------------------------------------------
const float FIELD_OF_VIEW_Y = 45.f;
const float MOVE_SPEED_POINTS_PER_SECOND = 40.f;
const float ROTATION_DEGREES_PER_SECOND = 480.f;
const std::string CURSOR_TEXTURE_FILE_NAME = "Data/Images/Cursor.png";


//-----------------------------------------------------------------------------------------------
class Game
{
public:
	Game( float gameWidth, float gameHeight );
	void Initialize();
	bool ProcessKeyDownEvent( unsigned char virtualKeyCode );
	bool ProcessKeyUpEvent( unsigned char virtualKeyCode );
	bool ProcessCharDownEvent( unsigned char charCode );
	void SetCameraPositionAndOrientation( const Camera& camera );
	void UpdateCameraPositionFromInput( float deltaSeconds );
	void UpdateCameraOrientationFromInput( float deltaSeconds, const Vector2& lastFrameCursorScreenPos );
	void UpdateFromInput( float deltaSeconds, HWND hWnd );
	void Update( HWND hWnd );
	void RenderWorld3D();
	void RenderWorld2D();
	void Render();

	World		m_world;
	Camera		m_camera;
	Mouse		m_mouse;
	Keyboard	m_keyboard;
	bool		m_isPaused;
	Vector2		m_size;
};


#endif // include_Game