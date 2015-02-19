#ifndef include_GameCommon
#define include_GameCommon
#pragma once

//-----------------------------------------------------------------------------------------------
#include "../Engine/Vector2.hpp"
#include "../Engine/IntVector2.hpp"


//-----------------------------------------------------------------------------------------------
#define STATIC


//-----------------------------------------------------------------------------------------------
const float ONE_OVER_THREE = 1.f / 3.f;
const float ONE_OVER_SIX = 1.f / 6.f;
const float TWO_OVER_SIX = 2.f / 6.f;
const float FOUR_OVER_SIX = 4.f / 6.f;
const float FIVE_OVER_SIX = 5.f / 6.f;
const float SIXTEEN_BY_NINE = 16.f / 9.f;
const float ONE_OVER_FIFTEEN = 1.f / 15.f;
const float ONE_OVER_SIXTEEN = 1.f / 16.f;
const float ONE_OVER_TWENTYFOUR = 1.f / 24.f;
const float SQRT_OF_THREE = sqrt( 3.f );
const double FRAME_TIME_SECONDS = 1.0 / 60.0;


//-----------------------------------------------------------------------------------------------
class Game;
extern Game g_game;
class DeveloperConsole;
extern DeveloperConsole g_developerConsole;


//-----------------------------------------------------------------------------------------------
typedef Vector2 WorldCoords;
typedef IntVector2 HexTileCoords;


#endif // include_GameCommon