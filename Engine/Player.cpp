#include "Player.h"

Player::Player( const Vec2& pos,const TileMap& tilemap,
	Camera& cam )
	:
	pos( pos ),
	tilemap( tilemap ),
	cam( cam )
{}

bool Player::StartTurn( const Keyboard& kbd,const Mouse& mouse )
{
	move = { 0,0 };
	if( kbd.KeyIsPressed( 'W' ) ) --move.y;
	else if( kbd.KeyIsPressed( 'S' ) ) ++move.y;
	else if( kbd.KeyIsPressed( 'A' ) ) --move.x;
	else if( kbd.KeyIsPressed( 'D' ) ) ++move.x;

	if( ( move.x != 0 || move.y != 0 ) &&
		tilemap.GetTile( int( pos.x ) + move.x,
		int( pos.y ) + move.y ) ==
		TileMap::TileType::Floor )
	{
		target = Vei2( pos ) + move;
		return( true );
	}
	else
	{
		return( false );
	}
}

bool Player::UpdateTurn( const Mouse& mouse,float dt )
{
	pos += Vec2( move ) / moveTimer.GetMaxTime() * dt;
	cam.CenterOn( pos );

	moveTimer.Update( dt );
	if( moveTimer.IsDone() )
	{
		moveTimer.Reset();
		return( true );
	}
	else
	{
		return( false );
	}
}

bool Player::EndTurn()
{
	pos = target;
	cam.CenterOn( pos );
	move = { 0,0 };
	return( true );
}

void Player::Draw( const Camera& cam ) const
{
	cam.RenderRect( pos,Colors::Blue );
}

const Vec2& Player::GetPos() const
{
	return( pos );
}
