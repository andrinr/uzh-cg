#version 330 core

/* TODO update your vertex shader so that...
 *      ...it emits the color for phong illumination
 *      ...it emits the color from the vertex shader in case you do gourand shading there
 */

in vec3 objectColor;
in vec3 normal;

// Ouput data
out vec3 color;

/* TODO fill these structs with values from outside the shader similar
 *      to your matric variables
 */
in vec3 lightPosition;

uniform vec3 lightColor;
uniform float ambientIntensity;
uniform vec3 ambientColor;
uniform float reflectiveness;
uniform float shininess;
uniform float diffuse;

void main()
{
	// Output color = color specified in the vertex shader,
	// interpolated between all 3 surrounding vertices
	color = objectColor;
	//color = normal;

	/* TODO add there code for phong lighting
	*
	*/
	// ambient only
	color = ambientIntensity * ambientColor * objectColor;









	// End TODO
}