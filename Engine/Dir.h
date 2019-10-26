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
};