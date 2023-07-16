#pragma once
#include <vendor/NixTools/system.h>
#include "inputManager.h"

class GUI : public NixTools::System, private Input
{
public:
	GUI(std::string componentName);
	void events(GLFWwindow* window, int key, int scancode, int action, int mods);
};