#pragma once
#include <vector>
#include <vendor/NixTools/system.h>
#include "window.h"
#include "keyboardinput.h"
#include "mouseinput.h"

class InputManager : public NixTools::System
{
private:
	//Singleton Constructor and pointer
	InputManager();
	static InputManager* s_instance;
	
	GLFWwindow* m_mainWindow;

	std::vector<KeyboardInput*> m_KeyboardInputs;
	std::vector<MouseInput*> m_MouseInputs;
public:
	//Singleton creation
	static void createInstance();
	static InputManager* getInstance();

	std::vector<KeyboardInput*> getKeyboardInputs();
	std::vector<MouseInput*> getMouseInputs();

	void addInput(KeyboardInput* input);
	void addInput(MouseInput* input);
};