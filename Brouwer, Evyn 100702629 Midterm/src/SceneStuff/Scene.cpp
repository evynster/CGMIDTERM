#include "Scene.h"


mte::Scene::Scene(GLFWwindow* window, std::string sceneName)
	:_gameWindow(window),_sceneName(sceneName)
{
}

void mte::Scene::update(float dt)
{
	
	virtualUpdate(dt);
}
