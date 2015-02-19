#version 330
// Vertex Shader, GLSL v3.30


// INPUTS
uniform mat4 u_modelViewProjectionMatrix;
in vec4 a_vertex;
in vec4 a_color;
in vec4 a_normal;
in vec4 a_tangent;
in vec4 a_texCoord;


// OUTPUTS
out vec4 a_screenPosition;
out vec4 a_worldPosition;
out vec4 a_surfaceColor;
out vec4 a_surfaceNormal;
out vec4 a_surfaceTangent;
out vec3 a_surfaceBitangent;
out vec2 a_textureCoordinates;


//-----------------------------------------------------------------------------------------------
void main()
{
	gl_Position = u_modelViewProjectionMatrix * a_vertex;
	a_screenPosition = gl_Position;
	a_worldPosition = a_vertex;
	a_surfaceColor = a_color;
	a_surfaceNormal = a_normal;
	a_surfaceTangent = a_tangent;
	a_surfaceBitangent = cross(a_normal.xyz, a_tangent.xyz);
	a_textureCoordinates = a_texCoord.xy;
}