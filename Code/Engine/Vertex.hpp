#ifndef include_Vertex
#define include_Vertex
#pragma once

//-----------------------------------------------------------------------------------------------
#include "Color.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "MathFunctions.hpp"


//-----------------------------------------------------------------------------------------------
struct Vertex
{
public:
	Vertex() : m_position( 0.f, 0.f, 0.f ), m_color( 0.f, 0.f, 0.f ), m_texCoords( 0.f, 0.f ), m_normal( 0.f, 0.f, 0.f ), m_tangent( 0.f, 0.f, 0.f ) {}
	Vertex( Vector3 position, Color color, Vector2 texCoords, Vector3 normal );
	bool operator==( const Vertex& vert ) const;
	void SetTangent( const Vertex& previousAdjacentVertex, const Vertex& nextAdjacentVertex );

	Vector3		m_position;
	Color		m_color;
	Vector2		m_texCoords;
	Vector3		m_normal;
	Vector3		m_tangent;
};


//-----------------------------------------------------------------------------------------------
inline Vertex::Vertex( Vector3 position, Color color, Vector2 texCoords, Vector3 normal )
	 : m_position( position )
	 , m_color( color )
	 , m_texCoords( texCoords )
	 , m_normal( normal )
{
	m_normal.Normalize();
}


//-----------------------------------------------------------------------------------------------
inline bool Vertex::operator==( const Vertex& vert ) const
{
	if( this->m_position == vert.m_position && this->m_color == vert.m_color && this->m_texCoords == vert.m_texCoords && this->m_normal == vert.m_normal )
		return true;
	else
		return false;
}


//-----------------------------------------------------------------------------------------------
inline void Vertex::SetTangent( const Vertex& previousAdjacentVertex, const Vertex& nextAdjacentVertex )
{
	ComputeSurfaceTangentsAtVertex( this->m_tangent, this->m_position, this->m_normal, this->m_texCoords, previousAdjacentVertex.m_position, previousAdjacentVertex.m_texCoords, nextAdjacentVertex.m_position, nextAdjacentVertex.m_texCoords );
}


#endif // include_Vertex