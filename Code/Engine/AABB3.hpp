#ifndef include_AABB3
#define include_AABB3
#pragma once

//-----------------------------------------------------------------------------------------------
#include "Vector3.hpp"


//-----------------------------------------------------------------------------------------------
class AABB3
{
public:
	AABB3() : m_centerPosition( 0.f, 0.f, 0.f ), m_xAxisHalfLength( 0.f ), m_yAxisHalfLength( 0.f ),m_zAxisHalfLength( 0.f ) {}
	AABB3( const Vector3& centerPosition, float lengthXAxis, float lengthYAxis, float lengthZAxis );

	Vector3				m_centerPosition;
	float				m_xAxisHalfLength;
	float				m_yAxisHalfLength;
	float				m_zAxisHalfLength;
};


//-----------------------------------------------------------------------------------------------
inline AABB3::AABB3( const Vector3& centerPosition, float lengthXAxis, float lengthYAxis, float lengthZAxis )
	: m_centerPosition( centerPosition )
	, m_xAxisHalfLength( lengthXAxis * 0.5f )
	, m_yAxisHalfLength( lengthYAxis * 0.5f )
	, m_zAxisHalfLength( lengthZAxis * 0.5f )
{

}


#endif // include_AABB3