#include "inputManager.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputManager* tmp = InputManager::getInstance();
	std::vector<KeyboardInput*> inputs = tmp->getKeyboardInputs();
	for (size_t i = 0; i < inputs.size(); i++)
	{
		inputs[i]->keyboardEvents(window, key, scancode, action, mods);
	}
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	InputManager* tmp = InputManager::getInstance();
	std::vector<MouseInput*> inputs = tmp->getMouseInputs();
	for (size_t i = 0; i < inputs.size(); i++)
	{
		inputs[i]->mouseEvents(window, xPos, yPos);
	}
}

InputManager::InputManager()
	:System("Default", "InputManager")
{
	m_mainWindow = Window::getInstance()->getGLFWwindow();
	glfwSetKeyCallback(m_mainWindow, keyCallback);
	glfwSetCursorPosCallback(m_mainWindow, mouseCallback);
}

void InputManager::createInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new InputManager();
	}
	else
	{
		s_instance->debugger.giveMessage(NixTools::Debugger::Error, "InputManager was already created!!");
	}
}

InputManager* InputManager::getInstance()
{
	if (s_instance != nullptr)
	{
		return s_instance;
	}
	else
	{
		NixTools::Debugger tmp("InputManager");
		tmp.giveMessage(NixTools::Debugger::Error, "InputManager isnt created! Create InputManager first.");
	}
}

std::vector<KeyboardInput*> InputManager::getKeyboardInputs()
{
	return m_KeyboardInputs;
}

std::vector<MouseInput*> InputManager::getMouseInputs()
{
	return m_MouseInputs;
}

void InputManager::addInput(KeyboardInput* input)
{
	m_KeyboardInputs.push_back(input);
}

void InputManager::addInput(MouseInput* input)
{
	m_MouseInputs.push_back(input);
}
