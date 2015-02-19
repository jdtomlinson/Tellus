#ifndef include_Color
#define include_Color
#pragma once

//-----------------------------------------------------------------------------------------------
struct Color
{
	Color() : r( 0.f ), g( 0.f ), b( 0.f ), a( 1.f ) {}
	Color( float red, float green, float blue ) : r( red ), g( green ), b( blue ), a( 1.f ) {}
	Color( float red, float green, float blue, float alpha ) : r( red ), g( green ), b( blue ), a( alpha ) {}
	void operator+=( const Color& color );
	void operator-=( const Color& color );
	void operator*=( float val );
	bool operator==( const Color& color ) const;
	void Clamp();

	float			r;
	float			g;
	float			b;
	float			a;
	static Color	Black;
	static Color	White;
	static Color	Red;
	static Color	Green;
	static Color	Blue;
	static Color	Yellow;
	static Color	Cyan;
	static Color	Magenta;
};


#endif // include_Color