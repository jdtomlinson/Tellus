#version 330
// Vertex Shader, GLSL v3.30


// INPUTS
uniform float u_xScale;
uniform float u_yScale;
uniform float u_zScale;
uniform mat4 u_modelViewProjectionMatrix;
in vec4 a_vertex;
in vec4 a_color;
in vec4 a_normal;
in vec4 a_texCoord;
in float a_height;


// OUTPUTS
out vec4 a_screenPosition;
out vec4 a_worldPosition;
out vec4 a_surfaceColor;
out vec4 a_surfaceNormal;
out vec2 a_textureCoordinates;


//-----------------------------------------------------------------------------------------------
float SmoothStep( float val )
{
	return ( 3.0 * ( val * val ) ) - ( 2.0 * ( val * val * val ) );
}


//-----------------------------------------------------------------------------------------------
float GetRandomNoiseValue( float x, float y )
{
	int n = int( x + ( y * 57 ) );
	n = ( n<<13 )^n;
	return ( 1.0 - ( ( n * ( n * n * 15731 + 789221 ) + 1376312589 ) & 0x7fffffff ) / 1073741824.0 );
}


//-----------------------------------------------------------------------------------------------
float PerlinNoise( vec2 position, vec2 perlinDimension )
{
	float oneOverPerlinSampleSizeX = 1.0 / perlinDimension.x;
	float oneOverPerlinSampleSizeY = 1.0 / perlinDimension.y;

	float southCoord = floor( position.x * oneOverPerlinSampleSizeX );
	float northCoord = southCoord + 1.0;
	float eastCoord = floor( position.y * oneOverPerlinSampleSizeY );
	float westCoord = eastCoord + 1.0;
	float percentAcrossX = ( position.x * oneOverPerlinSampleSizeX ) - southCoord;
	float percentAcrossY = ( position.y * oneOverPerlinSampleSizeY ) - eastCoord;
	percentAcrossX = SmoothStep( percentAcrossX );
	percentAcrossY = SmoothStep( percentAcrossY );

	vec2 posSE = vec2( southCoord, eastCoord );
	vec2 posSW = vec2( southCoord, westCoord );
	vec2 posNE = vec2( northCoord, eastCoord );
	vec2 posNW = vec2( northCoord, westCoord );

	float theta0 = GetRandomNoiseValue( posSE.x, posSE.y );
	float theta1 = GetRandomNoiseValue( posSW.x, posSW.y );
	float theta2 = GetRandomNoiseValue( posNE.x, posNE.y );
	float theta3 = GetRandomNoiseValue( posNW.x, posNW.y );

	vec2 vecSE = vec2( ( 1.0 - percentAcrossX ), ( 1.0 - percentAcrossY ) );
	vec2 vecSW = vec2( ( 1.0 - percentAcrossX ), percentAcrossY );
	vec2 vecNE = vec2( percentAcrossX, ( 1.0 - percentAcrossY ) );
	vec2 vecNW = vec2( percentAcrossX, percentAcrossY );

	normalize( vecSE );
	normalize( vecSW );
	normalize( vecNE );
	normalize( vecNW );

	float se = dot( vec2( cos( theta0 ), sin( theta0 ) ), vecSE );
	float sw = dot( vec2( cos( theta1 ), sin( theta1 ) ), vecSW );
	float ne = dot( vec2( cos( theta2 ), sin( theta2 ) ), vecNE );
	float nw = dot( vec2( cos( theta3 ), sin( theta3 ) ), vecNW );

	float south = ( se * ( 1.0 - percentAcrossY ) ) + ( sw * percentAcrossY );
	float north = ( ne * ( 1.0 - percentAcrossY ) ) + ( nw * percentAcrossY );

	return ( south * ( 1.0 - percentAcrossX ) ) + ( north * percentAcrossX );
}


//-----------------------------------------------------------------------------------------------
void main()
{
	vec4 adjustedVert = a_vertex;
	adjustedVert.x *= u_xScale;
	adjustedVert.y *= u_yScale;
	adjustedVert.z = u_zScale * ( pow( 2.0, a_height ) - 1 );

	gl_Position = u_modelViewProjectionMatrix * adjustedVert;
	a_screenPosition = gl_Position;
	a_worldPosition = adjustedVert;
	a_surfaceColor = a_color;
	a_surfaceNormal = a_normal;
	a_textureCoordinates = a_texCoord.xy;
}