#pragma once
#include <vendor/GLFW/glfw3.h>

class Input
{
public:
	virtual void events(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
};