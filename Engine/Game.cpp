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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	hanoi(gfx, 8, Hanoi::Mode::normHanoi ),
	backg(Colors::White)
{}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_RIGHT) && timer.GetTimeSinceLastRefresh() > 0.3f && hanoi.GetCS() < hanoi.GetMaxStep())
	{
		hanoi.ChangeCurrentStep(1);
		hanoi.LoadStep();
		timer.ResetClock();
	}
	else if (wnd.kbd.KeyIsPressed(VK_LEFT) && timer.GetTimeSinceLastRefresh() > 0.3f && hanoi.GetCS() > -1)
	{
		hanoi.ChangeCurrentStep(-1);
		hanoi.LoadStep();
		timer.ResetClock();
	}
}

void Game::ComposeFrame()
{
	backg.Draw(gfx);
	hanoi.Draw(gfx);
}