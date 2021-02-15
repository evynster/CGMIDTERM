#pragma once
#include "RenderStuff/Model/MeshContainer.h"


namespace mte {
	class Model {
	public:
		Model() { _transform = std::make_shared<Transform>(); };

		void addMesh(std::shared_ptr<MeshContainer> mesh);

		void draw();
		void update(float dt);
		
		std::shared_ptr<mte::MeshContainer> getMesh(std::string meshTag);  

		std::shared_ptr<Transform> getTransform() { return _transform; }

	private:

		
		std::vector<std::shared_ptr<MeshContainer>> _meshes;

		bool _active = true;

		std::shared_ptr<Transform> _transform;
	};
}