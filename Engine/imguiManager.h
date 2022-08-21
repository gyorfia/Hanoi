#pragma once
#include "imgui/imgui.h"



class imguiManager
{
public:
	imguiManager()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle* style = &ImGui::GetStyle();
		style->ScaleAllSizes(1.0f);
		style->WindowPadding = ImVec2(15, 10);
		style->WindowRounding = 6.0f;
		style->FramePadding = ImVec2(5, 5);
		style->FrameRounding = 4.0f;
		style->ItemSpacing = ImVec2(4, 4);
		style->ItemInnerSpacing = ImVec2(8, 6);
		style->IndentSpacing = 25.0f;
		style->ScrollbarSize = 15.0f;
		style->ScrollbarRounding = 9.0f;
		style->GrabMinSize = 14.0f;
		style->GrabRounding = 3.0f;
		style->TabRounding = 4.0f;
	}
	~imguiManager()
	{
		ImGui::DestroyContext();
	}
};