#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 a_pos;
uniform mat4 a_ModelViewProjection;

void main ()
{
	gl_Position = a_ModelViewProjection * (vec4(a_pos,1) + vec4(aPos, 1.0));
}