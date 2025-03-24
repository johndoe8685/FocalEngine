#pragma once
#include "vendor/NixTools/system.h"
#include "vendor/csys/system.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/imgui_console/imgui_console.h"

class DebugConsole : public NixTools::System
{
private:
	csys::System m_consoleSystem;
	size_t m_historyIndex;

	std::string m_inputBuffer;
	int InputCallback(ImGuiInputTextCallbackData* data);
public:
	ImGuiConsole m_console;
	DebugConsole(std::string componentName, size_t inputBufferSize = 256);
	
	void run(bool* p_open);
	void draw(bool* p_open);
};