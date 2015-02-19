#ifndef include_Vector4
#define include_Vector4
#pragma once

//-----------------------------------------------------------------------------------------------
#include <math.h>


//-----------------------------------------------------------------------------------------------
struct Vector4
{
public:
	Vector4() : x( 0.f ), y( 0.f ), z( 0.f ), w( 0.f ) {}
	Vector4( float initialX, float initialY, float initialZ, float initialW ) : x( initialX ), y ( initialY ), z( initialZ ), w( initialW ) {}
	void operator+=( const Vector4& vec );
	Vector4 operator-( const Vector4& vec ) const;
	void operator-=( const Vector4& vec );
	void operator*=( float val );
	bool operator==( const Vector4& vec ) const;
	bool operator!=( const Vector4& vec ) const;
	bool operator<( const Vector4& vec ) const;
	bool operator>( const Vector4& vec ) const;
	Vector4 Normalize();

	float x;
	float y;
	float z;
	float w;
};


//-----------------------------------------------------------------------------------------------
inline void Vector4::operator+=( const Vector4& vec )
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	this->w += vec.w;
}


//-----------------------------------------------------------------------------------------------
inline Vector4 Vector4::operator-( const Vector4& vec ) const
{
	return Vector4( this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w );
}


//-----------------------------------------------------------------------------------------------
inline void Vector4::operator-=( const Vector4& vec )
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	this->w -= vec.w;
}


//-----------------------------------------------------------------------------------------------
inline void Vector4::operator*=( float val )
{
	this->x *= val;
	this->y *= val;
	this->z *= val;
	this->w *= val;
}


//-----------------------------------------------------------------------------------------------
inline bool Vector4::operator==( const Vector4& vec ) const
{
	if( this->x == vec.x && this->y == vec.y && this->z == vec.z && this->w == vec.w )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
inline bool Vector4::operator!=( const Vector4& vec ) const
{
	if( this->x != vec.x || this->y != vec.y || this->z != vec.z || this->w != vec.w )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
inline bool Vector4::operator<( const Vector4& vec ) const
{
	if( this->w < vec.w )
		return true;
	else if( this->w == vec.w )
	{
		if( this->z < vec.z )
			return true;
		else if( this->z == vec.z )
		{
			if( this->y < vec.y )
				return true;
			else if( this->y == vec.y )
			{
				if( this->x < vec.x )
					return true;
			}
		}
	}

	return false;
}


//-----------------------------------------------------------------------------------------------
inline bool Vector4::operator>( const Vector4& vec ) const
{
	if( this->w > vec.w )
		return true;
	else if( this->w == vec.w )
	{
		if( this->z > vec.z )
			return true;
		else if( this->z == vec.z )
		{
			if( this->y > vec.y )
				return true;
			else if( this->y == vec.y )
			{
				if( this->x > vec.x )
					return true;
			}
		}
	}

	return false;
}


//-----------------------------------------------------------------------------------------------
inline Vector4 Vector4::Normalize()
{
	float lenSquared = ( ( this->x * this->x ) + ( this->y * this->y ) + ( this->z * this->z ) + ( this->w * this->w ) );
	float oneOverLen = 1.f;

	if( lenSquared != 0.f )
		oneOverLen = 1.f / sqrt( lenSquared );

	this->x *= oneOverLen;
	this->y *= oneOverLen;
	this->z *= oneOverLen;
	this->w *= oneOverLen;

	return *this;
}


#endif // include_Vector4