#version 330
// Fragment Shader, GLSL v3.30


// INPUTS
uniform sampler2D u_diffuseTexture;
in vec4 a_screenPosition;
in vec4 a_worldPosition;
in vec4 a_surfaceColor;
in vec2 a_textureCoordinates;


// OUTPUTS
out vec4 a_fragColor;


//-----------------------------------------------------------------------------------------------
void main()
{
	a_fragColor = a_surfaceColor;
}