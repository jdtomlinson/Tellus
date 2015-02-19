#ifndef include_EulerAngles
#define include_EulerAngles
#pragma once

//-----------------------------------------------------------------------------------------------
struct EulerAngles
{
public:
	EulerAngles() : yaw( 0.f ), pitch( 0.f ), roll( 0.f ) {}
	EulerAngles( float initialYaw, float initialPitch, float initialRoll ) : yaw( initialYaw ), pitch( initialPitch ), roll( initialRoll ) {}
	void operator+=( const EulerAngles& eul );
	void operator*=( float val );

	float yaw;
	float pitch;
	float roll;
};


//-----------------------------------------------------------------------------------------------
inline void EulerAngles::operator+=( const EulerAngles& eul )
{
	this->yaw += eul.yaw;
	this->pitch += eul.pitch;
	this->roll += eul.roll;
}


//-----------------------------------------------------------------------------------------------
inline void EulerAngles::operator*=( float val )
{
	this->yaw *= val;
	this->pitch *= val;
	this->roll *= val;
}


#endif // include_EulerAngles