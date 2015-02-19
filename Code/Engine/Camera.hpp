#ifndef include_Camera
#define include_Camera
#pragma once

//-----------------------------------------------------------------------------------------------
#include "Vector3.hpp"
#include "EulerAngles.hpp"


//-----------------------------------------------------------------------------------------------
class Camera
{
public:
	Camera() : m_position( 0.f, 0.f, 0.f ), m_orientation( 0.f, 0.f, 0.f ) {}
	Camera( const Vector3& position ) : m_position( position ), m_orientation( 0.f, 0.f, 0.f ) {}

	Vector3 m_position;
	EulerAngles m_orientation;
};


#endif // include_Camera