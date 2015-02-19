#ifndef include_HeightMapVertex
#define include_HeightMapVertex
#pragma once

//-----------------------------------------------------------------------------------------------
#include "../Engine/Vertex.hpp"


//-----------------------------------------------------------------------------------------------
class HeightMapVertex
{
public:
	HeightMapVertex( const Vertex& vert, float height ) : m_vertex( vert ), m_height( height ) {}

	Vertex	m_vertex;
	float	m_height;
};


#endif // include_HeightMapVertex