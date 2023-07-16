#include "inputManager.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputManager* tmp = InputManager::getInstance();
	std::vector<Input*> inputs = tmp->getInputs();
	for (size_t i = 0; i < inputs.size(); i++)
	{
		inputs[i]->events(window, key, scancode, action, mods);
	}
}

InputManager::InputManager()
	:System("Default", "InputManager")
{
	m_mainWindow = Window::getInstance()->getGLFWwindow();
	glfwSetKeyCallback(m_mainWindow, keyCallback);
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

std::vector<Input*> InputManager::getInputs()
{
	return m_Inputs;
}

void InputManager::addInput(Input* input)
{
	m_Inputs.push_back(input);
}
