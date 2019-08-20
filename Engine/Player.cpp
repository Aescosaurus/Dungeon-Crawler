#include "Player.h"

Player::Player( const Vec2& pos )
	:
	pos( pos )
{}

void Player::Update( const Keyboard& kbd )
{
	if( kbd.KeyIsPressed( 'W' ) ) --pos.y;
	if( kbd.KeyIsPressed( 'S' ) ) ++pos.y;
	if( kbd.KeyIsPressed( 'A' ) ) --pos.x;
	if( kbd.KeyIsPressed( 'D' ) ) ++pos.x;
}

void Player::Draw( const Camera& cam ) const
{
	cam.RenderRect( pos,Colors::Blue );
}

const Vec2& Player::GetPos() const
{
	return( pos );
}
