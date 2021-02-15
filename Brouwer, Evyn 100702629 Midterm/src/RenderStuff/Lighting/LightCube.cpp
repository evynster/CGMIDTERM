#include "LightCube.h"

mte::LightCube::LightCube(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
	:_pos(pos), _ambient(ambient), _diffuse(diffuse), _specular(specular),_constant(constant),_linear(linear),_quadratic(quadratic)
{
	_lightType = mte::lightType::pointLight;
	bindData();
}

mte::LightCube::LightCube(glm::vec3 dir, glm::vec3 ambient,glm::vec3 diffuse, glm::vec3 specular)
	:_dir(dir), _ambient(ambient),_diffuse(diffuse),_specular(specular)
{
	_lightType = mte::lightType::directionLight;
	bindData();
}

mte::LightCube::LightCube(glm::vec3 pos, glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	: _pos(pos), _ambient(ambient),_dir(dir), _diffuse(diffuse), _specular(specular)
{
	_lightType = mte::lightType::spotLight;
	bindData();
}

void mte::LightCube::drawCube()
{
	if (_active) {

		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES, 0, _master.size()/3);
	}
}

void mte::LightCube::bindData()
{
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);

	glBindVertexArray(_VAO);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	glm::vec3 cubeData[8] = {
			glm::vec3(-0.2,  0.2,  0.2),//0
			glm::vec3(0.2,  0.2,  0.2),//1
			glm::vec3(-0.2,  0.2, -0.2),//2
			glm::vec3(0.2,  0.2, -0.2),//3
			glm::vec3(-0.2, -0.2, -0.2),//4
			glm::vec3(0.2, -0.2, -0.2),//5
			glm::vec3(-0.2, -0.2,  0.2),//6
			glm::vec3(0.2, -0.2,  0.2) //7
	};

	{
		_master.push_back(cubeData[1].x);
		_master.push_back(cubeData[1].y);
		_master.push_back(cubeData[1].z);

		_master.push_back(cubeData[5].x);
		_master.push_back(cubeData[5].y);
		_master.push_back(cubeData[5].z);

		_master.push_back(cubeData[7].x);
		_master.push_back(cubeData[7].y);
		_master.push_back(cubeData[7].z);
	}

	{
		_master.push_back(cubeData[3].x);
		_master.push_back(cubeData[3].y);
		_master.push_back(cubeData[3].z);

		_master.push_back(cubeData[5].x);
		_master.push_back(cubeData[5].y);
		_master.push_back(cubeData[5].z);

		_master.push_back(cubeData[1].x);
		_master.push_back(cubeData[1].y);
		_master.push_back(cubeData[1].z);
	}

	{
		_master.push_back(cubeData[0].x);
		_master.push_back(cubeData[0].y);
		_master.push_back(cubeData[0].z);

		_master.push_back(cubeData[3].x);
		_master.push_back(cubeData[3].y);
		_master.push_back(cubeData[3].z);

		_master.push_back(cubeData[1].x);
		_master.push_back(cubeData[1].y);
		_master.push_back(cubeData[1].z);
	}

	{
		_master.push_back(cubeData[1].x);
		_master.push_back(cubeData[1].y);
		_master.push_back(cubeData[1].z);

		_master.push_back(cubeData[5].x);
		_master.push_back(cubeData[5].y);
		_master.push_back(cubeData[5].z);

		_master.push_back(cubeData[7].x);
		_master.push_back(cubeData[7].y);
		_master.push_back(cubeData[7].z);
	}

	{
		_master.push_back(cubeData[0].x);
		_master.push_back(cubeData[0].y);
		_master.push_back(cubeData[0].z);

		_master.push_back(cubeData[2].x);
		_master.push_back(cubeData[2].y);
		_master.push_back(cubeData[2].z);

		_master.push_back(cubeData[3].x);
		_master.push_back(cubeData[3].y);
		_master.push_back(cubeData[3].z);
	}

	{
		_master.push_back(cubeData[2].x);
		_master.push_back(cubeData[2].y);
		_master.push_back(cubeData[2].z);

		_master.push_back(cubeData[4].x);
		_master.push_back(cubeData[4].y);
		_master.push_back(cubeData[4].z);

		_master.push_back(cubeData[3].x);
		_master.push_back(cubeData[3].y);
		_master.push_back(cubeData[3].z);
	}

	{
		_master.push_back(cubeData[4].x);
		_master.push_back(cubeData[4].y);
		_master.push_back(cubeData[4].z);

		_master.push_back(cubeData[5].x);
		_master.push_back(cubeData[5].y);
		_master.push_back(cubeData[5].z);

		_master.push_back(cubeData[3].x);
		_master.push_back(cubeData[3].y);
		_master.push_back(cubeData[3].z);
	}

	{
		_master.push_back(cubeData[1].x);
		_master.push_back(cubeData[1].y);
		_master.push_back(cubeData[1].z);

		_master.push_back(cubeData[7].x);
		_master.push_back(cubeData[7].y);
		_master.push_back(cubeData[7].z);

		_master.push_back(cubeData[6].x);
		_master.push_back(cubeData[6].y);
		_master.push_back(cubeData[6].z);
	}

	{
		_master.push_back(cubeData[0].x);
		_master.push_back(cubeData[0].y);
		_master.push_back(cubeData[0].z);

		_master.push_back(cubeData[1].x);
		_master.push_back(cubeData[1].y);
		_master.push_back(cubeData[1].z);

		_master.push_back(cubeData[6].x);
		_master.push_back(cubeData[6].y);
		_master.push_back(cubeData[6].z);
	}

	{
		_master.push_back(cubeData[0].x);
		_master.push_back(cubeData[0].y);
		_master.push_back(cubeData[0].z);

		_master.push_back(cubeData[6].x);
		_master.push_back(cubeData[6].y);
		_master.push_back(cubeData[6].z);

		_master.push_back(cubeData[2].x);
		_master.push_back(cubeData[2].y);
		_master.push_back(cubeData[2].z);
	}

	{
		_master.push_back(cubeData[2].x);
		_master.push_back(cubeData[2].y);
		_master.push_back(cubeData[2].z);

		_master.push_back(cubeData[6].x);
		_master.push_back(cubeData[6].y);
		_master.push_back(cubeData[6].z);

		_master.push_back(cubeData[4].x);
		_master.push_back(cubeData[4].y);
		_master.push_back(cubeData[4].z);
	}

	{
		_master.push_back(cubeData[5].x);
		_master.push_back(cubeData[5].y);
		_master.push_back(cubeData[5].z);

		_master.push_back(cubeData[4].x);
		_master.push_back(cubeData[4].y);
		_master.push_back(cubeData[4].z);

		_master.push_back(cubeData[7].x);
		_master.push_back(cubeData[7].y);
		_master.push_back(cubeData[7].z);
	}

	{
		_master.push_back(cubeData[4].x);
		_master.push_back(cubeData[4].y);
		_master.push_back(cubeData[4].z);

		_master.push_back(cubeData[6].x);
		_master.push_back(cubeData[6].y);
		_master.push_back(cubeData[6].z);

		_master.push_back(cubeData[7].x);
		_master.push_back(cubeData[7].y);
		_master.push_back(cubeData[7].z);
	}

	glBufferData(GL_ARRAY_BUFFER, _master.size() * sizeof(float), &_master[0], GL_STATIC_DRAW);

	//vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

