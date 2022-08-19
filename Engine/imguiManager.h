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
	}
	~imguiManager()
	{
		ImGui::DestroyContext();
	}
};