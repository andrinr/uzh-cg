#version 330 core

// Interpolated values from the vertex shaders
// Tip: use the flat modifier to make color associations of a fragment visible for debugging. 
in vec3 fragColor;

// Ouput data
out vec3 color;

void main()
{
	// Output color = color specified in the vertex shader,
	// interpolated between all 3 surrounding vertices
	color = fragColor;
}