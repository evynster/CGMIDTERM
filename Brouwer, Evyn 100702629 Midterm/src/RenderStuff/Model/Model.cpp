#include "Model.h"

void mte::Model::addMesh(std::shared_ptr<MeshContainer> mesh)
{
	mesh->_transform->_parent = _transform;
	 _meshes.push_back(mesh); 
}

void mte::Model::draw()
{
	if(_active)
		for (unsigned i = 0; i < _meshes.size(); i++) {
			_meshes[i]->draw();
		}
}

void mte::Model::update(float dt)
{
	_transform->update();
	if (_active)
		for (unsigned i = 0; i < _meshes.size(); i++) {
			_meshes[i]->update(dt);
		}
}

std::shared_ptr<mte::MeshContainer> mte::Model::getMesh(std::string meshTag)
{
	for (auto x : _meshes) {
		if (x->_meshTag == meshTag)
			return x;
	}
	return NULL;
}
