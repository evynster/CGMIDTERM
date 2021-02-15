#include "MenuScene.h"
#include <GLM/gtc/matrix_transform.hpp>

MenuScene::MenuScene(GLFWwindow* window, std::string sceneName)
	:Scene(window,sceneName)
{
	loadData();
}

void MenuScene::loadData()
{
	_myTestCamera = std::make_shared<Camera>();
	_myTestCamera->SetPosition(glm::vec3(5, 5, 5));
	_myTestCamera->Projection = glm::perspective(glm::radians(60.0f), 1600.0f/900.0f, 0.01f, 1000.0f);
		
	meshShader = _resources.createShader("meshShader", "Shaders/meshShader.vs", "Shaders/meshShader.fs");


	_testBread = std::make_shared<mte::Model>();
	_testBread->addMesh(std::make_shared<mte::MeshContainer>("bread", _myTestCamera, _resources.createShader("meshShader", "Shaders/meshShader.vs", "Shaders/meshShader.fs"), _resources.createMesh("Meshes/Bread.obj", "Bread Mesh"), _resources.createTexture("Bread Texture", "Textures/Bread_diffuse.png"), _resources.createTexture("Bread Specular", "Textures/Bread_Specular.png"), _resources.createTexture()));
	_testBread->getTransform()->translate(glm::vec4(-3.8, 5.2, 0.0, 0.0));


	_testComp = std::make_shared<mte::Model>();
	_testComp->addMesh(std::make_shared<mte::MeshContainer>("comp", _myTestCamera, _resources.createShader("meshShader", "Shaders/meshShader.vs", "Shaders/meshShader.fs"), _resources.createMesh("Meshes/comp1.obj", "Comp Mesh"), _resources.createTexture("Comp Texture", "Textures/comp_diffuse.png"), _resources.createTexture("Bread Specular", "Textures/comp_spec.png"), _resources.createTexture()));;
	_testComp->getTransform()->translate(glm::vec4(-3.8, 1.0, 0.0, 0.0));
	_testComp->getTransform()->rotate(glm::vec3(0,1,0),90.0f);

	_testPrint = std::make_shared<mte::Model>();
	_testPrint->addMesh(std::make_shared<mte::MeshContainer>("printer", _myTestCamera, _resources.createShader("meshShader", "Shaders/meshShader.vs", "Shaders/meshShader.fs"), _resources.createMesh("Meshes/printer.obj", "Printer Mesh"), _resources.createTexture("Printer Texture", "Textures/printer_diffuse.jpg"), _resources.createTexture("Printer Specular", "Textures/printer_spec.jpg"), _resources.createTexture()));;
	_testPrint->getTransform()->translate(glm::vec4(-0.5, 1.1, 0.0, 0.0));
	_testPrint->getTransform()->rotate(glm::vec3(0, 1, 0), -270.0f);

	_testTable = std::make_shared<mte::Model>();
	_testTable->addMesh(std::make_shared<mte::MeshContainer>("table", _myTestCamera, _resources.createShader("meshShader", "Shaders/meshShader.vs", "Shaders/meshShader.fs"), _resources.createMesh("Meshes/table.obj", "Table Mesh"), _resources.createTexture("Table Texture", "Textures/table_diffuse.jpeg"), _resources.createTexture("Table Specular", "Textures/Table_spec.jpeg"), _resources.createTexture()));;
	_testTable->getTransform()->translate(glm::vec4(-2.0, -2.0, 0.0, 0.0));

	_testBuffer = _resources.createBuffer();
	_testBuffer->addDepthTarget();
	_testBuffer->addColourTarget(GL_RGBA8);
	_testBuffer->init(1600 , 900);

}

void MenuScene::Resize(int Width, int Height)
{
	_myTestCamera->Projection = glm::perspective(glm::radians(60.0f), Width / (float)Height, 0.01f, 1000.0f);
}

void MenuScene::virtualUpdate(float dt)
{



	_testBuffer->bind();





	_testBread->update(dt);
	_testBread->draw();

	_testComp->update(dt);
	_testComp->draw();

	_testPrint->update(dt);
	_testPrint->draw();

	_testTable->update(dt);
	_testTable->draw();



	_testBuffer->drawFSQ();
	_testBuffer->renderFSQ();











	glm::vec3 movement = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	float speed = 1.0f;
	float rotSpeed = 1.0f;
	if(_input.getKeyState(GLFW_KEY_W))
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








	if (_input.getKeyState(GLFW_KEY_P)) {
		_changeScene = true;
		_newSceneName = "TestScene";
	}
		

	_myTestCamera->Rotate(rotation);
	_myTestCamera->Move(movement);
	

	if (_input.getKeyState(GLFW_KEY_1) && !buttonTime) {

		buttonTime = 0.3f;
		diffuse = false;
		ambient = false;
		specular = false;

	}
	if (_input.getKeyState(GLFW_KEY_2) && !buttonTime) {
		buttonTime = 0.3f;
		diffuse = false;
		ambient = true;
		specular = false;
	}
	if (_input.getKeyState(GLFW_KEY_3) && !buttonTime) {
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

	if (_input.getKeyState(GLFW_KEY_5) && !buttonTime) {
		buttonTime = 0.3f;
		texture ^= 1;
	}
	if (buttonTime) {
		buttonTime -= dt;
		if (buttonTime < 0.0f)
			buttonTime = 0.0f;
	}

	mte::MeshContainer::ambient = ambient;
	mte::MeshContainer::diffuse = diffuse;
	mte::MeshContainer::specular = specular;
	mte::MeshContainer::bloom = bloom;
	mte::MeshContainer::texture = texture;


	if (_testBread != NULL) {
		std::shared_ptr<mte::LightCube> tempLight = _testBread->getMesh("bread")->_shader->_lightCubes[0];
		tempLight->_pos.y = sin(glfwGetTime()) * 10;
	}

	_resources.drawLightCubes(_myTestCamera);
	_resources.updateDrawCubes();
	
	_testBuffer->unBind();
	_testBuffer->drawBackBuffer();
	_testBuffer->clear();
}
