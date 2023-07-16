#include "game/gui.h"

GUI::GUI(std::string componentName)
	:System(componentName, "GUI")
{
	Input* input = static_cast<Input*>(this);
	InputManager::getInstance()->addInput(input);
}

void GUI::events(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, true);
}