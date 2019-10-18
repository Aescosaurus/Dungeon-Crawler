#pragma once

#include <cmath>

template<typename T>
class Vec2_
{
public:
	constexpr Vec2_( T x,T y )
		:
		x( x ),
		y( y )
	{}
	template<typename U>
	constexpr operator Vec2_<U>() const
	{
		return( Vec2_<U>{ U( x ),U( y ) } );
	}
	constexpr Vec2_& operator+=( const Vec2_& rhs )
	{
		x += rhs.x;
		y += rhs.y;
		return( *this );
	}
	constexpr Vec2_ operator+( const Vec2_& rhs ) const
	{
		auto temp = *this;
		temp += rhs;
		return( temp );
	}
	constexpr Vec2_& operator-=( const Vec2_& rhs )
	{
		x -= rhs.x;
		y -= rhs.y;
		return( *this );
	}
	constexpr Vec2_ operator-( const Vec2_& rhs ) const
	{
		auto temp = *this;
		temp -= rhs;
		return( temp );
	}
	constexpr Vec2_& operator*=( T amount )
	{
		x *= amount;
		y *= amount;
		return( *this );
	}
	constexpr Vec2_ operator*( T amount ) const
	{
		auto temp = *this;
		temp *= amount;
		return( temp );
	}
	constexpr Vec2_& operator/=( T amount )
	{
		x /= amount;
		y /= amount;
		return( *this );
	}
	constexpr Vec2_ operator/( T amount ) const
	{
		auto temp = *this;
		temp /= amount;
		return( temp );
	}
	constexpr bool operator==( const Vec2_& rhs ) const
	{
		return( x == rhs.x && y == rhs.y );
	}
	constexpr bool operator!=( const Vec2_& rhs ) const
	{
		return( !( *this == rhs ) );
	}
	constexpr Vec2_ operator-() const
	{
		return( Vec2_<T>{ -x,-y } );
	}
	constexpr T GetLengthSq() const
	{
		return( x * x + y * y );
	}
	constexpr T GetLength() const
	{
		return( T( std::sqrt( GetLengthSq() ) ) );
	}
	constexpr Vec2_ GetNormalized() const
	{
		const auto len = GetLength();
		return( *this / len );
	}
	constexpr Vec2_ X() const
	{
		return( Vec2_<T>{ x,T( 0.0 ) } );
	}
	constexpr Vec2_ Y() const
	{
		return( Vec2_<T>{ T( 0.0 ),y } );
	}
	static constexpr Vec2_ Up()
	{
		return( Vec2_<T>{ T( 0.0 ),T( -1.0 ) } );
	}
	static constexpr Vec2_ Down()
	{
		return( Vec2_<T>{ T( 0.0 ),T( 1.0 ) } );
	}
	static constexpr Vec2_ Left()
	{
		return( Vec2_<T>{ T( -1.0 ),T( 0.0 ) } );
	}
	static constexpr Vec2_ Right()
	{
		return( Vec2_<T>{ T( 1.0 ),T( 0.0 ) } );
	}
public:
	T x;
	T y;
};

typedef Vec2_<float> Vec2;
typedef Vec2_<int> Vei2;