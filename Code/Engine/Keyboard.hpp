#ifndef include_Keyboard
#define include_Keyboard
#pragma once

//-----------------------------------------------------------------------------------------------
#include <windows.h>
#include "EngineCommon.hpp"


//-----------------------------------------------------------------------------------------------
enum keys
{
	KEY_0				= '0',
	KEY_1				= '1',
	KEY_2				= '2',
	KEY_3				= '3',
	KEY_4				= '4',
	KEY_5				= '5',
	KEY_6				= '6',
	KEY_7				= '7',
	KEY_8				= '8',
	KEY_9				= '9',
	KEY_A				= 'A',
	KEY_B				= 'B',
	KEY_C				= 'C',
	KEY_D				= 'D',
	KEY_E				= 'E',
	KEY_F				= 'F',
	KEY_G				= 'G',
	KEY_H				= 'H',
	KEY_I				= 'I',
	KEY_J				= 'J',
	KEY_K				= 'K',
	KEY_L				= 'L',
	KEY_M				= 'M',
	KEY_N				= 'N',
	KEY_O				= 'O',
	KEY_P				= 'P',
	KEY_Q				= 'Q',
	KEY_R				= 'R',
	KEY_S				= 'S',
	KEY_T				= 'T',
	KEY_U				= 'U',
	KEY_V				= 'V',
	KEY_W				= 'W',
	KEY_X				= 'X',
	KEY_Y				= 'Y',
	KEY_Z				= 'Z',
	KEY_SPACE			= VK_SPACE,
	KEY_ENTER			= VK_RETURN,
	KEY_BACK			= VK_BACK,
	KEY_DELETE			= VK_DELETE,
	KEY_ESCAPE			= VK_ESCAPE,
	KEY_SHIFT			= VK_SHIFT,
	KEY_END				= VK_END,
	KEY_HOME			= VK_HOME,
	KEY_LEFT_ARROW		= VK_LEFT,
	KEY_UP_ARROW		= VK_UP,
	KEY_RIGHT_ARROW		= VK_RIGHT,
	KEY_DOWN_ARROW		= VK_DOWN,
	KEY_PLUS			= VK_OEM_PLUS,
	KEY_COMMA			= VK_OEM_COMMA,
	KEY_MINUS			= VK_OEM_MINUS,
	KEY_PERIOD			= VK_OEM_PERIOD,
	KEY_SEMI_COLON		= 0xBA,
	KEY_SLASH			= 0xBF,
	KEY_TILDE			= 0xC0,
	KEY_OPEN_BRACKET	= 0xDB,
	KEY_BACKSLASH		= 0xDC,
	KEY_CLOSE_BRACKET	= 0xDD,
	KEY_QUOTE			= 0xDE,
};


//-----------------------------------------------------------------------------------------------
class Keyboard
{
public:
	Keyboard();
	void SetKeyUp( unsigned char setKey );
	void SetKeyDown( unsigned char setKey );
	void SetCharDown( unsigned char setChar );
	bool IsKeyPressedDown( keys checkKey ) const;
	bool WasKeyPressedDown( keys checkKey ) const;
	bool IsKeyPressedDownAndWasNotBefore( keys checkKey ) const;
	bool IsCharPressedDown( unsigned char checkChar ) const;
	bool IsShiftBeingHeld() const;
	bool IsCapsLockOn() const;
	void Update();

	bool		m_isKeyDown[ NUM_VIRTUAL_KEYS ];
	bool		m_wasKeyDown[ NUM_VIRTUAL_KEYS ];
	bool		m_isCharDown[ NUM_KEYBOARD_CHARS ];
};


#endif // include_Keyboard