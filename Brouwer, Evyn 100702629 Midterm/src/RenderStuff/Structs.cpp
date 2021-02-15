#include "Structs.h"

Vertex::Vertex()
{
	_position = glm::vec3(0.0f);
	_colour = glm::vec4(1.0f);
}

Vertex::Vertex(glm::vec3 pos, glm::vec4 col)
	: _position(pos),_colour(col)
{
}
