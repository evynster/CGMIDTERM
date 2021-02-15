#pragma once
#include "Scene.h"
#include <iostream>
#include <memory>
#include <stb_image.h>

#include "RenderStuff/Model/Model.h"

#include "Resources/ResourceManager.h"

class TestScene : public mte::Scene
{
public:
	TestScene(GLFWwindow* window, std::string sceneName);

	void loadData();

	virtual void Resize(int Width, int Height)override;
private:

	virtual void virtualUpdate(float dt)override;

	mte::ResourceManager _resources;
	std::shared_ptr<Camera> _myTestCamera;


	std::shared_ptr<mte::Model> _testModel;

	std::shared_ptr<mte::Model> _testBread;

	float buttonTime = 0.0f;

	bool diffuse = true;
	bool ambient = true;
	bool specular = true;

	

};