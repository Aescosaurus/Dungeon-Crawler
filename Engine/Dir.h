#pragma once

#include "Vec2.h"
#include <cassert>

class Dir
{
public:
	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};
public:
	static Direction Vec2Dir( const Vei2& dir )
	{
		assert( dir.x == 0 || dir.y == 0 );

		if( dir.y < 0 ) return( Direction::Up );
		if( dir.y > 0 ) return( Direction::Down );
		if( dir.x < 0 ) return( Direction::Left );
		if( dir.x > 0 ) return( Direction::Right );

		assert( false );
		return( Direction::Up );
	}
	static Vei2 Dir2Vec( Direction d )
	{
		switch( d )
		{
		case Direction::Up:
			return( Vei2::Up() );
		case Direction::Down:
			return( Vei2::Down() );
		case Direction::Left:
			return( Vei2::Left() );
		case Direction::Right:
			return( Vei2::Right() );
		default:
			assert( false );
			return( Vei2::Zero() );
		}
	}
};