#pragma once
#include <iostream>
#include <vendor/NixTools/system.h>
#include <vendor/glad/glad.h>
#include <vendor/GLFW/glfw3.h>

/* Singletons */
static float s_DeltaTime = 0.0f;

class Window : public NixTools::System
{
private:
	GLFWwindow* m_glfwWindow;
	static Window* s_instance;

	float m_curFrame, m_lastFrame;

	bool isFailed;
	bool isStarted;

	Window(std::string componentName, int width, int height, bool isFullscreen);
public:
	static void createInstance(std::string componentName, int width, int height, bool isFullscreen);
	static Window* getInstance();
	~Window();

	bool renderLoop();
	
	void setWindowSize(int width, int height);
	void getWindowSize(int* width, int* height);

	GLFWwindow* getGLFWwindow();
};