#pragma once

#include "RenderStuff/ShaderStuff/Shader.h"
#include "RenderStuff/Model/Mesh.h"
#include "RenderStuff/Model/Transform.h"
#include "RenderStuff/Camera.h"

namespace mte {
	class MeshContainer {
	public:
		MeshContainer(std::string meshTag, std::shared_ptr<Camera> camera, std::shared_ptr<mte::Shader> shader, std::shared_ptr<mte::Mesh> mesh,
			std::shared_ptr<mte::TextureContainer> diffuse, std::shared_ptr<mte::TextureContainer> specular, std::shared_ptr<mte::TextureContainer> emission);

		void draw();
		void update(float dt);

		std::string _meshTag;


		bool _active = true;

		std::shared_ptr<mte::Mesh> _mesh;
		std::shared_ptr<mte::TextureContainer> _diffuse;
		std::shared_ptr<mte::TextureContainer> _specular;
		std::shared_ptr<mte::TextureContainer> _emission;

		std::shared_ptr <mte::Shader> _shader;

		std::shared_ptr<Transform> _transform;

		std::shared_ptr<Camera> _camera;
		static bool ambient;
		static bool diffuse;
		static bool specular;
		static bool bloom;
		static bool texture;

	};



}