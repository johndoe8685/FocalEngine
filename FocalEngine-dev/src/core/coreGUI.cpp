#include "core/coreGUI.h"

void CoreGUI::createInstance(Window* window, std::string componentName)
{
	if (s_instance == nullptr)
	{
		s_instance = new CoreGUI(window, componentName);
	}
	else
	{
		s_instance->debugger.giveMessage(NixTools::Error, "InputManager was already created!!");
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
		tmp.giveMessage(NixTools::Error, "CoreGUI isnt created! Create CoreGUI first.");
	}
}

CoreGUI::CoreGUI(Window* window, std::string componentName)
	:System(componentName, "CoreGUI"), m_window(window), EscClicked(false), tildeClicked(false), Fclicked(false), F11clicked(false), consoleClicked(false),
	editorClicked(false), shouldRenderExit(false), shouldExit(false), shouldShowOverlay(true)
{
	KeyboardInput* keyboardInput = static_cast<KeyboardInput*>(this);
	InputManager::getInstance()->addInput(keyboardInput);

	
	/* Initialize ImGUI */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window->getGLFWwindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	m_console = new DebugConsole("Debug", 256);

	/* ImGUI style */
	// This style is from simongeilfus/Cinder-ImGui
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowMinSize = ImVec2(160, 20);
	style.FramePadding = ImVec2(4, 2);
	style.ItemSpacing = ImVec2(6, 2);
	style.ItemInnerSpacing = ImVec2(6, 4);
	style.Alpha = 0.95f;
	style.WindowRounding = 0.0f;
	style.FrameRounding = 2.0f;
	style.IndentSpacing = 6.0f;
	style.ItemInnerSpacing = ImVec2(2, 4);
	style.ColumnsMinSpacing = 50.0f;
	style.GrabMinSize = 14.0f;
	style.GrabRounding = 16.0f;
	style.ScrollbarSize = 20.0f;
	style.ScrollbarRounding = 0.0f;

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
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
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
	style.Colors[ImGuiCol_Tab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.65f, 0.07f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_TabSelected] = ImVec4(0.65f, 0.07f, 0.07f, 1.00f);

	ImGui::PushStyleVar(ImGuiStyleVar_TabBarBorderSize, 0.0f);

	/* Font */
	//directory.changePath("/res/fonts/Px437_IBM_VGA_9x16.ttf");
	directory.changePath("/res/fonts/Inter-Bold.ttf");
	//directory.changePath("/res/fonts/Inter-Medium.ttf");
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImFont* font1 = io.Fonts->AddFontFromFileTTF(directory.getPath().c_str(), 16, nullptr, io.Fonts->GetGlyphRangesTurkish());

	directory.changePath("/res/fonts/AcPlus_IBM_VGA_9x16.ttf");
	ImFont* font2 = io.Fonts->AddFontFromFileTTF(directory.getPath().c_str(), 16, nullptr, io.Fonts->GetGlyphRangesTurkish());

	directory.changePath("/res/fonts/PxPlus_IBM_VGA_9x16.ttf");
	ImFont* font3 = io.Fonts->AddFontFromFileTTF(directory.getPath().c_str(), 16, nullptr, io.Fonts->GetGlyphRangesTurkish());

	directory.changePath("/res/fonts/MxPlus_IBM_VGA_9x16.ttf");
	ImFont* font4 = io.Fonts->AddFontFromFileTTF(directory.getPath().c_str(), 16, nullptr, io.Fonts->GetGlyphRangesTurkish());

	/* Core GUI related classes */
}


void CoreGUI::keyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		if (EscClicked)
		{
			EscClicked = false;
			callEscClicked();
		}
		else
		{
			EscClicked = true;
			Fclicked = false;
			callEscClicked();
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS)
	{
		if (consoleClicked) consoleClicked = false;
		else consoleClicked = true;
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
			glfwSwapInterval(1);
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
	/*
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	*/

	if (shouldShowOverlay)
	{
		renderFPS();
	}

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
		m_window->exit();
	}
	
	if (m_console->m_console.m_shouldExit)
	{
		m_window->exit();
	}

	/*
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	*/
}

