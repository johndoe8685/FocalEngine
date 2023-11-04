#pragma once
#include <vendor/NixTools/system.h>
#include "inputManager.h"

class GUI : public NixTools::System, KeyboardInput
{
public:
	GUI(std::string componentName);
	void keyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mods);
};