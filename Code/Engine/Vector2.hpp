#ifndef include_Vector2
#define include_Vector2
#pragma once

//-----------------------------------------------------------------------------------------------
#include <math.h>


//-----------------------------------------------------------------------------------------------
struct Vector2
{
public:
	Vector2() : x( 0.f ), y( 0.f ) {}
	Vector2( float initialX, float initialY ) : x( initialX ), y ( initialY ) {}
	Vector2 operator+( const Vector2& vec ) const;
	void operator+=( const Vector2& vec );
	Vector2 operator-( const Vector2& vec ) const;
	void operator-=( const Vector2& vec );
	Vector2 operator*( float val ) const;
	friend Vector2 operator*( float val, const Vector2& vec );
	void operator*=( float val );
	bool operator==( const Vector2& vec ) const;
	bool operator!=( const Vector2& vec ) const;
	bool operator<( const Vector2& vec ) const;
	bool operator>( const Vector2& vec ) const;
	float GetLength() const;
	void Normalize();

	float x;
	float y;
};


//-----------------------------------------------------------------------------------------------
inline Vector2 Vector2::operator+( const Vector2& vec ) const
{
	return Vector2( this->x + vec.x, this->y + vec.y );
}


//-----------------------------------------------------------------------------------------------
inline void Vector2::operator+=( const Vector2& vec )
{
	this->x += vec.x;
	this->y += vec.y;
}


//-----------------------------------------------------------------------------------------------
inline Vector2 Vector2::operator-( const Vector2& vec ) const
{
	return Vector2( this->x - vec.x, this->y - vec.y );
}


//-----------------------------------------------------------------------------------------------
inline void Vector2::operator-=( const Vector2& vec )
{
	this->x -= vec.x;
	this->y -= vec.y;
}


//-----------------------------------------------------------------------------------------------
inline Vector2 Vector2::operator*( float val ) const
{
	return Vector2( this->x * val, this->y * val );
}


//-----------------------------------------------------------------------------------------------
inline Vector2 operator*( float val, const Vector2& vec )
{
	return Vector2( vec.x * val, vec.y * val );
}


//-----------------------------------------------------------------------------------------------
inline void Vector2::operator*=( float val )
{
	this->x *= val;
	this->y *= val;
}


//-----------------------------------------------------------------------------------------------
inline bool Vector2::operator==( const Vector2& vec ) const
{
	if( this->x == vec.x && this->y == vec.y )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
inline bool Vector2::operator!=( const Vector2& vec ) const
{
	if( this->x != vec.x || this->y != vec.y )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
inline bool Vector2::operator<( const Vector2& vec ) const
{
	if( this->y < vec.y )
		return true;
	else if( this->y == vec.y )
	{
		if( this->x < vec.x )
			return true;
	}

	return false;
}


//-----------------------------------------------------------------------------------------------
inline bool Vector2::operator>( const Vector2& vec ) const
{
	if( this->y > vec.y )
		return true;
	else if( this->y == vec.y )
	{
		if( this->x > vec.x )
			return true;
	}

	return false;
}


//-----------------------------------------------------------------------------------------------
inline float Vector2::GetLength() const
{
	return sqrt( ( this->x * this->x ) + ( this->y * this->y ) );
}


//-----------------------------------------------------------------------------------------------
inline void Vector2::Normalize()
{
	float lenSquared = ( ( this->x * this->x ) + ( this->y * this->y ) );
	float oneOverLength = 1.f;

	if( lenSquared != 0.f )
		oneOverLength = 1.f / sqrt( lenSquared );

	this->x *= oneOverLength;
	this->y *= oneOverLength;
}


#endif // include_Vector2