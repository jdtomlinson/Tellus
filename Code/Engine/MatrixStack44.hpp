#ifndef include_MatrixStack44
#define include_MatrixStack44
#pragma once

//-----------------------------------------------------------------------------------------------
#include <stack>
#include "Matrix44.hpp"


//-----------------------------------------------------------------------------------------------
class MatrixStack44
{
public:
	MatrixStack44();
	void PushMatrix();
	void PopMatrix();
	void MakeIdentity();
	const Matrix44& GetCurrentMatrix() const;
	Matrix44& GetCurrentMatrix();
	void ApplyTranslation( float translateX, float translateY, float translateZ );
	void ApplyRotation( float angleDegrees, float rotateX, float rotateY, float rotateZ );
	void ApplyScale( float scaleX, float scaleY, float scaleZ );
	void ApplyOrtho( float leftCoord, float rightCoord, float bottomCoord, float topCoord, float zNearDistance, float zFarDistance );
	void ApplyPerspective( float fovyDegrees, float aspectRatio, float zNearDistance, float zFarDistance );

	std::stack<Matrix44>	m_matrixStack;
};


//-----------------------------------------------------------------------------------------------
inline MatrixStack44::MatrixStack44()
{
	m_matrixStack.push( Matrix44() );
	MakeIdentity();
}


//-----------------------------------------------------------------------------------------------
inline void MatrixStack44::PushMatrix()
{
	m_matrixStack.push( m_matrixStack.top() );
}


//-----------------------------------------------------------------------------------------------
inline void MatrixStack44::PopMatrix()
{
	if( m_matrixStack.size() > 1 )
		m_matrixStack.pop();
}


//-----------------------------------------------------------------------------------------------
inline void MatrixStack44::MakeIdentity()
{
	if( m_matrixStack.empty() )
		return;

	Matrix44 identityMat;
	identityMat.MakeIdentity();

	m_matrixStack.top() = identityMat;
}


//-----------------------------------------------------------------------------------------------
inline const Matrix44& MatrixStack44::GetCurrentMatrix() const
{
	return m_matrixStack.top();
}


//-----------------------------------------------------------------------------------------------
inline Matrix44& MatrixStack44::GetCurrentMatrix()
{
	return m_matrixStack.top();
}


//-----------------------------------------------------------------------------------------------
inline void MatrixStack44::ApplyTranslation( float translateX, float translateY, float translateZ )
{
	Matrix44 translateMatrix;
	translateMatrix.MakeTranslation( translateX, translateY, translateZ );
	m_matrixStack.top().ApplyTransformation( translateMatrix );
}


//-----------------------------------------------------------------------------------------------
inline void MatrixStack44::ApplyRotation( float angleDegrees, float rotateX, float rotateY, float rotateZ )
{
	Matrix44 rotateMatrix;
	rotateMatrix.MakeRotation( angleDegrees, rotateX, rotateY, rotateZ );
	m_matrixStack.top().ApplyTransformation( rotateMatrix );
}


//-----------------------------------------------------------------------------------------------
inline void MatrixStack44::ApplyScale( float scaleX, float scaleY, float scaleZ )
{
	Matrix44 scaleMatrix;
	scaleMatrix.MakeScale( scaleX, scaleY, scaleZ );
	m_matrixStack.top().ApplyTransformation( scaleMatrix );
}


//-----------------------------------------------------------------------------------------------
inline void MatrixStack44::ApplyOrtho( float leftCoord, float rightCoord, float bottomCoord, float topCoord, float zNearDistance, float zFarDistance )
{
	Matrix44 orthoMatrix;
	orthoMatrix.MakeOrtho( leftCoord, rightCoord, bottomCoord, topCoord, zNearDistance, zFarDistance );
	m_matrixStack.top().ApplyTransformation( orthoMatrix );
}


//-----------------------------------------------------------------------------------------------
inline void MatrixStack44::ApplyPerspective( float fovyDegrees, float aspectRatio, float zNearDistance, float zFarDistance )
{
	Matrix44 perspectiveMatrix;
	perspectiveMatrix.MakePerspective( fovyDegrees, aspectRatio, zNearDistance, zFarDistance );
	m_matrixStack.top().ApplyTransformation( perspectiveMatrix );
}


#endif