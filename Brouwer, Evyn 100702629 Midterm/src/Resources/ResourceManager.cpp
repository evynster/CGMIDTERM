#include "ResourceManager.h"



std::vector<std::shared_ptr<mte::Shader>> mte::ResourceManager::_shaders;
std::vector<std::shared_ptr<mte::Mesh>> mte::ResourceManager::_meshes;
std::vector<std::shared_ptr<mte::TextureContainer>> mte::ResourceManager::_textures;
std::vector<std::shared_ptr<mte::FrameBuffer>> mte::ResourceManager::_buffers;

mte::ResourceManager::ResourceManager()
{
	_lightCubeShader = createShader("lightCubeShader", "Shaders/lightCubeShader.vs", "Shaders/lightCubeShader.fs");
}

std::shared_ptr<mte::Shader> mte::ResourceManager::createShader(std::string shaderName, std::string vsSource, std::string fsSource)
{
	for (auto x : _shaders) {
		if (x->_shaderName==shaderName) {
			return x;
		}
	}
	std::shared_ptr<mte::Shader> tempShader = std::make_shared<mte::Shader>(shaderName, vsSource, fsSource);
	tempShader->_lightCubeShader = _lightCubeShader;
	_shaders.push_back(tempShader);
	return tempShader;
}

std::shared_ptr<mte::Shader> mte::ResourceManager::getShader(std::string shaderName)
{
	for (auto x : _shaders) {
		if (x->_shaderName == shaderName) {
			return x;
		}
	}
	return NULL;
}

std::shared_ptr<mte::Mesh> mte::ResourceManager::createMesh(std::string meshFile, std::string meshName)
{
	for (auto x : _meshes) {
		if (x->_meshName == meshName) {
			return x;
		}
	}
	std::shared_ptr<mte::Mesh> tempMesh = std::make_shared<mte::Mesh>(meshFile, meshName);
	_meshes.push_back(tempMesh);
	return tempMesh;
}

std::shared_ptr<mte::TextureContainer> mte::ResourceManager::createTexture(std::string textureName, std::string textureFile)
{
	for (auto x : _textures) {
		if (x->_textureName == textureName && x->_textureFile == textureFile) {
			return x;
		}
	}
	std::shared_ptr<mte::TextureContainer> tempTexture = std::make_shared<mte::TextureContainer>(textureName, textureFile);
	_textures.push_back(tempTexture);
	return tempTexture;
}

std::shared_ptr<mte::FrameBuffer> mte::ResourceManager::createBuffer()
{
	std::shared_ptr<mte::FrameBuffer> tempBuffer;
	tempBuffer = std::make_shared<mte::FrameBuffer>();
	_buffers.push_back(tempBuffer);
	return tempBuffer;
}

std::shared_ptr<mte::TextureContainer> mte::ResourceManager::createTexture()
{
	for (auto x : _textures) {
		if (x->_textureName == "Default" && x->_textureFile == "Textures/default_map.jpg") {
			return x;
		}
	}
	std::shared_ptr<mte::TextureContainer> tempTexture = std::make_shared<mte::TextureContainer>("Default", "Textures/default_map.jpg");
	_textures.push_back(tempTexture);
	return tempTexture;
}

void mte::ResourceManager::drawLightCubes(std::shared_ptr<Camera> camera)
{
	for (auto x : _shaders) {
		if(x->_shaderName!="lightCubeShader")
			x->drawCubes(camera);
	}
}

void mte::ResourceManager::updateDrawCubes()
{
	for (auto x : _shaders) {
		x->updateCubes();
	}
}
