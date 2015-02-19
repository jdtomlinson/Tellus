#version 330
// Fragment Shader, GLSL v3.30


// INPUTS
uniform float u_lightAngle;
uniform sampler2D u_heightmapTexture;
uniform sampler2D u_diffuseTexture;
in vec4 a_screenPosition;
in vec4 a_worldPosition;
in vec4 a_surfaceColor;
in vec4 a_surfaceNormal;
in vec2 a_textureCoordinates;


// OUTPUTS
out vec4 a_fragColor;


//-----------------------------------------------------------------------------------------------
void main()
{
	float size = 100.0;
	vec4 diffuseTexel = texture2D( u_diffuseTexture, a_textureCoordinates );

	vec3 lightDir = normalize( vec3( 0.0, sin(u_lightAngle), cos(u_lightAngle) ) );
	float NdotL = clamp( dot( a_surfaceNormal.xyz, lightDir ), 0.0, 1.0 );
	
	a_fragColor = a_surfaceColor * diffuseTexel * NdotL;
	a_fragColor.w = 1.0;
}