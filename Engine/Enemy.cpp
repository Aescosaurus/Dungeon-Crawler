#include "Enemy.h"

Enemy::Enemy( const Vec2& pos,Color c )
	:
	pos( pos ),
	c( c )
{}

bool Enemy::UpdateTurn( float dt )
{
	switch( action )
	{
	case TurnType::None:
		return( true );
	case TurnType::Move:
		pos += Vec2( move ) / moveTimer.GetMaxTime() * dt;

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
	case TurnType::Attack:
		return( true );
	default:
		assert( false );
		return( false );
	}
}

bool Enemy::EndTurn()
{
	switch( action )
	{
	case TurnType::None:
		return( true );
	case TurnType::Move:
		pos = target;
		move = { 0,0 };
		return( true );
	case TurnType::Attack:
		return( true );
	default:
		assert( false );
		return( false );
	}
}

void Enemy::Draw( const Camera& cam ) const
{
	cam.RenderRect( pos,c );
}

void Enemy::Move( const Vei2& dir )
{
	assert( dir.x == 0 || dir.y == 0 );
	target = Vei2( pos ) + dir;
	move = dir;
}
