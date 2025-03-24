#include "engine.h"

/* Singletons */
Window* Window::s_instance = nullptr;
InputManager* InputManager::s_instance = nullptr;
ShaderManager* ShaderManager::s_instance = nullptr;
AssetManager* AssetManager::s_instance = nullptr;
CoreGUI* CoreGUI::s_instance = nullptr;

int main()
{
	/* Init glfw before Engine init */
	if (!glfwInit()) return -1;

	GameEngine engine;
	engine.run();
}