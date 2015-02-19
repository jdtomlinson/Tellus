#include "Keyboard.hpp"


//-----------------------------------------------------------------------------------------------
Keyboard::Keyboard()
{
	for( int key = 0; key < NUM_VIRTUAL_KEYS; ++key )
	{
		m_isKeyDown[ key ] = false;
		m_wasKeyDown[ key ] = false;
	}
}


//-----------------------------------------------------------------------------------------------
void Keyboard::SetKeyUp( unsigned char setKey )
{
	m_isKeyDown[ setKey ] = false;
}


//-----------------------------------------------------------------------------------------------
void Keyboard::SetKeyDown( unsigned char setKey )
{
	m_isKeyDown[ setKey ] = true;
}


//-----------------------------------------------------------------------------------------------
void Keyboard::SetCharDown( unsigned char setChar )
{
	m_isCharDown[ setChar ] = true;
}



//-----------------------------------------------------------------------------------------------
bool Keyboard::IsKeyPressedDown( keys checkKeys ) const
{
	if( m_isKeyDown[ checkKeys ] )
		return true;

	return false;
}


//-----------------------------------------------------------------------------------------------
bool Keyboard::WasKeyPressedDown( keys checkKeys ) const
{
	if( m_wasKeyDown[ checkKeys ] )
		return true;

	return false;
}


//-----------------------------------------------------------------------------------------------
bool Keyboard::IsKeyPressedDownAndWasNotBefore( keys checkKey ) const
{
	if( m_isKeyDown[ checkKey ] && !m_wasKeyDown[ checkKey ] )
		return true;

	return false;
}


//-----------------------------------------------------------------------------------------------
bool Keyboard::IsCharPressedDown( unsigned char checkChar ) const
{
	if( m_isCharDown[ checkChar ] )
		return true;

	return false;
}


//-----------------------------------------------------------------------------------------------
bool Keyboard::IsShiftBeingHeld() const
{
	if( m_isKeyDown[ KEY_SHIFT ] )
		return true;

	return false;
}


//-----------------------------------------------------------------------------------------------
bool Keyboard::IsCapsLockOn() const
{
	if( GetKeyState( VK_CAPITAL ) )
		return true;

	return false;
}


//-----------------------------------------------------------------------------------------------
void Keyboard::Update()
{
	for( int charIndex = 0; charIndex < NUM_KEYBOARD_CHARS; ++charIndex )
	{
		m_isCharDown[ charIndex ] = false;
	}

	memcpy( &m_wasKeyDown, &m_isKeyDown, sizeof( m_isKeyDown ) );
}