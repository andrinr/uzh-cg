#version 330 core

// TODO: update this shader so that
//       - normals are shown as colors
//       - a normal matrix is declared and is applied so that..
//       - ...normals are given to the fragment shader


layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;

out vec3 fragColor;


// matrices that stay constant for the whole mesh.
uniform mat4 mvpMatrix;

void main(){	
	
	gl_Position =  mvpMatrix * vec4(vPosition, 1);
	fragColor = vColor;
}