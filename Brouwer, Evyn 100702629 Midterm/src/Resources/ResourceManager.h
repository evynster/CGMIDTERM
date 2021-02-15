#pragma once

#include "RenderStuff/ShaderStuff/Shader.h"
#include "RenderStuff/Model/Mesh.h"
#include "RenderStuff/FrameBuffer.h"

namespace mte {
	class ResourceManager {
	public:
		ResourceManager();
		std::shared_ptr<mte::Shader> createShader(std::string shaderName, std::string vsSource,std::string fsSource);
		static std::vector<std::shared_ptr<mte::Shader>> _shaders;
		std::shared_ptr<mte::Shader> getShader(std::string shaderName);


		std::shared_ptr<mte::Mesh> createMesh(std::string meshFile, std::string meshName);
		static std::vector<std::shared_ptr<mte::Mesh>> _meshes;

		std::shared_ptr<mte::TextureContainer> createTexture();
		std::shared_ptr<mte::TextureContainer> createTexture(std::string textureName, std::string textureFile);
		static std::vector<std::shared_ptr<mte::TextureContainer>> _textures;

		std::shared_ptr<mte::FrameBuffer> createBuffer();
		static std::vector < std::shared_ptr<mte::FrameBuffer> > _buffers;

		//light cube stuff
		void drawLightCubes(std::shared_ptr<Camera> camera);
		void updateDrawCubes();

	private:

		std::shared_ptr<mte::Shader> _lightCubeShader;
	};
}
