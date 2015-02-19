#include "Color.hpp"


//-----------------------------------------------------------------------------------------------
Color Color::Black( 0.f, 0.f, 0.f, 1.f );
Color Color::White( 1.f, 1.f, 1.f, 1.f );
Color Color::Red( 1.f, 0.f, 0.f );
Color Color::Green( 0.f, 1.f, 0.f );
Color Color::Blue( 0.f, 0.f, 1.f );
Color Color::Yellow( 1.f, 1.f, 0.f );
Color Color::Cyan( 0.f, 1.f, 1.f );
Color Color::Magenta( 1.f, 0.f, 1.f );


//-----------------------------------------------------------------------------------------------
void Color::operator+=( const Color& color )
{
	this->r += color.r;
	this->g += color.g;
	this->b += color.b;
	this->Clamp();
}


//-----------------------------------------------------------------------------------------------
void Color::operator-=( const Color& color )
{
	this->r -= color.r;
	this->g -= color.g;
	this->b -= color.b;
	this->Clamp();
}


//-----------------------------------------------------------------------------------------------
void Color::operator*=( float val )
{
	this->r *= val;
	this->g *= val;
	this->b *= val;
	this->Clamp();
}


//-----------------------------------------------------------------------------------------------
bool Color::operator==( const Color& color ) const
{
	if( this->r == color.r && this->g == color.g && this->b == color.b && this->a && color.a )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
void Color::Clamp()
{
	if( this->r < 0.f )
		this->r = 0.f;
	if( this->g < 0.f )
		this->g = 0.f;
	if( this->b < 0.f )
		this->b = 0.f;
	if( this->a < 0.f )
		this->a = 0.f;

	if( this->r > 1.f )
		this->r = 1.f;
	if( this->g > 1.f )
		this->g = 1.f;
	if( this->b > 1.f )
		this->b = 1.f;
	if( this->a > 1.f )
		this->a = 1.f;
}