void CoreGUI::renderMenu()
{
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("Engine"))
	{
		ImGui::MenuItem("Engine Options", nullptr, false, false);
		if (shouldShowOverlay)
		{
			if (ImGui::MenuItem("Hide Overlay"))
			{
				shouldShowOverlay = false;
			}
		}
		else
		{
			if (ImGui::MenuItem("Show Overlay"))
			{
				shouldShowOverlay = true;
			}
		}
		if (ImGui::MenuItem("Exit"))
		{
			shouldRenderExit = true;
			tildeClicked = false;
		}
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Window"))
	{
		ImGui::MenuItem("Engine Windows", nullptr, false, false);
		ImGui::MenuItem("Text Editor");
		ImGui::MenuItem("Shader Editor");
		ImGui::EndMenu();
	}

	
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.0f, 0.0f));
	if (ImGui::Button("Console"))
	{	
		if (!consoleClicked)
		{
			consoleClicked = true;
		}
		else
		{
			consoleClicked = false;
		}
	}
	ImGui::PopStyleColor();

	if (consoleClicked)
	{
		//m_console.run(&consoleClicked);
		m_console->draw(&consoleClicked);
	}

	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.0f, 0.0f));
	if (ImGui::Button("Editor"))
	{
		if (!editorClicked)
		{
			editorClicked = true;
		}
		else
		{
			editorClicked = false;
		}
	}
	ImGui::PopStyleColor();

	if (editorClicked)
	{
		renderTextEditor();
	}

	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.0f, 0.0f));
	if (ImGui::Button("Resume"))
	{
		EscClicked = false;
		callEscClicked();
	}
	ImGui::PopStyleColor();
	ImGui::EndMainMenuBar();
}

#include "shaderManager.h"

