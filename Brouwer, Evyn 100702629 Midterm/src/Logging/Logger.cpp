#include "Logger.h"

void mte::Logger::printErrors()
{
	if (_blackListBool) {
		for (auto x : _errorList) {
			for (auto z : _errorBlackList) {
				bool blacklisted = false;
				for (auto y : x._errorTypes) {
					if (z == y) {
						blacklisted = true;
						continue;
					}
				}
				if(!blacklisted)
					x.print();
			}
		}		
	}
	else
	{
		for (auto x : _errorList) {
			for (auto z : _errorWhiteList) {
				bool whitelisted = false;
				for (auto y : x._errorTypes) {
					if (z == y) {
						whitelisted = true;
						continue;
					}
				}
				if (whitelisted)
					x.print();
			}
		}
	}

	_errorList.clear();
}

void mte::Logger::createLists()
{
	_errorBlackList.push_back(mte::ErrorType::Log);
}

mte::Error::Error()
{
	_errorTime = (float)glfwGetTime();
	_errorTotal++;
	_errorID=_errorTotal;
	
}

void mte::Error::print()
{
	HANDLE  hConsole;//windows only
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, (int)_errorSeverity);
	printf("Time: %4.2f File: %s  \n",_errorTime, _errorLocation.c_str());
	printf("ID: %d %s \n\n",_errorID,_errorMessage.c_str());



	SetConsoleTextAttribute(hConsole, 7);
}

std::vector<mte::Error> mte::Logger::_errorList;
unsigned mte::Error::_errorTotal = 0;

std::vector<mte::ErrorType> mte::Logger::_errorBlackList;
std::vector<mte::ErrorType> mte::Logger::_errorWhiteList;