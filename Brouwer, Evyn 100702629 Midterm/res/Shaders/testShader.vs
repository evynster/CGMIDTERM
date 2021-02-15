#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec3 normals;

out vec3 normal;
out vec2 uv;

uniform mat4 a_ModelViewProjection;

void main ()
{
	uv = uvs;
	normal = normals;

	gl_Position = a_ModelViewProjection * vec4(aPos, 1.0);

}