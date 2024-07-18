#include "core/coreGUI.h"

void CoreGUI::createInstance(Window* window, std::string componentName)
{
	if (s_instance == nullptr)
	{
		s_instance = new CoreGUI(window, componentName);
	}
	else
	{
		s_instance->debugger.giveMessage(NixTools::Debugger::Error, "InputManager was already created!!");
	}
}

CoreGUI* CoreGUI::getInstance()
{
	if (s_instance != nullptr)
	{
		return s_instance;
	}
	else
	{
		NixTools::Debugger tmp("CoreGUI");
		tmp.giveMessage(NixTools::Debugger::Error, "CoreGUI isnt created! Create CoreGUI first.");
	}
}

CoreGUI::CoreGUI(Window* window, std::string componentName)
	:System(componentName, "CoreGUI"), m_window(window), EscClicked(false), tildeClicked(false), Fclicked(false), F11clicked(false), shouldRenderExit(false), shouldExit(false)
{
	KeyboardInput* keyboardInput = static_cast<KeyboardInput*>(this);
	InputManager::getInstance()->addInput(keyboardInput);

	/* Initialize ImGUI */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window->getGLFWwindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	/* ImGUI style */
	// This style is from simongeilfus/Cinder-ImGui
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowMinSize = ImVec2(160, 20);
	style.FramePadding = ImVec2(4, 2);
	style.ItemSpacing = ImVec2(6, 2);
	style.ItemInnerSpacing = ImVec2(6, 4);
	style.Alpha = 0.95f;
	style.WindowRounding = 4.0f;
	style.FrameRounding = 2.0f;
	style.IndentSpacing = 6.0f;
	style.ItemInnerSpacing = ImVec2(2, 4);
	style.ColumnsMinSpacing = 50.0f;
	style.GrabMinSize = 14.0f;
	style.GrabRounding = 16.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 16.0f;

	style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.28f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.65f, 0.07f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.65f, 0.07f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.85f, 0.07f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.92f, 0.18f, 0.29f, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.9f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.f, 0.f, 0.f, 0.6f);


	/* Font */
	//directory.changePath("/res/fonts/Px437_IBM_VGA_9x16.ttf");
	//directory.changePath("/res/fonts/Inter-Bold.ttf");
	directory.changePath("/res/fonts/Inter-Medium.ttf");
	ImFont* font1 = io.Fonts->AddFontFromFileTTF(directory.getPath().c_str(), 16);
}


void CoreGUI::keyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		EscClicked = true;
		Fclicked = false;
		callEscClicked();
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS)
	{

	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		if (!EscClicked)
		{
			if (!Fclicked)
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				Fclicked = true;
			}
			else
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				Fclicked = false;
			}
		}
	}

	if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
	{
		if (!F11clicked)
		{
			//Set window into borderless fullscreen
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			glfwGetWindowPos(window, &prev_xPos, &prev_yPos);
			glfwGetWindowSize(window, &prev_width, &prev_height);

			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			F11clicked = true;
		}
		else
		{
			glfwSetWindowMonitor(window, nullptr, prev_xPos, prev_yPos, prev_width, prev_height, 0);
			F11clicked = false;
		}
	}
}

void CoreGUI::addCamera(CoreGUIListener* listener_camera)
{
	m_cameraList.push_back(listener_camera);
}

void CoreGUI::removeCamera(CoreGUIListener* listener_camera)
{
	m_cameraList.remove(listener_camera);
}

void CoreGUI::callEscClicked()
{
	std::list<CoreGUIListener*>::iterator iterator = m_cameraList.begin();
	while (iterator != m_cameraList.end())
	{
		(*iterator)->onEscClicked(&EscClicked);
		++iterator;
	}
}

void CoreGUI::run()
{
	/* Start New Frame and make the backend ready */
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (EscClicked)
	{
		renderMenu();
	}

	if (shouldRenderExit)
	{
		renderExit();
	}

	/* Do some Engine related changes that is related to CoreGUI */
	if (shouldExit)
	{
		glfwSetWindowShouldClose(m_window->getGLFWwindow(), true);
	}

	//ImGui::ShowDemoWindow();
	//ImGui::ShowStyleEditor();

	/* Render all GUI */
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void CoreGUI::renderMenu()
{
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("Engine"))
	{
		ImGui::MenuItem("Engine Options", nullptr, false, false);
		if (ImGui::MenuItem("Exit"))
		{
			shouldRenderExit = true;
			tildeClicked = false;
		}
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
}

void CoreGUI::renderExit()
{
	ImGui::OpenPopup("Exit NixEngine");

	/* Always center this window when appearing */
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(350.0f, 80.0f));

	if (ImGui::BeginPopupModal("Exit NixEngine", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
	{
		ImGui::Text("Are you sure you want to exit?");
		ImGui::Dummy(ImVec2(0.0f, 4.0f));

		if (ImGui::Button("Exit"))
		{
			shouldExit = true;
			EscClicked = false;
			callEscClicked();
			ImGui::CloseCurrentPopup();
		}
		
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();

		if (ImGui::Button("Cancel"))
		{
			shouldExit = false;
			EscClicked = false;
			shouldRenderExit = false;
			callEscClicked();
			ImGui::CloseCurrentPopup();
		}
	}

	ImGui::EndPopup();
}

