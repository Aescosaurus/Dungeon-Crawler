/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

#include "Camera.h"
#include "TileMap.h"
#include "Player.h"
#include "FrameTimer.h"
#include "SideMenu.h"
#include "HitNumber.h"

#include "Rat.h"

class Game
{
private:
	enum class State
	{
		PlayerStart,
		PlayerTurn,
		PlayerEnd,
		EnemyStart,
		EnemyTurn,
		EnemyEnd
	};
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Camera cam;
	TileMap tilemap;
	SideMenu menu;
	Player player;
	State gameState = State::PlayerStart;
	FrameTimer ft;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Enemy>>::iterator curEnemy;
	std::vector<HitNumber> hitNums;
	/********************************/
};