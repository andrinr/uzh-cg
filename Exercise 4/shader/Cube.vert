#version 330 core

/* TODO update your vertex shader so that...
 *      ...it emits all necessary information to the fragment shader for phong illumination
 *      ...it emits the color in case you do gourand shading
 */

// Input vertex data
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;

// Output data will be interpolated for each fragment.
// Tip: Try to use the flat modifier to make color associations of a fragment visible for debugging. 
out vec3 objectColor;
out vec3 normal;
out vec3 lightPosition;

// matrices that stay constant for the whole mesh.
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;

/* TODO additional variables
 *
 */
uniform vec3 uLightPosition;

void main(){
	normal = mat3(transpose(inverse(modelMatrix))) * vNormal;
	// Output position of the vertex, in clip space : MVP * vPosition
	gl_Position = mvpMatrix * vec4(vPosition, 1);
	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	// ... uncomment this for color
	objectColor = vColor;
	// ... uncomment this for color according to normals
	//objectColor = vNormal;

	/* TODO add there code for gourand shading
	*
	*/
	lightPosition = (mvpMatrix * vec4(uLightPosition, 1)).xyz;





 	// End TODO
}