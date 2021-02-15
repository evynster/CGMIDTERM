#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
out vec2 uv;

out mat4 a_view;
out mat4 a_mod;

uniform mat4 a_ViewProjection;
uniform mat4 a_Model;


void main ()
{

	a_view = a_ViewProjection;
	a_mod = a_Model;


	gl_Position = a_ViewProjection * a_Model * vec4(aPos, 1.0);

	
	Normal = mat3(transpose(inverse(a_Model))) * aNormal;

	FragPos = vec3(a_Model * vec4(aPos,1.0));

	uv = textureCoords;

	
}