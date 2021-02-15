#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <cstdint> // Needed for uint32_t
#include <memory> // Needed for smart pointers

class Vertex
{
public:
	Vertex();
	Vertex(glm::vec3 pos, glm::vec4 col);
	glm::vec3 _position;
	glm::vec4 _colour;


private:


};