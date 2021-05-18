#version 330 core

uniform vec3 objectColor;

in vec3 fragColor;
out vec3 color;

void main()
{
	color = objectColor;
}