void CoreGUI::renderTextEditor()
{
	static char basicVertexText[1024 * 32];
	static char basicFragmentText[1024 * 32];
	static char testVertexText[1024 * 32];
	static char testfragmentText[1024 * 32];
	static char frameRateVertexText[1024 * 32];
	static char frameRatefragmentText[1024 * 32];
	static bool doOnce = true;
	
	if (doOnce)
	{
		ShaderManager* shaderManager = ShaderManager::getInstance();
		Shader* shader = shaderManager->getShader("MainShader");
		Shader* testShader = shaderManager->getShader("checkerShader");
		Shader* skyboxShader = shaderManager->getShader("skybox");
		Shader* testFrameRateShader = shaderManager->getShader("TestFramerateShader");
		std::string basicVertexShaderText = shader->GetShaderSource(shader->directory.getWorkDirectory() + shader->m_VertexFilePath);
		std::string basicFragmentShaderText = shader->GetShaderSource(shader->directory.getWorkDirectory() + shader->m_FragmentFilePath);
		std::string testVertexShaderText = shader->GetShaderSource(shader->directory.getWorkDirectory() + testShader->m_VertexFilePath);
		std::string testFragmentShaderText = shader->GetShaderSource(shader->directory.getWorkDirectory() + testShader->m_FragmentFilePath);
		std::string frameRateVertexShaderText = shader->GetShaderSource(shader->directory.getWorkDirectory() + testFrameRateShader->m_VertexFilePath);
		std::string frameRateFragmentShaderText = shader->GetShaderSource(shader->directory.getWorkDirectory() + testFrameRateShader->m_FragmentFilePath);
		std::copy(basicVertexShaderText.begin(), basicVertexShaderText.end(), const_cast<char*>(basicVertexText));
		std::copy(basicFragmentShaderText.begin(), basicFragmentShaderText.end(), const_cast<char*>(basicFragmentText));
		std::copy(testVertexShaderText.begin(), testVertexShaderText.end(), const_cast<char*>(testVertexText));
		std::copy(testFragmentShaderText.begin(), testFragmentShaderText.end(), const_cast<char*>(testfragmentText));
		std::copy(frameRateVertexShaderText.begin(), frameRateVertexShaderText.end(), const_cast<char*>(frameRateVertexText));
		std::copy(frameRateFragmentShaderText.begin(), frameRateFragmentShaderText.end(), const_cast<char*>(frameRatefragmentText));
		
		doOnce = false;
	}


	ImVec2 size = ImGui::GetWindowSize();
	ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable;
	static bool opened[4] = { true, true, true, true };

	ImGui::Begin("Text Editor", &editorClicked, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Files"))
		{
			ImGui::MenuItem("File Options", nullptr, false, false);
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("Options"))
		{
			ImGui::MenuItem("Editor Options", nullptr, false, false);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Test"))
		{
			ImGui::MenuItem("Test Options", nullptr, false, false);
			if (ImGui::MenuItem("Reopen all test files"))
			{
				opened[0] = true;
				opened[1] = true;
				opened[2] = true;
				opened[3] = true;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (ImGui::BeginTabBar("Files", tab_bar_flags))
	{
		if (ImGui::BeginTabItem("basic.vert", &opened[0]))
		{
			ImGui::InputTextMultiline("##basic.vertex", basicVertexText, IM_ARRAYSIZE(basicVertexText), ImVec2(-FLT_MIN, ImGui::GetFrameHeight() - ImGui::GetFrameHeightWithSpacing()), flags);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("basic.frag", &opened[1]))
		{
			ImGui::InputTextMultiline("##basic.fragment", basicFragmentText, IM_ARRAYSIZE(basicFragmentText), ImVec2(-FLT_MIN, ImGui::GetFrameHeight() - ImGui::GetFrameHeightWithSpacing()), flags);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("test.vert", &opened[2]))
		{
			ImGui::InputTextMultiline("##test.vertex", testVertexText, IM_ARRAYSIZE(testVertexText), ImVec2(-FLT_MIN, ImGui::GetFrameHeight() - ImGui::GetFrameHeightWithSpacing()), flags);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("test.frag", &opened[3]))
		{
			ImGui::InputTextMultiline("##test.fragment", testfragmentText, IM_ARRAYSIZE(testfragmentText), ImVec2(-FLT_MIN, ImGui::GetFrameHeight() - ImGui::GetFrameHeightWithSpacing()), flags);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("framerate.vert", &opened[2]))
		{
			ImGui::InputTextMultiline("##framerate.vertex", frameRateVertexText, IM_ARRAYSIZE(frameRateVertexText), ImVec2(-FLT_MIN, ImGui::GetFrameHeight() - ImGui::GetFrameHeightWithSpacing()), flags);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("framerate.frag", &opened[3]))
		{
			ImGui::InputTextMultiline("##framerate.fragment", frameRatefragmentText, IM_ARRAYSIZE(frameRatefragmentText), ImVec2(-FLT_MIN, ImGui::GetFrameHeight() - ImGui::GetFrameHeightWithSpacing()), flags);
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
}

void CoreGUI::renderFPS()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	const float PAD = 10.0f;
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
	ImVec2 work_size = viewport->WorkSize;
	ImVec2 window_pos;
	window_pos.x = work_pos.x + PAD;
	window_pos.y = work_pos.y + PAD;
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
	window_flags |= ImGuiWindowFlags_NoMove;
	ImGui::SetNextWindowSize(ImVec2(270.f, 50.f));
	ImGui::SetNextWindowBgAlpha(0.45f); // Transparent background

	if (ImGui::Begin("NixEngineOverlay", &shouldShowOverlay, window_flags))
	{
		ImGui::Text("Application average %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
		if (ImGui::BeginPopupContextWindow())
		{
			if (shouldShowOverlay && ImGui::MenuItem("Hide Overlay")) shouldShowOverlay = false;
			ImGui::EndPopup();
		}
	}
	ImGui::End();
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
			shouldRenderExit = false;
			callEscClicked();
			ImGui::CloseCurrentPopup();
		}
	}

	ImGui::EndPopup();
}

