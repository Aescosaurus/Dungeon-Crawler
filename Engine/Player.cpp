#include "Player.h"

Player::Player( const Vec2& pos,const TileMap& tilemap,
	Camera& cam )
	:
	pos( pos ),
	tilemap( tilemap ),
	cam( cam )
{}

void Player::Update( const Keyboard& kbd )
{
	if( kbd.KeyIsPressed( 'W' ) ) --pos.y;
	if( kbd.KeyIsPressed( 'S' ) ) ++pos.y;
	if( kbd.KeyIsPressed( 'A' ) ) --pos.x;
	if( kbd.KeyIsPressed( 'D' ) ) ++pos.x;
}

bool Player::StartTurn( const Keyboard& kbd )
{
	move = { 0,0 };
	if( kbd.KeyIsPressed( 'W' ) ) --move.y;
	else if( kbd.KeyIsPressed( 'S' ) ) ++move.y;
	else if( kbd.KeyIsPressed( 'A' ) ) --move.x;
	else if( kbd.KeyIsPressed( 'D' ) ) ++move.x;

	if( move.x != 0 || move.y != 0 )
	{
		target = Vei2( pos ) + move;
		return( true );
	}
	else
	{
		return( false );
	}
}

bool Player::UpdateTurn( float dt )
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
