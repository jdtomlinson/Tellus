#version 330
// Fragment Shader, GLSL v3.30


// CONSTANTS
const float MAX_SPEC_POWER = 32.0;
const float MAX_FLOAT_VALUE = pow( 10.0, 19.02725 );


// INPUTS
uniform vec3 u_lightPos;
in vec4 a_screenPosition;
in vec4 a_worldPosition;
in vec4 a_surfaceColor;
in vec4 a_surfaceNormal;
in vec4 a_surfaceTangent;
in vec4 a_surfaceBitangent;
in vec2 a_textureCoordinates;


// OUTPUTS
out vec4 a_fragColor;


//-----------------------------------------------------------------------------------------------
void main()
{
	vec3 pointToLight = normalize( u_lightPos - a_worldPosition.xyz );
	float diffuseCoefficient = clamp( dot( a_surfaceNormal.xyz, pointToLight ), 0.0, 1.0 );

	a_fragColor = vec4( 1.0, 1.0, 1.0, 1.0 );
	a_fragColor *= diffuseCoefficient;
	a_fragColor.w = 1.0;
}