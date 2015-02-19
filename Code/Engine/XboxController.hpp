#ifndef include_XboxController
#define include_XboxController
#pragma once

//-----------------------------------------------------------------------------------------------
#include "Vector2.hpp"
#include <Xinput.h> // include the Xinput API
#pragma comment( lib, "xinput" ) // Link in the xinput.lib static library


//-----------------------------------------------------------------------------------------------
const float DEAD_ZONE_RADIUS = 0.3f;
const float ONE_OVER_SHORT_MAX = 1.f / SHRT_MAX;
const float LEFT_TRIGGER_PERCENT_CONSIDERED_PRESSED_DOWN = 0.8f;
const float RIGHT_TRIGGER_PERCENT_CONSIDERED_PRESSED_DOWN = 0.8f;


//-----------------------------------------------------------------------------------------------
enum xboxControllerButtons
{
	XBOX_CONTROLLER_D_PAD_UP_BUTTON = 0x0001,
	XBOX_CONTROLLER_D_PAD_DOWN_BUTTON = 0x0002,
	XBOX_CONTROLLER_D_PAD_LEFT_BUTTON = 0x0004,
	XBOX_CONTROLLER_D_PAD_RIGHT_BUTTON = 0x0008,
	XBOX_CONTROLLER_START_BUTTON = 0x0010,
	XBOX_CONTROLLER_BACK_BUTTON = 0x0020,
	XBOX_CONTROLLER_LEFT_STICK_BUTTON = 0x0040,
	XBOX_CONTROLLER_RIGHT_STICK_BUTTON = 0x0080,
	XBOX_CONTROLLER_LEFT_BUMPER_BUTTON = 0x0100,
	XBOX_CONTROLLER_RIGHT_BUMPER_BUTTON = 0x0200,
	XBOX_CONTROLLER_A_BUTTON = 0x1000,
	XBOX_CONTROLLER_B_BUTTON = 0x2000,
	XBOX_CONTROLLER_X_BUTTON = 0x4000,
	XBOX_CONTROLLER_Y_BUTTON = 0x8000
};


//-----------------------------------------------------------------------------------------------
class XboxController
{
public:
	XboxController();
	XboxController( int xboxControllerNumber );
	bool IsXboxControllerConnected();
	Vector2 NormalizeStickPosition( const Vector2& rawStickPosition );
	bool IsStickOutsideDeadZone( const Vector2& stickPosition );
	bool IsButtonPressedDown( xboxControllerButtons buttonPressed );
	bool IsButtonPressedDownAndWasNotBefore( xboxControllerButtons buttonPressed );
	bool IsLeftTriggerPressedDown();
	bool IsLeftTriggerPressedDownAndWasNotBefore();
	bool IsRightTriggerPressedDown();
	bool IsRightTriggerPressedDownAndWasNotBefore();
	float GetLeftStickOrientationDegrees();
	float GetRightStickOrientationDegrees();
	float GetLeftStickLengthFromDeadZoneZeroToOne();
	float GetRightStickLengthFromDeadZoneZeroToOne();
	Vector2 GetLeftStickPosition();
	Vector2 GetRightStickPosition();
	void Update();

	XINPUT_STATE	m_currentXboxControllerState;
	XINPUT_STATE	m_previousXboxControllerState;
	Vector2			m_leftStickPosition;
	Vector2			m_rightStickPosition;
	int				m_xboxControllerNumber;
};


#endif // include_XboxController