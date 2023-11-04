#pragma once
#include <vendor/GLFW/glfw3.h>

class MouseInput
{
public:
	virtual void mouseEvents(GLFWwindow* window, double xPos, double yPos) = 0;
};