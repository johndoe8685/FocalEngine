#include "game/gui.h"

GUI::GUI(std::string componentName)
	:System(componentName, "GUI")
{
	KeyboardInput* keyboardInput = static_cast<KeyboardInput*>(this);
	InputManager::getInstance()->addInput(keyboardInput);
}

void GUI::keyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}