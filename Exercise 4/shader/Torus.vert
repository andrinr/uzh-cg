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
out vec3 fragPos;

// matrices that stay constant for the whole mesh.
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;

uniform vec3 lightPosition;
uniform vec3 viewerPosition;

uniform vec3 lightColor;
uniform vec3 ambientTerm;
uniform vec3 diffuseTerm;
uniform vec3 specularTerm;
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
	
	fragPos = vec3(modelMatrix*vec4(vPosition, 1));

	/*vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPosition - fragPos);
	vec3 viewDir = normalize(viewerPosition - fragPos);
	vec3 reflectionDir = dot(norm,lightDir) * 2 * norm - lightDir;

	vec3 ambient = ambientTerm * objectColor;
	vec3 diffuse = diffuseTerm * objectColor * dot(norm, lightDir);
	// Use max term to avoid backside specular
	vec3 specular = specularTerm * pow(max(dot(viewDir, reflectionDir),0.0), 5);
	objectColor = ( ambient + diffuse + specular) * objectColor;*/




 	// End TODO
}