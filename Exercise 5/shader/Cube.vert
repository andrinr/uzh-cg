#version 330 core

/* TODO update your vertex shader so that...
 *      ...it emits all necessary information to the fragment shader texturing
 *      
 */

// Input vertex data
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;
layout(location = 3) in vec2 vTexCoords;

// Output data will be interpolated for each fragment.
// Tip: Try to use the flat modifier to make color associations of a fragment visible for debugging. 
out vec3 objectColor;
out vec3 normal;
out vec3 worldPos;
out vec2 texCoord;

// matrices that stay constant for the whole mesh.
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;

void main(){
	/* TODO: set texture coordinates here */


	// End TODO
	
	normal = normalize(mat3(transpose(inverse(modelMatrix))) * vNormal);
	// Output position of the vertex, in clip space : MVP * vPosition
	gl_Position = mvpMatrix * vec4(vPosition, 1);
	objectColor = vColor;
	worldPos = vec3(modelMatrix * vec4(vPosition, 1));
}