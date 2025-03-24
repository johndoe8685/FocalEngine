#include "window.h"

void errorCallback(int code, const char* description)
{
	std::string value = description;

	NixTools::Debugger dbg("GLFW");
	dbg.giveMessage(NixTools::Error, description, code);
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window(std::string componentName, int width, int height, bool isFullscreen)
	:NixTools::System(componentName, "Window"), isFailed(false), m_curFrame(0.0f), m_lastFrame(0.0f), isStarted(false)
{
	/* GLFW Init Code Here */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Window Creation */
	if (isFullscreen) m_glfwWindow = glfwCreateWindow(width, height, "NixEngine", glfwGetPrimaryMonitor(), NULL);
	else m_glfwWindow = glfwCreateWindow(width, height, "NixEngine", NULL, NULL);

	if (!m_glfwWindow)
	{
		debugger.giveMessage(NixTools::Error, "GLFW Window Creation Failed!");
		isFailed = true;
		glfwTerminate();
	}

	if (!isFailed)
	{
		glfwMakeContextCurrent(m_glfwWindow);
		glfwSwapInterval(1);
		gladLoadGL();

		/* OpenGL Spesific Code Here */
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		//Clear the screen with pink Error color
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

		if (glfwRawMouseMotionSupported) glfwSetInputMode(m_glfwWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

		glfwSetErrorCallback(errorCallback);
		glfwSetFramebufferSizeCallback(m_glfwWindow, frameBufferSizeCallback);
	}
}

void Window::createInstance(std::string componentName, int width, int height, bool isFullscreen)
{
	if (s_instance == nullptr)
	{
		s_instance = new Window(componentName, width, height, isFullscreen);
	}
	else
	{
		s_instance->debugger.giveMessage(NixTools::Error, "Window was already created!!");
	}
}

Window* Window::getInstance()
{
	if (s_instance != nullptr)
	{
		return s_instance;
	}
	else
	{
		NixTools::Debugger tmp("Window");
		tmp.giveMessage(NixTools::Error, "Window isnt created! Create window first.");
	}
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::renderLoop(float* deltaTime, double* elapsedTime)
{
	if (!isStarted) isStarted = true;
	else glfwSwapBuffers(m_glfwWindow);
	glfwPollEvents();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Get Delta Time */
	m_curFrame = glfwGetTime();
	*deltaTime = m_curFrame - m_lastFrame;
	m_lastFrame = m_curFrame;

	*elapsedTime += *deltaTime;
	
	return !glfwWindowShouldClose(m_glfwWindow);
}

void Window::setWindowSize(int width, int height)
{
	glfwSetWindowSize(m_glfwWindow, width, height);
}

void Window::getWindowSize(int* width, int* height)
{
	glfwGetWindowSize(m_glfwWindow, width, height);
}

void Window::exit()
{
	glfwSetWindowShouldClose(m_glfwWindow, true);
}

GLFWwindow* Window::getGLFWwindow()
{
	return m_glfwWindow;
}
