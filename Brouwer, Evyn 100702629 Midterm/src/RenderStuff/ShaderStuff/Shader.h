#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "RenderStuff/Lighting/LightCube.h"
#include "Logging/Logger.h"

#include "RenderStuff/Camera.h"

namespace mte {
	class Shader {
	public:
		Shader(std::string shaderName, std::string vs_source, std::string fs_source);
		~Shader();
		char* readFile(const char* filename);

		void compile(const char* vs_source, const char* fs_source);
		void Load(const char* vsFile,const char* fsFile);
		void Bind();

		void SetUniform(const char* name, const glm::mat4& value);
		void SetUniform(const char* name, const glm::mat3& value);
		void SetUniform(const char* name, const glm::vec3& value);
		void SetUniform(const char* name, const float& value);
		void SetUniform(const char* name, const int& value);


		std::string _shaderName;


		std::shared_ptr<Shader>_lightCubeShader;

		std::vector<std::shared_ptr<LightCube>> _lightCubes;

		void drawCubes(std::shared_ptr<Camera> camera);
		void updateCubes();
	private:
		GLuint __CompileShaderPart(const char* source, GLenum type);
		GLuint myShaderHandle = 0;

		Logger _logger;

		
		std::string _vs_source;
		std::string _fs_source;

		
		
	};
}
