#include "SceneManager.h"

mte::SceneManager::SceneManager()
:_currentScene(NULL)
{
}

void mte::SceneManager::update(float dt)
{
	if (_currentScene != NULL) {//if there is a scene active
		if (!_currentScene->_changeScene) {//if the current scene doesn't want to change
			_currentScene->update(dt);//update the scene
		}
		else {//if the current scene wants to change
			if (_currentScene->_newSceneName != _currentScene->_sceneName) {//if the scenes to change to is not this scene
				if (_currentScene->_newSceneName!="") {//if there is an actual scene name to change to
					for (unsigned i = 0; i < _scenes.size(); i++) {//check all the scenes
						if (_currentScene->_newSceneName == _scenes[i]->_sceneName) {//if we have found the correct scene to change to
							_currentScene->_newSceneName = "";
							_currentScene->_changeScene = false;
							_currentScene = _scenes[i];//change the scene
							_currentScene->_changeScene = false;
							_currentScene->_newSceneName = "";
							_currentScene->update(dt);
						}
						else if (i == _scenes.size() - 1) {
							_currentScene->update(dt);
							_currentScene->_changeScene = false;
							Error error;
							error._errorLocation = "SceneManager.cpp";
							error._errorMessage = "There is no " + _currentScene->_newSceneName + " Scene!";
							error._errorSeverity = mte::ErrorSeverityLevel::bad;
							_logger.sendError(error);
							_currentScene->_newSceneName = "";
						}
					}
				
				}
				else {
					_currentScene->update(dt);
					Error error;
					error._errorLocation = "SceneManager.cpp";
					error._errorMessage = _currentScene->_sceneName + " wants to change scene, but doesn't know to what scene to change to!";
					error._errorSeverity = mte::ErrorSeverityLevel::bad;
					_logger.sendError(error);
					_currentScene->_changeScene = false;
				}
			}
			else {
				Error error;
				error._errorLocation = "SceneManager.cpp";
				error._errorMessage = _currentScene->_sceneName + " is trying to swap to itself!";
				error._errorSeverity = mte::ErrorSeverityLevel::bad;
				_logger.sendError(error);
				_currentScene->_changeScene = false;
				_currentScene->_newSceneName = "";
				_currentScene->update(dt);
			}
			
		}
	}
	else {//if the current scene is NULL
		Error error;
		error._errorLocation = "SceneManager.cpp";
		error._errorMessage = "There is no active Scene!";
		error._errorSeverity = mte::ErrorSeverityLevel::severe;
		_logger.sendError(error);
	}
}
