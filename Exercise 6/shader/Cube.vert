#version 330 core

/* TODO update your vertex shader so that...
 *      ...it can receive the tangent as vertex input
 *      ...it calculates a tbn matrix
 *      ...it emits a tbn matrix to the fragment shader
 */

// Input vertex data
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;
layout(location = 3) in vec2 vTexCoords;

out vec3 objectColor;
out vec3 vertexNormal;
out vec3 worldPos;
out vec2 texCoord;

// matrices that stay constant for the whole mesh.
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;

void main(){
	// Output position of the vertex, in clip space : MVP * vPosition
	texCoord = vTexCoords;
	gl_Position = mvpMatrix * vec4(vPosition, 1);
	objectColor = vColor;
	worldPos = vec3(modelMatrix * vec4(vPosition, 1));

	/* TODO: calculate the tbn matrix and update the normal here */
	vertexNormal = normalize(mat3(transpose(inverse(modelMatrix))) * vNormal);








  	// End TODO
}