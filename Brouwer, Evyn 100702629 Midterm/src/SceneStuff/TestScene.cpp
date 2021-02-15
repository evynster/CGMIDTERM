#include "TestScene.h"
#include <math.h>

TestScene::TestScene(GLFWwindow* window, std::string sceneName)
	:Scene(window,sceneName)
{
	loadData();
}

void TestScene::loadData()
{
	_myTestCamera = std::make_shared<Camera>();
	_myTestCamera->SetPosition(glm::vec3(5, 0, 5));
	_myTestCamera->Projection = glm::perspective(glm::radians(60.0f), 1600.0f / 900.0f, 0.01f, 1000.0f);


	_testModel = std::make_shared<mte::Model>();
	_testModel->addMesh(std::make_shared<mte::MeshContainer>("box0",_myTestCamera, _resources.createShader("testMeshShader", "Shaders/testShader.vs", "Shaders/testShader.fs"), _resources.createMesh("Meshes/test.obj", "Test Mesh"), _resources.createTexture( "Test Texture", "Textures/meme.jpg"), _resources.createTexture(), _resources.createTexture()));
	_testModel->addMesh(std::make_shared<mte::MeshContainer>("box1",_myTestCamera, _resources.createShader("meshShader", "Shaders/meshShader.vs", "Shaders/meshShader.fs"),_resources.createMesh("Meshes/box.obj", "Box Mesh"), _resources.createTexture("Box Texture", "Textures/boxdiffuse.jpg"), _resources.createTexture(), _resources.createTexture()));

	_testBread = std::make_shared<mte::Model>();
	_testBread->addMesh(std::make_shared<mte::MeshContainer>("bread", _myTestCamera, _resources.createShader("meshShader", "Shaders/meshShader.vs", "Shaders/meshShader.fs"), _resources.createMesh("Meshes/Bread.obj","Bread Mesh"),_resources.createTexture("Bread Texture","Textures/Bread_diffuse.png"), _resources.createTexture("Bread Specular","Textures/Bread_Specular.png"), _resources.createTexture()));
	_testBread->getTransform()->translate(glm::vec4(4.0,0.0,0.0,0.0));

	std::shared_ptr<mte::LightCube> tempLight = std::make_shared<mte::LightCube>(glm::vec3(5, 1, 6), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 1.0f, 0.09f, 0.032f);
	_resources.getShader("meshShader")->_lightCubes.push_back(tempLight);

}

void TestScene::Resize(int Width, int Height)
{
	_myTestCamera->Projection = glm::perspective(glm::radians(60.0f), (float)Width / (float)Height, 0.01f, 1000.0f);
}

void TestScene::virtualUpdate(float dt)
{

	glm::vec3 movement = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	float speed = 1.0f;
	float rotSpeed = 1.0f;
	if (_input.getKeyState(GLFW_KEY_W))
		movement.z -= speed * dt;
	if (_input.getKeyState(GLFW_KEY_S))
		movement.z += speed * dt;
	if (_input.getKeyState(GLFW_KEY_A))
		movement.x -= speed * dt;
	if (_input.getKeyState(GLFW_KEY_D))
		movement.x += speed * dt;
	if (_input.getKeyState(GLFW_KEY_SPACE))
		movement.y += speed * dt;
	if (_input.getKeyState(GLFW_KEY_LEFT_CONTROL))
		movement.y -= speed * dt;

	if (_input.getKeyState(GLFW_KEY_Q))
		rotation.z -= rotSpeed * dt;
	if (_input.getKeyState(GLFW_KEY_E))
		rotation.z += rotSpeed * dt;
	if (_input.getKeyState(GLFW_KEY_UP))
		rotation.x -= rotSpeed * dt;
	if (_input.getKeyState(GLFW_KEY_DOWN))
		rotation.x += rotSpeed * dt;
	if (_input.getKeyState(GLFW_KEY_LEFT))
		rotation.y -= rotSpeed * dt;
	if (_input.getKeyState(GLFW_KEY_RIGHT))
		rotation.y += rotSpeed * dt;




	if (_input.getKeyState(GLFW_KEY_1)&&!buttonTime) {
		
		buttonTime = 0.3f;
		diffuse = false;
		ambient = false;
		specular = false;
	}
	if (_input.getKeyState(GLFW_KEY_2)&&!buttonTime) {
		buttonTime = 0.3f;
		diffuse = false;
		ambient = true;
		specular = false;
	}
	if (_input.getKeyState(GLFW_KEY_3)&&!buttonTime) {
		buttonTime = 0.3f;
		diffuse = false;
		ambient = false;
		specular = true;
	}
	if (_input.getKeyState(GLFW_KEY_4) && !buttonTime) {
		buttonTime = 0.3f;
		diffuse = false;
		ambient = true;
		specular = true;
	}
	if (_input.getKeyState(GLFW_KEY_5) && !buttonTime) {
		buttonTime = 0.3f;
		diffuse = false;
		ambient = true;
		specular = true;
	}
	if (buttonTime) {
		buttonTime -= dt;
		if (buttonTime < 0.0f)
			buttonTime = 0.0f;
	}
		
	mte::MeshContainer::ambient = ambient;
	mte::MeshContainer::diffuse = diffuse;
	mte::MeshContainer::specular = specular;
	





	std::shared_ptr<mte::MeshContainer> tempModel1 = _testModel->getMesh("box1");
	std::shared_ptr<mte::MeshContainer> tempModel2 = _testModel->getMesh("box0");
	if (tempModel2 != NULL) {
		tempModel2->_transform->translate(glm::vec3(0, 0.3 * dt, 0));
	}
	{
		_testBread->getTransform()->translate(glm::vec4(0.0, 0.3*dt, 0.0, 0.0));

	}





	if (tempModel1 != NULL) {
		std::shared_ptr<mte::LightCube> tempLight = tempModel1->_shader->_lightCubes[0];
		tempLight->_pos.y = sin(glfwGetTime()) * 10;
	}
	
	





	//move to list of objects
	_testModel->update(dt);
	_testModel->draw();

	_testBread->update(dt);
	_testBread->draw();





	_myTestCamera->Rotate(rotation);
	_myTestCamera->Move(movement);


	_resources.drawLightCubes(_myTestCamera);
	_resources.updateDrawCubes();

}
