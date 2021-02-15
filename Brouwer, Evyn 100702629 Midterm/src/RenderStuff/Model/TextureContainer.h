#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Logging/Logger.h"

#include <vector>
#include <string>
#include <stb_image.h>


namespace mte {
	class TextureContainer {
	public:
		TextureContainer(std::string textureName,std::string textureFile);
		std::string _textureName;
		std::string _textureFile;

		GLuint _texture;

	private:
		Logger _logger;
	};

}
