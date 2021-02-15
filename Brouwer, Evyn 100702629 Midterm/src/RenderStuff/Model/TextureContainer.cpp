#include "TextureContainer.h"



mte::TextureContainer::TextureContainer(std::string textureName, std::string textureFile)
	:_textureName(textureName),_textureFile(textureFile)
{
	glGenTextures(1, &_texture);

	std::string filename = "Assets/Textures/default_map.jpg";
	if (_textureFile != "")
	{
		filename = _textureFile;
	}
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format = GL_RGB;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		glBindTexture(GL_TEXTURE_2D, _texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(data);
	}
	else
	{
		Error error;
		error._errorLocation = "Mesh.cpp";
		error._errorSeverity = mte::ErrorSeverityLevel::bad;
		error._errorTypes.push_back(mte::ErrorType::LoadFail);
		error._errorMessage = "Failed to load texture: " + filename;
		_logger.sendError(error);
		stbi_image_free(data);
	}
}
