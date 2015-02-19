#ifndef include_IntVector2
#define include_IntVector2
#pragma once

//-----------------------------------------------------------------------------------------------
struct IntVector2
{
public:
	IntVector2() : x( 0 ), y( 0 ) {}
	IntVector2( int initialX, int initialY ) : x( initialX ), y( initialY ) {}
	IntVector2 operator+( const IntVector2& vec ) const;
	void operator+=( const IntVector2& vec );
	IntVector2 operator-( const IntVector2& vec ) const;
	void operator-=( const IntVector2& vec );
	IntVector2 operator*( int val ) const;
	friend IntVector2 operator*( int val, const IntVector2& vec );
	void operator*=( int val );
	bool operator==( const IntVector2& vec ) const;
	bool operator!=( const IntVector2& vec ) const;
	bool operator<( const IntVector2& vec ) const;
	bool operator>( const IntVector2& vec ) const;

	int x;
	int y;
};


//-----------------------------------------------------------------------------------------------
inline IntVector2 IntVector2::operator+( const IntVector2& vec ) const
{
	return IntVector2( this->x + vec.x, this->y + vec.y );
}


//-----------------------------------------------------------------------------------------------
inline void IntVector2::operator+=( const IntVector2& vec )
{
	this->x += vec.x;
	this->y += vec.y;
}


//-----------------------------------------------------------------------------------------------
inline IntVector2 IntVector2::operator-( const IntVector2& vec ) const
{
	return IntVector2( this->x - vec.x, this->y - vec.y );
}


//-----------------------------------------------------------------------------------------------
inline void IntVector2::operator-=( const IntVector2& vec )
{
	this->x -= vec.x;
	this->y -= vec.y;
}


//-----------------------------------------------------------------------------------------------
inline IntVector2 IntVector2::operator*( int val ) const
{
	return IntVector2( this->x * val, this->y * val );
}


//-----------------------------------------------------------------------------------------------
inline IntVector2 operator*( int val, const IntVector2& vec )
{
	return IntVector2( vec.x * val, vec.y * val );
}


//-----------------------------------------------------------------------------------------------
inline void IntVector2::operator*=( int val )
{
	this->x *= val;
	this->y *= val;
}


//-----------------------------------------------------------------------------------------------
inline bool IntVector2::operator==( const IntVector2& vec ) const
{
	if( this->x == vec.x && this->y == vec.y )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
inline bool IntVector2::operator!=( const IntVector2& vec ) const
{
	if( this->x != vec.x || this->y != vec.y )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
inline bool IntVector2::operator<( const IntVector2& vec ) const
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
inline bool IntVector2::operator>( const IntVector2& vec ) const
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


#endif // include_IntVector2