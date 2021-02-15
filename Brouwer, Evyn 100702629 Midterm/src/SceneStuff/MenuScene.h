#pragma once

#include "Scene.h"

#include "Resources/ResourceManager.h"


#include "RenderStuff/Model/Model.h"

#include <glm/gtc/quaternion.hpp>

#include <memory>

#include <stb_image.h>

#include <Logging/Logger.h>

class MenuScene : public mte::Scene
{
public:
	MenuScene(GLFWwindow* window, std::string sceneName);
	
	void loadData();

	virtual void Resize(int Width,int Height)override;
private:

	virtual void virtualUpdate(float dt)override;

	std::shared_ptr<Camera> _myTestCamera = NULL;
	std::shared_ptr<mte::Shader> meshShader;
	

	mte::Logger _logger;

	mte::ResourceManager _resources;

	std::shared_ptr<mte::FrameBuffer> _testBuffer;


	float buttonTime = 0.0f;
	bool diffuse = true;
	bool ambient = true;
	bool specular = true;
	bool bloom = true;
	bool texture = true;

	std::shared_ptr<mte::Model> _testBread;

	std::shared_ptr<mte::Model> _testComp;

	std::shared_ptr<mte::Model> _testPrint;

	std::shared_ptr<mte::Model> _testTable;
};