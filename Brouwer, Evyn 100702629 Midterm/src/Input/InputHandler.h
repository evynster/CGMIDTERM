#pragma once
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include "Logging/Logger.h"

namespace mte {

	class InputHandler {
	public:
		InputHandler() {};
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void cursor_postion_callback(GLFWwindow* window, double xPos, double yPos);
		void mouse_button_callback(GLFWwindow* window,int button,int action, int mods);

		/*
		modes:
		GLFW_CURSOR_DISABLED
		GLFW_CURSOR_HIDDEN
		GLFW_CURSOR_NORMAL
		*/
		void cursorMode(GLFWwindow* window, int mode);

		bool getKeyState(int key);
		glm::vec2 getMousePos();
		bool getMouseButtonState(int button);

	private:

		static bool _keylist[1024];
		static bool _mouseButtonList[32];
		static double _mouseX, _mouseY;
		Logger _logger;
	};

}