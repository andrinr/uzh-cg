#version 330 core

/* TODO update your vertex shader so that...
 *      ...it has texture samplers declared
 *      ...it outputs a diffuse texture as diffuse color 
 *      ...it uses a light map to modify the specular highlights
 */    

in vec3 objectColor;
in vec3 normal;
in vec3 worldPos;
in vec2 texCoord;

/* TODO declare texture samplers here */


// END TODO

uniform vec3 camPos;

out vec3 color;

uniform struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
} light;

void main()
{
	/* TODO modify this piece of source code to make the texture lookup 
       working with the input texture instead of the object color */
    vec3 colorMap = objectColor;

	// END TODO

	// ambient term
	float ambientFactor = 0.25f;
	vec3 ambientColor = (light.ambient.xyz * ambientFactor);
	// diffuse term
	vec3 lightDir = vec3(normalize(light.position - worldPos));
	float diffDot = max(dot(normal, lightDir), 0.0);
	vec3 diffuseColor = diffDot * light.diffuse;

	// specular term (phong version)
	vec3 viewDir = vec3(normalize(camPos - worldPos));
	vec3 reflectDir = reflect(-lightDir, normal);
	float specDot = max(dot(viewDir, reflectDir), 0.0);
	float spec = pow(specDot, 16);
	float specStrength = 1.0;
	vec3 specularColor = specStrength * spec * light.specular;

	/* TODO modify this piece of source code if your are using a specular map. 
	 *      remember that you can also use the color output for debugging of the
	 *      texture maps and texture coordinates in case that you face troubles.
	 */
	color = (ambientColor + diffuseColor + specularColor) * colorMap.rgb, 1.0;
	
	// End TODO

}