#ifndef include_Vector3
#define include_Vector3
#pragma once

//-----------------------------------------------------------------------------------------------
#include <math.h>


//-----------------------------------------------------------------------------------------------
struct Vector3
{
public:
	Vector3() : x( 0.f ), y( 0.f ), z( 0.f ) {}
	Vector3( float initialX, float initialY, float initialZ ) : x( initialX ), y ( initialY ), z( initialZ ) {}
	Vector3 operator+( const Vector3& vec ) const;
	void operator+=( const Vector3& vec );
	Vector3 operator-( const Vector3& vec ) const;
	void operator-=( const Vector3& vec );
	Vector3 operator*( float val ) const;
	friend Vector3 operator*( float val, const Vector3& vec );
	void operator*=( float val );
	bool operator==( const Vector3& vec ) const;
	bool operator!=( const Vector3& vec ) const;
	bool operator<( const Vector3& vec ) const;
	bool operator>( const Vector3& vec ) const;
	float GetLength() const;
	void Normalize();

	float x;
	float y;
	float z;
};


//-----------------------------------------------------------------------------------------------
inline Vector3 Vector3::operator+( const Vector3& vec ) const
{
	return Vector3( this->x + vec.x, this->y + vec.y, this->z + vec.z );
}


//-----------------------------------------------------------------------------------------------
inline void Vector3::operator+=( const Vector3& vec )
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
}


//-----------------------------------------------------------------------------------------------
inline Vector3 Vector3::operator-( const Vector3& vec ) const
{
	return Vector3( this->x - vec.x, this->y - vec.y, this->z - vec.z );
}


//-----------------------------------------------------------------------------------------------
inline void Vector3::operator-=( const Vector3& vec )
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
}


//-----------------------------------------------------------------------------------------------
inline Vector3 Vector3::operator*( float val ) const
{
	return Vector3( this->x * val, this->y * val, this->z * val );
}


//-----------------------------------------------------------------------------------------------
inline Vector3 operator*( float val, const Vector3& vec )
{
	return Vector3( vec.x * val, vec.y * val, vec.z * val );
}


//-----------------------------------------------------------------------------------------------
inline void Vector3::operator*=( float val )
{
	this->x *= val;
	this->y *= val;
	this->z *= val;
}


//-----------------------------------------------------------------------------------------------
inline bool Vector3::operator==( const Vector3& vec ) const
{
	if( this->x == vec.x && this->y == vec.y && this->z == vec.z )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
inline bool Vector3::operator!=( const Vector3& vec ) const
{
	if( this->x != vec.x || this->y != vec.y || this->z != vec.z )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
inline bool Vector3::operator<( const Vector3& vec ) const
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

	return false;
}


//-----------------------------------------------------------------------------------------------
inline bool Vector3::operator>( const Vector3& vec ) const
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

	return false;
}


//-----------------------------------------------------------------------------------------------
inline float Vector3::GetLength() const
{
	return sqrt( ( this->x * this->x ) + ( this->y * this->y ) + ( this->z * this->z ) );
}


//-----------------------------------------------------------------------------------------------
inline void Vector3::Normalize()
{
	float length = this->GetLength();
	float oneOverLength = 1.f;

	if( length != 0.f )
		oneOverLength = 1.f / length ;

	this->x *= oneOverLength;
	this->y *= oneOverLength;
	this->z *= oneOverLength;
}


#endif // include_Vector3