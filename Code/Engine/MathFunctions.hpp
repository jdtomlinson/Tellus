#ifndef include_MathFunction
#define include_MathFunction
#pragma once

//-----------------------------------------------------------------------------------------------
#include "Vector2.hpp"
#include "Vector3.hpp"


//-----------------------------------------------------------------------------------------------
const float pi = 3.1415926535897932384626433832795f;
const float TWO_PI = 2.f * pi;
const float ONE_OVER_PI = 1.f / pi;
const float MARGIN_OF_ERROR = 0.001f;
const float ONE_OVER_ONE_HUNDRED_EIGHTY = 1.f / 180.f;


//-----------------------------------------------------------------------------------------------
inline bool FloatsApproximatelyEqual( float value1, float value2 )
{
	if( value1 < value2 + MARGIN_OF_ERROR && value1 > value2 - MARGIN_OF_ERROR )
		return true;

	return false;
}


//-----------------------------------------------------------------------------------------------
inline float ConvertRadiansToDegrees( float rad )
{
	return ( rad * ( 180.f * ONE_OVER_PI) );
}


//-----------------------------------------------------------------------------------------------
inline float ConvertDegreesToRadians( float deg )
{
	return ( deg * ( pi * ONE_OVER_ONE_HUNDRED_EIGHTY ) );
}


//-----------------------------------------------------------------------------------------------
inline float GetSquaredDistanceBetweenPoints2D( const Vector2& point1, const Vector2& point2 )
{
	float differenceX = point1.x - point2.x;
	float differenceY = point1.y - point2.y;
	return ( ( differenceX * differenceX ) + ( differenceY * differenceY ) );
}


//-----------------------------------------------------------------------------------------------
inline int ClampInt( int val, int minInt, int maxInt )
{
	if( val < minInt )
		return minInt;

	if( val > maxInt )
		return maxInt;

	return val;
}


//-----------------------------------------------------------------------------------------------
inline float ClampFloat( float val, float minFloat, float maxFloat )
{
	if( val < minFloat )
		return minFloat;

	if( val > maxFloat )
		return maxFloat;

	return val;
}


//-----------------------------------------------------------------------------------------------
inline float GetRandomPercentage()
{
	return static_cast<float>( rand() ) / static_cast<float>( RAND_MAX );
}


//-----------------------------------------------------------------------------------------------
inline float GetRandomNoiseValue( float x, float y )
{
	int n = (int) x + ( (int) y * 57 );
	n = ( n<<13 )^n;
	return ( 1.f - (float) ( ( n * ( n * n * 15731 + 789221 ) + 1376312589 ) & 0x7fffffff ) / 1073741824.f );
}


//-----------------------------------------------------------------------------------------------
inline float SmoothStep( float p )
{
	return ( 3.f * ( p * p ) ) - ( 2.f * ( p * p * p ) );
}


//-----------------------------------------------------------------------------------------------
inline float DotProduct( const Vector2& vec1, const Vector2& vec2 )
{
	return ( vec1.x * vec2.x ) + ( vec1.y * vec2.y );
}


//-----------------------------------------------------------------------------------------------
inline float DotProduct( const Vector3& vec1, const Vector3& vec2 )
{
	return ( vec1.x * vec2.x ) + ( vec1.y * vec2.y ) + ( vec1.z * vec2.z );
}


//-----------------------------------------------------------------------------------------------
inline Vector3 CrossProduct( const Vector3& vec1, const Vector3& vec2 )
{
	Vector3 returnVec;
	returnVec.x = ( vec1.y * vec2.z ) - ( vec2.y * vec1.z );
	returnVec.y = -( vec1.x * vec2.z ) + ( vec2.x * vec1.z );
	returnVec.z = ( vec1.x * vec2.y ) - ( vec2.x * vec1.y );

	return returnVec;
}


//-----------------------------------------------------------------------------------------------
inline float VectorLength( const Vector2& vec )
{
	return sqrt( vec.x + vec.y );
}


//-----------------------------------------------------------------------------------------------
inline float VectorLength( const Vector3& vec )
{
	return sqrt( vec.x + vec.y + vec.z );
}


//-----------------------------------------------------------------------------------------------
inline bool ComputeSurfaceTangentsAtVertex(
	Vector3& vertexSurfaceTangent_out,
	const Vector3& thisVertexPosition,
	const Vector3& thisVertexNormal,
	const Vector2& thisVertexTexCoords,
	const Vector3& previousAdjacentVertexPosition,
	const Vector2& previousAdjacentVertexTexCoords,
	const Vector3& nextAdjacentVertexPosition,
	const Vector2& nextAdjacnetVertexTexCoords )
{
	Vector3 vecToPrevious = previousAdjacentVertexPosition - thisVertexPosition;
	Vector3 vecToNext = nextAdjacentVertexPosition - thisVertexPosition;

	Vector2 texToPrevious = previousAdjacentVertexTexCoords - thisVertexTexCoords;
	Vector2 texToNext = nextAdjacnetVertexTexCoords - thisVertexTexCoords;

	float oneOverDeterminant = 1.f / ( ( texToPrevious.x * texToNext.y ) - ( texToNext.x * texToPrevious.y ) );

	Vector3 uDirectionInWorldSpace(	( texToNext.y * vecToPrevious.x - texToPrevious.y * vecToNext.x ), ( texToNext.y * vecToPrevious.y - texToPrevious.y * vecToNext.y ), ( texToNext.y * vecToPrevious.z - texToPrevious.y * vecToNext.z ) );
	Vector3 vDirectionInWorldSpace( ( texToPrevious.x * vecToNext.x - texToNext.x * vecToPrevious.x ), ( texToPrevious.x * vecToNext.y - texToNext.x * vecToPrevious.y ), ( texToPrevious.x * vecToNext.z - texToNext.x * vecToPrevious.z ) );

	uDirectionInWorldSpace *= oneOverDeterminant;
	vDirectionInWorldSpace *= oneOverDeterminant;

	Vector3& tangentFromCalculations = uDirectionInWorldSpace;
	Vector3& bitangentFromCalculations = vDirectionInWorldSpace;
	Vector3 bitangentFromCross = CrossProduct( thisVertexNormal, tangentFromCalculations );
	bitangentFromCross.Normalize();
	Vector3 tangentFromCross = CrossProduct( bitangentFromCross, thisVertexNormal );

	float bitangentDotCrossBitangent = DotProduct( bitangentFromCalculations, bitangentFromCross );
	bool isRightHanded = ( bitangentDotCrossBitangent >= 0.f );
	if( !isRightHanded )
	{
		bitangentFromCross *= -1.f;
	}

	vertexSurfaceTangent_out = tangentFromCross;
	return isRightHanded;
}


#endif // include_MathFunctions