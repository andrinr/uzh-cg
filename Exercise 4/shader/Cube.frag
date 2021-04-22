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


void main()
{
	// Output color = color specified in the vertex shader,
	// interpolated between all 3 surrounding vertices
	color = objectColor;
	//color = normal;

	/* TODO add there code for phong lighting
	*
	*/
	










	// End TODO
}