#include "core/console.h"


DebugConsole::DebugConsole(std::string componentName, size_t inputBufferSize)
	:System(componentName, "Console"), m_console("Console")
{
	// Set input buffer size
	m_inputBuffer.resize(inputBufferSize);
}

void DebugConsole::run(bool* p_open)
{
	//m_console.Draw(p_open);

	if (!*p_open)
	{
		return;
	}

	ImGui::SetNextWindowSize(ImVec2(600, 400));
	ImGui::Begin(m_componentName.c_str(), p_open, ImGuiWindowFlags_MenuBar);

	//////////////
	//Log Window//
	//////////////

	const float footerHeightToReserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
	if (ImGui::BeginChild("ScrollRegion##", ImVec2(0, -footerHeightToReserve), false, 0))
	{
		//Wrap items
		ImGui::PushTextWrapPos();

		//Display items
		for (const auto& item : m_consoleSystem.Items())
		{
			ImGui::TextUnformatted(item.Get().data());
		}

		// Stop wrapping since we are done displaying console items.
		ImGui::PopTextWrapPos();

		// Loop through command string vector.
		ImGui::EndChild();
	}

	/////////////
	//Input Bar//
	/////////////

	ImGuiInputTextFlags inputTextFlags =
		ImGuiInputTextFlags_CallbackHistory | ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_CallbackCompletion |
		ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackAlways;


	// Input widget. (Width an always fixed width)
	ImGui::PushItemWidth(-ImGui::GetStyle().ItemSpacing.x * 7);

	ImGui::End();
}

void DebugConsole::draw(bool* p_open)
{
	m_console.Draw(p_open);
}

int DebugConsole::InputCallback(ImGuiInputTextCallbackData* data)
{
    return 0;
}
