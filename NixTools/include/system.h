#pragma once
#include "directory.h"
#include "debugger.h"

//If NIXTOOLS_EXPORTS preprocessor defined. Then export the functions. Else import.

#ifdef NIXTOOLS_EXPORTS
#define NIXTOOLS_API __declspec(dllexport)
#else
#define NIXTOOLS_API __declspec(dllimport)
#endif

namespace NixTools
{
	class System
	{
	public:
		Debugger debugger;
		Directory directory;
		std::string m_componentName;

		NIXTOOLS_API System(std::string className);
		NIXTOOLS_API System(std::string componentName, std::string className);
	};
};
