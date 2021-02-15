#version 330 core
out vec4 FragColor;

uniform vec3 a_colour;

void main()
{
	FragColor = vec4(a_colour,1);
}