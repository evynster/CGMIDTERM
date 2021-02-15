#pragma once
#include "RenderStuff/Model/TextureContainer.h"



namespace mte {
	class Mesh
	{
	public:
		Mesh(std::string meshFile, std::string meshName);

		Mesh(Mesh& copy);
		virtual ~Mesh();

		virtual void draw();

		std::string _meshName = "";

	private:
		Logger _logger;
		bool loadData();

		GLuint _VAO = 0;
		GLuint _VBO = 0;

		

		unsigned _vertexCount = 0, _indexCount = 0;

		bool _loaded = false;

		std::vector<float> _master;
		std::vector<float> _vertices;
		std::vector<float> _uvs;
		std::vector<float> _normals;


		std::string _meshFile = "";


		bool _active = true;
	};
}