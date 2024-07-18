#pragma once
#include <list>
#include <vendor/NixTools/system.h>
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "inputManager.h"
#include "interface/CoreGUIListener.h"

class CoreGUI : public NixTools::System, KeyboardInput
{
private:
	//Singleton Constructor and pointer
	CoreGUI(Window* window, std::string componentName);
	static CoreGUI* s_instance;

	Window* m_window;

	bool EscClicked, tildeClicked, Fclicked, F11clicked;

	int prev_xPos, prev_yPos;
	int prev_width, prev_height;

	bool shouldRenderExit, shouldExit;
	std::list<CoreGUIListener*> m_cameraList;
public:
	//Singleton creation
	static void createInstance(Window* window, std::string componentName);
	static CoreGUI* getInstance();
	
	void keyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mods);

	void addCamera(CoreGUIListener* listener_camera);
	void removeCamera(CoreGUIListener* listener_camera);

	void callEscClicked();

	void run();

	void renderMenu();
	void renderExit();
};