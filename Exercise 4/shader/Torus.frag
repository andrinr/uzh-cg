#version 330 core

/* TODO update your vertex shader so that...
 *      ...it emits the color for phong illumination
 *      ...it emits the color from the vertex shader in case you do gourand shading there
 */

in vec3 objectColor;
in vec3 normal;
in vec3 fragPos;

// Ouput data
out vec3 color;

/* TODO fill these structs with values from outside the shader similar
 *      to your matric variables
 */
uniform vec3 lightPosition;
uniform vec3 viewerPosition;

uniform vec3 lightColor;
uniform vec3 ambientTerm;
uniform vec3 diffuseTerm;
uniform vec3 specularTerm;


void main()
{
	// Output color = color specified in the vertex shader,
	// interpolated between all 3 surrounding vertices
	//color = objectColor;
	//color = normal;

	/* TODO add there code for phong lighting
	*
	*/
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPosition - fragPos);
	vec3 viewDir = normalize(viewerPosition - fragPos);
	vec3 reflectionDir = dot(norm,lightDir) * 2 * norm - lightDir;

	vec3 ambient = ambientTerm * objectColor;
	vec3 diffuse = diffuseTerm * objectColor * dot(norm, lightDir);
	// Use max term to avoid backside specular
	vec3 specular = specularTerm * pow(max(dot(viewDir, reflectionDir),0.0), 5);
	color = ( ambient + diffuse + specular ) * objectColor;

	//color = objectColor;
	// End TODO
}