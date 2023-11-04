#pragma once
#include <vendor/GLFW/glfw3.h>

class KeyboardInput
{
public:
	virtual void keyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
};