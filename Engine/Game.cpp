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
#include <functional>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	cam( gfx ),
	menu( cam ),
	player( tilemap.GetRandFloorPos(),tilemap,cam,menu )
{
	cam.CenterOn( player.GetPos() );

	enemies.emplace_back( std::make_unique<Rat>(
		player.GetPos() + Vec2::Right() * 2 ) );
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const auto dt = ft.Mark();

	for( auto& num : hitNums ) num.Update( dt );
	chili::remove_erase_if( hitNums,std::mem_fn( &HitNumber::IsDone ) );
	switch( gameState )
	{
	case State::PlayerStart:
		if( player.StartTurn( wnd.kbd,wnd.mouse,enemies ) )
		{
			gameState = State::PlayerTurn;
		}
		break;
	case State::PlayerTurn:
		if( player.UpdateTurn( wnd.mouse,dt ) )
		{
			gameState = State::PlayerEnd;
		}
		break;
	case State::PlayerEnd:
		if( player.EndTurn( enemies,hitNums ) )
		{
			chili::remove_erase_if( enemies,
				std::mem_fn( &Enemy::IsExpl ) );
			gameState = State::EnemyStart;
			curEnemy = enemies.begin();
			if( curEnemy == enemies.end() )
			{
				gameState = State::PlayerStart;
			}
		}
		break;
	case State::EnemyStart:
	{
		EnemyUpdateInfo euInfo{ tilemap,player.GetPos(),
			enemies,dt };
		if( ( *curEnemy )->StartTurn( euInfo ) )
		{
			gameState = State::EnemyTurn;
		}
	}
	break;
	case State::EnemyTurn:
		if( ( *curEnemy )->UpdateTurn( dt ) )
		{
			gameState = State::EnemyEnd;
		}
		break;
	case State::EnemyEnd:
		( *curEnemy )->EndTurn();

		++curEnemy;
		if( curEnemy == enemies.end() )
		{
			gameState = State::PlayerStart;
		}
		else
		{
			gameState = State::EnemyStart;
		}
	}
}

void Game::ComposeFrame()
{
	tilemap.Draw( cam );
	for( const auto& e : enemies ) e->Draw( cam );
	player.Draw( cam );
	for( const auto& num : hitNums ) num.Draw( gfx );

	menu.Draw( cam,gfx );
}
