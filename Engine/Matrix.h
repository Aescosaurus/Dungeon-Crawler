#pragma once

#include <cmath>
#include "Vec2.h"
#include "ChiliUtils.h"

class Matrix
{
public:
	// Angle in radians.
	static constexpr Matrix Rotation( float angle )
	{
		return( Matrix{
			std::cos( angle ),-std::sin( angle ),
			std::sin( angle ),std::cos( angle ) } );
	}
	constexpr Vec2 operator*( const Vec2& rhs ) const
	{
		Vec2 start = Vec2::Zero();
		start.x = a00 * rhs.x + a01 * rhs.y;
		start.y = a10 * rhs.x + a11 * rhs.y;
		return( start );
	}
	static constexpr Matrix Up()
	{
		return( Rotation( 0.0f ) );
	}
	static constexpr Matrix Down()
	{
		return( Rotation( chili::pi ) );
	}
	static constexpr Matrix Left()
	{
		return( Rotation( chili::pi * 1.5f ) );
	}
	static constexpr Matrix Right()
	{
		return( Rotation( chili::pi / 2.0f ) );
	}
	constexpr bool operator==( const Matrix& rhs ) const
	{
		return( a00 == rhs.a00,
			a01 == rhs.a01,
			a10 == rhs.a10,
			a11 == rhs.a11 );
	}
private:
	constexpr Matrix( float a,float b,float c,float d )
		:
		a00( a ),
		a01( b ),
		a10( c ),
		a11( d )
	{}
private:
	static constexpr int size = 2;
	float a00;
	float a01;
	float a10;
	float a11;
};