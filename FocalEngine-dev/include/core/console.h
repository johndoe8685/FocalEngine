#pragma once
#include "window.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

class DebugConsole
{
public:
	DebugConsole(Window* window);
	
	void run();
};