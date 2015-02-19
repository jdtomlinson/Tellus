#ifndef include_Matrix44
#define include_Matrix44
#pragma once

//-----------------------------------------------------------------------------------------------
#include "MathFunctions.hpp"


//-----------------------------------------------------------------------------------------------
class Matrix44
{
public:
	Matrix44();
	void ApplyTransformation( const Matrix44& mat );
	void MakeIdentity();
	void MakeTranslation( float translateX, float translateY, float translateZ );
	void MakeRotation( float angleDegrees, float rotateX, float rotateY, float rotateZ );
	void MakeScale( float scaleX, float scaleY, float scaleZ );
	void MakeOrtho( float leftCoord, float rightCoord, float bottomCoord, float topCoord, float zNearDistance, float zFarDistance );
	void MakePerspective( float fovyDegrees, float aspectRatio, float zNearDistance, float zFarDistance );

	float	m_entries[16];
};


//-----------------------------------------------------------------------------------------------
inline Matrix44::Matrix44()
{
	for( int entryIndex = 0; entryIndex < 16; ++entryIndex )
	{
		m_entries[ entryIndex ] = 0.f;
	}
}


//-----------------------------------------------------------------------------------------------
inline void Matrix44::ApplyTransformation( const Matrix44& mat )
{
	Matrix44 tempMat;
	tempMat.m_entries[0] = this->m_entries[0] * mat.m_entries[0] + this->m_entries[4] * mat.m_entries[1] + this->m_entries[8] * mat.m_entries[2] + this->m_entries[12] * mat.m_entries[3];
	tempMat.m_entries[1] = this->m_entries[1] * mat.m_entries[0] + this->m_entries[5] * mat.m_entries[1] + this->m_entries[9] * mat.m_entries[2] + this->m_entries[13] * mat.m_entries[3];
	tempMat.m_entries[2] = this->m_entries[2] * mat.m_entries[0] + this->m_entries[6] * mat.m_entries[1] + this->m_entries[10] * mat.m_entries[2] + this->m_entries[14] * mat.m_entries[3];
	tempMat.m_entries[3] = this->m_entries[3] * mat.m_entries[0] + this->m_entries[7] * mat.m_entries[1] + this->m_entries[11] * mat.m_entries[2] + this->m_entries[15] * mat.m_entries[3];

	tempMat.m_entries[4] = this->m_entries[0] * mat.m_entries[4] + this->m_entries[4] * mat.m_entries[5] + this->m_entries[8] * mat.m_entries[6] + this->m_entries[12] * mat.m_entries[7];
	tempMat.m_entries[5] = this->m_entries[1] * mat.m_entries[4] + this->m_entries[5] * mat.m_entries[5] + this->m_entries[9] * mat.m_entries[6] + this->m_entries[13] * mat.m_entries[7];
	tempMat.m_entries[6] = this->m_entries[2] * mat.m_entries[4] + this->m_entries[6] * mat.m_entries[5] + this->m_entries[10] * mat.m_entries[6] + this->m_entries[14] * mat.m_entries[7];
	tempMat.m_entries[7] = this->m_entries[3] * mat.m_entries[4] + this->m_entries[7] * mat.m_entries[5] + this->m_entries[11] * mat.m_entries[6] + this->m_entries[15] * mat.m_entries[7];

	tempMat.m_entries[8] = this->m_entries[0] * mat.m_entries[8] + this->m_entries[4] * mat.m_entries[9] + this->m_entries[8] * mat.m_entries[10] + this->m_entries[12] * mat.m_entries[11];
	tempMat.m_entries[9] = this->m_entries[1] * mat.m_entries[8] + this->m_entries[5] * mat.m_entries[9] + this->m_entries[9] * mat.m_entries[10] + this->m_entries[13] * mat.m_entries[11];
	tempMat.m_entries[10] = this->m_entries[2] * mat.m_entries[8] + this->m_entries[6] * mat.m_entries[9] + this->m_entries[10] * mat.m_entries[10] + this->m_entries[14] * mat.m_entries[11];
	tempMat.m_entries[11] = this->m_entries[3] * mat.m_entries[8] + this->m_entries[7] * mat.m_entries[9] + this->m_entries[11] * mat.m_entries[10] + this->m_entries[15] * mat.m_entries[11];

	tempMat.m_entries[12] = this->m_entries[0] * mat.m_entries[12] + this->m_entries[4] * mat.m_entries[13] + this->m_entries[8] * mat.m_entries[14] + this->m_entries[12] * mat.m_entries[15];
	tempMat.m_entries[13] = this->m_entries[1] * mat.m_entries[12] + this->m_entries[5] * mat.m_entries[13] + this->m_entries[9] * mat.m_entries[14] + this->m_entries[13] * mat.m_entries[15];
	tempMat.m_entries[14] = this->m_entries[2] * mat.m_entries[12] + this->m_entries[6] * mat.m_entries[13] + this->m_entries[10] * mat.m_entries[14] + this->m_entries[14] * mat.m_entries[15];
	tempMat.m_entries[15] = this->m_entries[3] * mat.m_entries[12] + this->m_entries[7] * mat.m_entries[13] + this->m_entries[11] * mat.m_entries[14] + this->m_entries[15] * mat.m_entries[15];

	memcpy( &this->m_entries, &tempMat.m_entries, sizeof( tempMat.m_entries ) );
}


