#pragma once
#include <vector>
#include <vendor/NixTools/system.h>
#include "window.h"
#include "input.h"

class InputManager : public NixTools::System
{
private:
	static InputManager* s_instance;
	GLFWwindow* m_mainWindow;

	std::vector<Input*> m_Inputs;

	InputManager();
public:
	static void createInstance();
	static InputManager* getInstance();


	std::vector<Input*> getInputs();
	void addInput(Input* input);
};