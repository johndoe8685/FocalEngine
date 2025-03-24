#pragma once
#include <iostream>

//If NIXTOOLS_EXPORTS preprocessor defined. Then export the functions. Else import.

#ifdef NIXTOOLS_EXPORTS
#define NIXTOOLS_API __declspec(dllexport)
#else
#define NIXTOOLS_API __declspec(dllimport)
#endif


namespace NixTools
{
	enum DebugLevel
	{
		Info,
		Warning,
		Error,
		Unknown
	};

	class Debugger
	{
	private:
		std::string m_className;
		std::string m_componentName;
		std::string m_previousMessage;
		int m_previousValueInt;
		float m_previousValueFloat;
		unsigned int m_previousValueUInt;
	public:
		NIXTOOLS_API Debugger(std::string componentName, std::string className);
		NIXTOOLS_API Debugger(std::string className);

		NIXTOOLS_API void giveMessage(DebugLevel level, std::string message);
		NIXTOOLS_API void giveMessage(DebugLevel level, std::string title, std::string message);
		template<typename T>
		NIXTOOLS_API void giveMessage(DebugLevel level, std::string message, T value);
		NIXTOOLS_API void giveMessage(DebugLevel level, std::string message, unsigned int value);
		NIXTOOLS_API void giveMessage(DebugLevel level, std::string message, int value);
		NIXTOOLS_API void giveMessage(DebugLevel level, std::string message, float value);
	};
}
