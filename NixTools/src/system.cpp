#include "system.h"

namespace NixTools
{
	System::System(std::string className)
		:debugger("Unknown", className), m_componentName("Unknown")
	{
	}

	System::System(std::string componentName, std::string className)
		:m_componentName(componentName), debugger(componentName, className)
	{
	}
};