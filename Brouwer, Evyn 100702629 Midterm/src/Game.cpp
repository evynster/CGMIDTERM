#include "Game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void GlfwWindowResizedCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	mte::Game* myGame = reinterpret_cast<mte::Game*>(glfwGetWindowUserPointer(window));
	if (myGame) {
		myGame->Resize(width, height);
	}
}

static void GLFW_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	mte::Game* myGame = (mte::Game*)glfwGetWindowUserPointer(window);
	if (myGame) {
		myGame->_input.key_callback(window,key,scancode,action,mods);
	}

}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	mte::Game* myGame = (mte::Game*)glfwGetWindowUserPointer(window);
	if (myGame) {
		myGame->_input.cursor_postion_callback(window,xpos,ypos);
	}
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	mte::Game* myGame = (mte::Game*)glfwGetWindowUserPointer(window);
	if (myGame) {
		myGame->_input.mouse_button_callback(window,button,action,mods);
	}

}


mte::Game::Game(std::string gameName, GLuint width, GLuint height)
	: _gameName(gameName)
{
	stbi_set_flip_vertically_on_load(true);
	_width = width;
	_height = height;
	_gameWindow = NULL;
	_sceneManager = std::make_shared<SceneManager>();
	if (!init())
		glfwTerminate();
}


mte::Game::~Game()
{
	glfwTerminate();
}

bool mte::Game::init()
{
	// Initialize GLFW
	if (!glfwInit() ) {
		Error error;
		error._errorLocation = "Game.cpp";
		error._errorMessage = "Failed to initialize GLFW";
		error._errorSeverity = mte::ErrorSeverityLevel::gameCrashing;
		error._errorTypes.push_back(mte::ErrorType::Init);
		_logger.sendError(error);
		return false;
	}
	_gameWindow = glfwCreateWindow(_width, _height, _gameName.c_str(), nullptr, nullptr);

	if (!_gameWindow) {
		Error error;
		error._errorLocation = "Game.cpp";
		error._errorMessage = "Failed to create Game Window";
		error._errorSeverity = mte::ErrorSeverityLevel::gameCrashing;
		error._errorTypes.push_back(mte::ErrorType::Init);
		_logger.sendError(error);
		return false;
	}

	glfwSetWindowUserPointer(_gameWindow, this);
	glfwSetWindowSizeCallback(_gameWindow, GlfwWindowResizedCallback);
	glfwSetKeyCallback(_gameWindow, GLFW_key_callback);
	glfwSetCursorPosCallback(_gameWindow, cursor_position_callback);
	glfwSetMouseButtonCallback(_gameWindow, mouse_button_callback);

	glfwMakeContextCurrent(_gameWindow);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
		Error error;
		error._errorLocation = "Game.cpp";
		error._errorMessage = "Failed to initialize Glad";
		error._errorSeverity = mte::ErrorSeverityLevel::gameCrashing;
		error._errorTypes.push_back(mte::ErrorType::Init);
		_logger.sendError(error); 
		return false;
	}

	// Display our GPU and OpenGL version
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;


	/*
	create a function for each scene
	*/
	std::shared_ptr<MenuScene> menuScene = std::make_shared<MenuScene>(_gameWindow,"MenuScene");
	_sceneManager->addScene(menuScene);
	_sceneManager->_currentScene = menuScene;

	std::shared_ptr<TestScene> testScene = std::make_shared<TestScene>(_gameWindow, "TestScene");
	_sceneManager->addScene(testScene);

	glEnable(GL_DEPTH_TEST);

	Error error;
	error._errorLocation = "Game.cpp";
	error._errorMessage = "Game has been initialized!";
	error._errorSeverity = mte::ErrorSeverityLevel::great;
	error._errorTypes.push_back(mte::ErrorType::CheckPoint);
	_logger.sendError(error);
	return true;
}


void mte::Game::runGame()
{
	Error error;
	error._errorLocation = "game.cpp";
	error._errorSeverity = mte::ErrorSeverityLevel::normal;
	error._errorTypes.push_back(mte::ErrorType::CheckPoint);
	error._errorMessage = "Game started Running!";
	_logger.sendError(error);

	static float prevFrame = (float)glfwGetTime();
	while (!glfwWindowShouldClose(_gameWindow)) {
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

		

		float thisFrame = (float)glfwGetTime();
		float deltaTime = thisFrame - prevFrame;
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_sceneManager->update(deltaTime);

		prevFrame = thisFrame;
		

		glfwSwapBuffers(_gameWindow);

		glfwPollEvents(); 

		_logger.printErrors();
	}

}

void mte::Game::Resize(GLuint width, GLuint height)
{
	_width = width;
	_height = height;
	for (auto x : _sceneManager->_scenes)
		x->Resize(width,height);
	for (auto x : mte::ResourceManager::_buffers)
		x->resize(width, height);
	
}


GLint mte::Game::_height = 0;
GLint mte::Game::_width = 0;
