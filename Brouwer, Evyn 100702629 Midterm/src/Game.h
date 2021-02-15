#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include<iostream>
#include <memory>

#include "SceneStuff/SceneManager.h"
#include "Logging/Logger.h"

#include "SceneStuff/MenuScene.h"
#include "SceneStuff/TestScene.h" 



namespace mte {

	class Game
	{
	public:
		Game(std::string gameName, GLuint width, GLuint height);
		
		~Game();

		/*
		this function will loop continously until the window is closed
		*/
		void runGame();

		void Resize(GLuint width, GLuint height);

		InputHandler _input;
		Logger _logger;
	private:
		/*
		this function is a contructor
		*/
		bool init();


		
		static GLint _width, _height;
		std::string _gameName;

		GLFWwindow* _gameWindow;

		std::shared_ptr<SceneManager> _sceneManager;
	};
}