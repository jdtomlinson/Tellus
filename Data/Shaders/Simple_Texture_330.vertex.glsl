#version 330
// Vertex Shader, GLSL v3.30


// INPUTS
uniform bool u_useTexture;
uniform float u_time;
uniform mat4 u_modelViewProjectionMatrix;
in vec4 a_vertex;
in vec4 a_color;
in vec4 a_normal;
in vec4 a_texCoord;


// OUTPUTS
out vec4 a_screenPosition;
out vec4 a_worldPosition;
out vec4 a_surfaceColor;
out vec4 a_surfaceNormal;
out vec2 a_textureCoordinates;


//-----------------------------------------------------------------------------------------------
void main()
{
	gl_Position = u_modelViewProjectionMatrix * a_vertex;
	a_screenPosition = gl_Position;
	a_worldPosition = a_vertex;
	a_surfaceColor = a_color;
	a_surfaceNormal = a_normal;
	a_textureCoordinates = a_texCoord.xy;
}