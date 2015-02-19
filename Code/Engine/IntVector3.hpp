#ifndef include_IntVector3
#define include_IntVector3
#pragma once

//-----------------------------------------------------------------------------------------------
struct IntVector3
{
public:
	IntVector3() : x( 0 ), y( 0 ), z( 0 ) {}
	IntVector3( int initialX, int initialY, int initialZ ) : x( initialX ), y( initialY ), z( initialZ ) {}
	bool operator==( const IntVector3& vec ) const;
	bool operator!=( const IntVector3& vec ) const;
	bool operator<( const IntVector3& vec ) const;
	bool operator>( const IntVector3& vec ) const;

	int x;
	int y;
	int z;
};


//-----------------------------------------------------------------------------------------------
inline bool IntVector3::operator==( const IntVector3& vec ) const
{
	if( this->x == vec.x && this->y == vec.y && this->z == vec.z )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
inline bool IntVector3::operator!=( const IntVector3& vec ) const
{
	if( this->x != vec.x || this->y != vec.y || this->z != vec.z )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
inline bool IntVector3::operator<( const IntVector3& vec ) const
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
inline bool IntVector3::operator>( const IntVector3& vec ) const
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


#endif // include_IntVector3