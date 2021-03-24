#version 330 core

// Input vertex data
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;

// Output data will be interpolated for each fragment.
// Tip: Try to use the flat modifier to make color associations of a fragment visible for debugging. 
out vec3 fragColor;

// matrices that stay constant for the whole mesh.
uniform mat4 mvpMatrix;

void main(){
	// Output position of the vertex, in clip space : MVP * vPosition
	gl_Position =  mvpMatrix * vec4(vPosition, 1);
	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	// ... uncomment this for color
	fragColor = vColor;
	// ... uncomment this for color according to normals
	// fragColor = vNormal;
}