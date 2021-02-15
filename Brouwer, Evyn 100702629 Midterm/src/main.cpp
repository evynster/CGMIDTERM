
#include "Game.h"
#include <memory>

//this lets us use the gpu
extern "C" {
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x01;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x01;
}



int main()
{
	mte::Logger _logger;
	_logger.createLists();

	std::shared_ptr<mte::Game> myGame = std::make_shared<mte::Game>("Evyn's Terrible Game", 1600, 900);
	
	myGame->runGame();

	mte::Error error;
	error._errorLocation = "main.cpp";
	error._errorSeverity = mte::ErrorSeverityLevel::normal;
	error._errorMessage = "Game has exited!";
	error._errorTypes.push_back(mte::ErrorType::CheckPoint);
	_logger.sendError(error);
	_logger.printErrors();
	return 0;
}