/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	pHanoi( new Hanoi{8, Hanoi::Mode::normHanoi} ),
	backg(Colors::White)
{}

void Game::Go()
{
	gfx.BeginFrame();
	wnd.ImGuiNewFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	// IMGUI BEGIN
	/*static bool demo = true;
	if (demo)
		ImGui::ShowDemoWindow(&demo);*/
	ImGui::Begin("Hanoi control panel");
	ImGui::SetWindowFontScale(1.8f);
	// Combo
	if (ImGui::Combo("Mode", &PM.comboMode, "Normal_Hanoi\0Double_Hanoi\0Merge_Hanoi\0Split_Hanoi\0Base_Swap_Hanoi\0Easy_Bicolor_Hanoi\0Bicolor_Hanoi\0"))
		PM.newParams = true;
	// Number of Disks
	if ((Hanoi::Mode)PM.comboMode == Hanoi::Mode::normHanoi)
	{
		if (ImGui::InputInt("Disks", &PM.nDisksNormal, 1, 50))
			PM.newParams = true;
	}
	else
	{
		if (ImGui::InputInt("Disks", &PM.nDisksBiC, 2, 50))
			PM.newParams = true;
	}
	// Progress Bar
	double progress = ((double)pHanoi->GetCS() + 1)/ ((double)pHanoi->GetMaxStep() + 1);
	char buf[32];
	sprintf_s(buf, "%d/%d", (int)(pHanoi->GetCS()) + 1, pHanoi->GetMaxStep() + 1);
	ImGui::ProgressBar(progress, ImVec2(0.0f, 0.f), buf);
	ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
	ImGui::Text("Progress");
	// FPS
	ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
	ImGui::End();

	// IMGUI END

	if (wnd.kbd.KeyIsPressed(VK_RIGHT) && timer.GetTimeSinceLastRefresh() > 0.3f && pHanoi->GetCS() < pHanoi->GetMaxStep())
	{
		pHanoi->ChangeCurrentStep(1);
		pHanoi->LoadStep();
		timer.ResetClock();
	}
	else if (wnd.kbd.KeyIsPressed(VK_LEFT) && timer.GetTimeSinceLastRefresh() > 0.3f && pHanoi->GetCS() > -1)
	{
		pHanoi->ChangeCurrentStep(-1);
		pHanoi->LoadStep();
		timer.ResetClock();
	}
	if (PM.newParams)
	{
		PM.ClampValues();
		if ((Hanoi::Mode)PM.comboMode == Hanoi::Mode::normHanoi)
		{
			pHanoi = std::make_unique<Hanoi>(PM.nDisksNormal, (Hanoi::Mode)PM.comboMode);
		}
		else
		{
			pHanoi = std::make_unique<Hanoi>(PM.nDisksBiC, (Hanoi::Mode)PM.comboMode);
		}
		PM.newParams = false;
	}
}

void Game::ComposeFrame()
{
	backg.Draw(gfx);
	pHanoi->Draw(gfx);
}