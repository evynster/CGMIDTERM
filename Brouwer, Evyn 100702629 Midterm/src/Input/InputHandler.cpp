#include "InputHandler.h"

void mte::InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (!key < 1024) {
		if (action == GLFW_PRESS) {
			_keylist[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			_keylist[key] = false;
		}
	}
	else {
		Error error;
		error._errorLocation = "InputHandler.cpp";
		error._errorSeverity = mte::ErrorSeverityLevel::bad;
		error._errorMessage = "Keyboard key " + std::to_string(key) + " is not supported!";
		error._errorTypes.push_back(mte::ErrorType::Bounds);
		_logger.sendError(error);
	}
}

void mte::InputHandler::cursor_postion_callback(GLFWwindow* window, double xPos, double yPos)
{
	_mouseX = xPos;
	_mouseY = yPos;
}

void mte::InputHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (!button < 32) {
		if (action == GLFW_PRESS) {
			_mouseButtonList[button] = true;
		}
		else if (action == GLFW_RELEASE) {
			_mouseButtonList[button] = false;
		}
	}
	else {
		Error error;
		error._errorLocation = "InputHandler.cpp";
		error._errorSeverity = mte::ErrorSeverityLevel::bad;
		error._errorMessage = "Mouse button " + std::to_string(button) + " is not supported!";
		error._errorTypes.push_back(mte::ErrorType::Bounds);
		_logger.sendError(error);
	}

}

void mte::InputHandler::cursorMode(GLFWwindow* window, int mode)
{
	glfwSetInputMode(window, GLFW_CURSOR, mode);
}

bool mte::InputHandler::getKeyState(int key)
{
	return _keylist[key];
}

glm::vec2 mte::InputHandler::getMousePos()
{
	return glm::vec2(_mouseX,_mouseY);
}

bool mte::InputHandler::getMouseButtonState(int button)
{
	return _mouseButtonList[button];
}

double mte::InputHandler::_mouseX = 0.0f;
double mte::InputHandler::_mouseY = 0.0f;

bool mte::InputHandler::_keylist[1024];
bool mte::InputHandler::_mouseButtonList[32];