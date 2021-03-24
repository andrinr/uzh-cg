#version 330 core


// TODO: update this shader so that
//       - draw incoming normals from the vertex shader


in vec3 fragColor;

out vec3 color;


void main()
{
	// ... uncomment this for color
	color = fragColor;
	// ... uncomment this for color according to normals
	//color = ...;
}