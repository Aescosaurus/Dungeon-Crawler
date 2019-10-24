#pragma once

#include "Enemy.h"
#include "Random.h"

class Rat
	:
	public Enemy
{
public:
	Rat( const Vec2& pos )
		:
		Enemy( pos,Colors::Blue5 )
	{}

	bool StartTurn( EnemyUpdateInfo& info ) override
	{
		Vei2 move = Vei2::Zero();
		do
		{
			move = Vei2::Zero();
			if( int( Random{ 0,10 } ) < 5 )
			{
				if( int( Random{ 0,10 } ) < 5 ) move.x = 1;
				else move.x = -1;
			}
			else
			{
				if( int( Random{ 0,10 } ) < 5 ) move.y = 1;
				else move.y = -1;
			}
		}
		while( info.tilemap.GetTile( Vei2( pos + move ) ) ==
			TileMap::TileType::Wall );
		action = TurnType::Move;
		Enemy::Move( move );
		return( true );
	}
private:
};