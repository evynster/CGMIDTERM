#pragma once
#include <string>
#include <vector>
#include <glfw/glfw3.h>
#include <iostream>
#include <windows.h> 

namespace mte {
	
	enum class ErrorSeverityLevel
	{
		normal = 15,//white 7 or 15
		bad = 14,//yellow 14
		severe=6,//orange
		gameCrashing=12,//red 4 or 12
		good=10,//green 2 or 10
		great=11,//blue 3 or 11
		other=13,//purple 4 or 13
		boring=8, //gray 8
	};

	enum class ErrorType
	{
		Init=0,
		Log,
		CheckPoint,
		Bounds,
		LoadFail
	};

	struct Error {
	public:
		Error();
		std::string _errorLocation = "";
		std::string _errorMessage = "";
		float _errorTime;
		ErrorSeverityLevel _errorSeverity = ErrorSeverityLevel::normal;
		void print();
		static unsigned _errorTotal;
		unsigned _errorID = 0;
		std::vector <ErrorType> _errorTypes;
	private:
	};


	class Logger {
	public:
		void sendError(Error error) { _errorList.push_back(error); };

		void printErrors();

		void createLists();

	private:

		static std::vector<Error> _errorList;

		bool _blackListBool = true; // while this is true it will not print anything on the blacklist, while false it will only print types on the white list

		static std::vector<ErrorType> _errorWhiteList;
		static std::vector<ErrorType> _errorBlackList;

	};

}