//-----------------------------------------------------------------------------------------------
inline void Matrix44::MakeIdentity()
{
	this->m_entries[0] = 1.f;
	this->m_entries[1] = 0.f;
	this->m_entries[2] = 0.f;
	this->m_entries[3] = 0.f;

	this->m_entries[4] = 0.f;
	this->m_entries[5] = 1.f;
	this->m_entries[6] = 0.f;
	this->m_entries[7] = 0.f;

	this->m_entries[8] = 0.f;
	this->m_entries[9] = 0.f;
	this->m_entries[10] = 1.f;
	this->m_entries[11] = 0.f;

	this->m_entries[12] = 0.f;
	this->m_entries[13] = 0.f;
	this->m_entries[14] = 0.f;
	this->m_entries[15] = 1.f;
}


//-----------------------------------------------------------------------------------------------
inline void Matrix44::MakeTranslation( float translateX, float translateY, float translateZ )
{
	this->MakeIdentity();

	this->m_entries[12] = translateX;
	this->m_entries[13] = translateY;
	this->m_entries[14] = translateZ;
}


//-----------------------------------------------------------------------------------------------
inline void Matrix44::MakeRotation( float angleDegrees, float rotateX, float rotateY, float rotateZ )
{
	this->MakeIdentity();
	Vector3 axisVector( rotateX, rotateY, rotateZ );
	axisVector.Normalize();
	float angleRadians = ConvertDegreesToRadians( angleDegrees );

	this->m_entries[0] = cos( angleRadians ) + ( ( axisVector.x * axisVector.x ) * ( 1 - cos( angleRadians ) ) );
	this->m_entries[1] = ( axisVector.y * axisVector.x * ( 1 - cos( angleRadians ) ) ) + ( axisVector.z * sin( angleRadians ) );
	this->m_entries[2] = ( axisVector.z * axisVector.x * ( 1 - cos( angleRadians ) ) ) - ( axisVector.y * sin( angleRadians ) );

	this->m_entries[4] = ( axisVector.x * axisVector.y * ( 1 - cos( angleRadians ) ) ) - ( axisVector.z * sin( angleRadians ) );
	this->m_entries[5] = cos( angleRadians ) + ( ( axisVector.y * axisVector.y ) * ( 1 - cos( angleRadians ) ) );
	this->m_entries[6] = ( axisVector.z * axisVector.y * ( 1 - cos( angleRadians ) ) ) + ( axisVector.x * sin( angleRadians ) );

	this->m_entries[8] = ( axisVector.x * axisVector.z * ( 1 - cos( angleRadians ) ) ) + ( axisVector.y * sin( angleRadians ) );
	this->m_entries[9] = ( axisVector.y * axisVector.z * ( 1 - cos( angleRadians ) ) ) - ( axisVector.x * sin( angleRadians ) );
	this->m_entries[10] = cos( angleRadians ) + ( ( axisVector.z * axisVector.z ) * ( 1 - cos( angleRadians ) ) );
}


//-----------------------------------------------------------------------------------------------
inline void Matrix44::MakeScale( float scaleX, float scaleY, float scaleZ )
{
	this->MakeIdentity();

	this->m_entries[0] = scaleX;
	this->m_entries[5] = scaleY;
	this->m_entries[10] = scaleZ;
}


//-----------------------------------------------------------------------------------------------
inline void Matrix44::MakeOrtho( float leftCoord, float rightCoord, float bottomCoord, float topCoord, float zNearDistance, float zFarDistance )
{
	this->MakeIdentity();

	float oneOverRightMinusLeft = 0.f;
	if( ( rightCoord - leftCoord ) != 0.f )
		oneOverRightMinusLeft = 1.f / ( rightCoord - leftCoord );

	float oneOverTopMinusBottom = 0.f;
	if( ( topCoord - bottomCoord ) != 0.f )
		oneOverTopMinusBottom = 1.f / ( topCoord - bottomCoord );

	float oneOverFarMinusNear = 0.f;
	if( ( zFarDistance - zNearDistance ) != 0.f )
		oneOverFarMinusNear = 1.f / ( zFarDistance - zNearDistance );

	float translateX = -1.f * ( rightCoord + leftCoord ) * oneOverRightMinusLeft;
	float translateY = -1.f * ( topCoord + bottomCoord ) * oneOverTopMinusBottom;
	float translateZ = -1.f * ( zFarDistance + zNearDistance ) * oneOverFarMinusNear;

	this->m_entries[0] = 2.f * oneOverRightMinusLeft;
	this->m_entries[5] = 2.f * oneOverTopMinusBottom;
	this->m_entries[10] = -2.f * oneOverFarMinusNear;
	this->m_entries[12] = translateX;
	this->m_entries[13] = translateY;
	this->m_entries[14] = translateZ;
}


//-----------------------------------------------------------------------------------------------
inline void Matrix44::MakePerspective( float fovyDegrees, float aspectRatio, float zNearDistance, float zFarDistance )
{
	this->MakeIdentity();

	float fovyRadians = ConvertDegreesToRadians( fovyDegrees );
	float fValue = 0.f;
	float fValueDenom = tan( fovyRadians * 0.5f );
	if( fValueDenom != 0.f )
		fValue = 1.f / fValueDenom;

	float oneOverNearMinusFar = 0.f;
	if( ( zNearDistance - zFarDistance ) != 0.f )
		oneOverNearMinusFar = 1.f / ( zNearDistance - zFarDistance );

	this->m_entries[0] = fValue / aspectRatio;
	this->m_entries[5] = fValue;
	this->m_entries[10] = ( zNearDistance + zFarDistance ) * oneOverNearMinusFar;
	this->m_entries[11] = -1.f;
	this->m_entries[14] = ( 2.f * zNearDistance * zFarDistance ) * oneOverNearMinusFar;
}


#endif // include_Matrix44