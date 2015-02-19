#include <math.h>
#include <windows.h>
#include "XboxController.hpp"


//-----------------------------------------------------------------------------------------------
const float pi = 3.1415926535897932384626433832795f;


//-----------------------------------------------------------------------------------------------
XboxController::XboxController()
{

}


//-----------------------------------------------------------------------------------------------
XboxController::XboxController( int xboxControllerNumber ) : m_xboxControllerNumber( xboxControllerNumber )
{

}


//-----------------------------------------------------------------------------------------------
bool XboxController::IsXboxControllerConnected()
{
	memset( &m_currentXboxControllerState, 0, sizeof( m_currentXboxControllerState ) );
	DWORD results = XInputGetState( m_xboxControllerNumber, &m_currentXboxControllerState );
	if( results == ERROR_DEVICE_NOT_CONNECTED )
		return false;
	else
		return true;
}


//-----------------------------------------------------------------------------------------------
Vector2 XboxController::NormalizeStickPosition( const Vector2& rawStickPosition )
{
	Vector2 normalizedStickPosition = rawStickPosition;

	normalizedStickPosition.x *= ONE_OVER_SHORT_MAX;
	normalizedStickPosition.y *= ONE_OVER_SHORT_MAX;

	return normalizedStickPosition;
}


//-----------------------------------------------------------------------------------------------
bool XboxController::IsStickOutsideDeadZone( const Vector2& stickPosition )
{
	float stickDistanceFromCenterSquared = ( stickPosition.x * stickPosition.x ) + ( stickPosition.y * stickPosition.y );
	if( stickDistanceFromCenterSquared > ( DEAD_ZONE_RADIUS * DEAD_ZONE_RADIUS ) )
		return true;
	return false;
}


//-----------------------------------------------------------------------------------------------
bool XboxController::IsButtonPressedDown( xboxControllerButtons buttonPressed )
{
	if( m_currentXboxControllerState.Gamepad.wButtons & buttonPressed )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
bool XboxController::IsButtonPressedDownAndWasNotBefore( xboxControllerButtons buttonPressed )
{
	if( IsButtonPressedDown( buttonPressed ) && !( m_previousXboxControllerState.Gamepad.wButtons & buttonPressed ) )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
bool XboxController::IsLeftTriggerPressedDown()
{
	float percentPressedDown = m_currentXboxControllerState.Gamepad.bLeftTrigger / 255.f;

	if(percentPressedDown > LEFT_TRIGGER_PERCENT_CONSIDERED_PRESSED_DOWN )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
bool XboxController::IsLeftTriggerPressedDownAndWasNotBefore()
{
	float percentWasPressedDown = m_previousXboxControllerState.Gamepad.bLeftTrigger / 255.f;

	if( IsLeftTriggerPressedDown() && percentWasPressedDown < LEFT_TRIGGER_PERCENT_CONSIDERED_PRESSED_DOWN )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
bool XboxController::IsRightTriggerPressedDown()
{
	float percentPressedDown = m_currentXboxControllerState.Gamepad.bRightTrigger / 255.f;

	if(percentPressedDown > RIGHT_TRIGGER_PERCENT_CONSIDERED_PRESSED_DOWN )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
bool XboxController::IsRightTriggerPressedDownAndWasNotBefore()
{
	float percentWasPressedDown = m_previousXboxControllerState.Gamepad.bRightTrigger / 255.f;

	if( IsRightTriggerPressedDown() && percentWasPressedDown < RIGHT_TRIGGER_PERCENT_CONSIDERED_PRESSED_DOWN )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
float XboxController::GetLeftStickOrientationDegrees()
{
	Vector2 leftStickPosition = GetLeftStickPosition();
	float angleRadians = atan2f( leftStickPosition.y, leftStickPosition.x );
	float angleDegrees = angleRadians * ( 180.f / pi );
	return angleDegrees;
}


//-----------------------------------------------------------------------------------------------
float XboxController::GetRightStickOrientationDegrees()
{
	Vector2 rightStickPosition = GetRightStickPosition();
	float angleRadians = atan2f( rightStickPosition.y, rightStickPosition.x );
	float angleDegrees = angleRadians * ( 180.f / pi );
	return angleDegrees;
}


//-----------------------------------------------------------------------------------------------
float XboxController::GetLeftStickLengthFromDeadZoneZeroToOne()
{
	Vector2 leftStickPosition = GetLeftStickPosition();
	if( leftStickPosition.x == 0 && leftStickPosition.y == 0 )
		return 0;

	float stickLengthFromCenter = sqrt( ( leftStickPosition.x * leftStickPosition.x ) + ( leftStickPosition.y * leftStickPosition.y ) );
	float accelerationScale = ( stickLengthFromCenter - DEAD_ZONE_RADIUS ) / ( 1.f - DEAD_ZONE_RADIUS );
	return accelerationScale;
}


//-----------------------------------------------------------------------------------------------
float XboxController::GetRightStickLengthFromDeadZoneZeroToOne()
{
	Vector2 rightStickPosition = GetRightStickPosition();
	float stickLengthFromCenter = sqrt( ( rightStickPosition.x * rightStickPosition.x ) + ( rightStickPosition.y * rightStickPosition.y ) );
	float accelerationScale = ( stickLengthFromCenter - DEAD_ZONE_RADIUS ) / ( 1.f - DEAD_ZONE_RADIUS );
	return accelerationScale;
}


//-----------------------------------------------------------------------------------------------
Vector2 XboxController::GetLeftStickPosition()
{
	Vector2 rawLeftStickPosition( m_currentXboxControllerState.Gamepad.sThumbLX, m_currentXboxControllerState.Gamepad.sThumbLY );
	Vector2 normalizedLeftStickPosition = NormalizeStickPosition( rawLeftStickPosition );

	if( !IsStickOutsideDeadZone( normalizedLeftStickPosition ) )
	{
		return Vector2( 0.f, 0.f );
	}

	return normalizedLeftStickPosition;
}


//-----------------------------------------------------------------------------------------------
Vector2 XboxController::GetRightStickPosition()
{
	Vector2 rawRightStickPosition( m_currentXboxControllerState.Gamepad.sThumbRX, m_currentXboxControllerState.Gamepad.sThumbRY );
	Vector2 normalizedRightStickPosition = NormalizeStickPosition( rawRightStickPosition );

	if( !IsStickOutsideDeadZone( normalizedRightStickPosition ) )
	{
		return Vector2( 0.f, 0.f );
	}

	return normalizedRightStickPosition;
}


//-----------------------------------------------------------------------------------------------
void XboxController::Update()
{
	m_previousXboxControllerState = m_currentXboxControllerState;
	m_leftStickPosition = GetLeftStickPosition();
	m_rightStickPosition = GetRightStickPosition();
}