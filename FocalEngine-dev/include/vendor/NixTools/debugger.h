#pragma once
#include <iostream>

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
		Debugger(std::string componentName, std::string className);
		Debugger(std::string className);

		void giveMessage(DebugLevel level, std::string message);
		void giveMessage(DebugLevel level, std::string title, std::string message);
		void giveMessage(DebugLevel level, std::string message, unsigned int value);
		void giveMessage(DebugLevel level, std::string message, int value);
		void giveMessage(DebugLevel level, std::string message, float value);
	};
}
