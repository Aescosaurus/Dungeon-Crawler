#pragma once

#include "Vec2.h"
#include "Random.h"

template<typename T>
class Rect_
{
public:
	constexpr Rect_() = default;
	constexpr Rect_( T left,T right,T top,T bottom )
		:
		left( left ),
		right( right ),
		top( top ),
		bottom( bottom )
	{}
	constexpr Rect_( const Vec2_<T>& topLeft,const Vec2_<T>& bottomRight )
		:
		Rect_( topLeft.x,bottomRight.x,topLeft.y,bottomRight.y )
	{}
	constexpr Rect_( const Vec2_<T>& topLeft,T width,T height )
		:
		Rect_( topLeft,topLeft + Vec2_<T>( width,height ) )
	{}

	template<typename U>
	constexpr operator Rect_<U>() const
	{
		return Rect_<U>( U( left ),U( right ),U( top ),U( bottom ) );
	}

	constexpr void MoveTo( const Vec2_<T>& pos )
	{
		const auto size = GetSize();
		left = pos.x;
		right = pos.x + size.x;
		top = pos.y;
		bottom = pos.y + size.y;
	}
	constexpr void MoveBy( const Vec2_<T>& diff )
	{
		left += diff.x;
		right += diff.x;
		top += diff.y;
		bottom += diff.y;
	}

	constexpr bool IsOverlappingWith( const Rect_& other ) const
	{
		return( right > other.left && left < other.right
			&& bottom > other.top && top < other.bottom );
	}
	constexpr bool IsContainedBy( const Rect_& other ) const
	{
		return( left >= other.left && right <= other.right &&
			top >= other.top && bottom <= other.bottom );
	}
	constexpr bool ContainsPoint( const Vec2_<T>& point ) const
	{
		return( point.x > left && point.x < right &&
			point.y > top && point.y < bottom );
	}
	constexpr bool OverlapsPoint( const Vec2_<T>& point ) const
	{
		return( point.x >= left && point.x <= right &&
			point.y >= top && point.y <= bottom );
	}
	// Returns random point within rect.
	constexpr Vei2 GetRandPoint() const
	{
		const auto randX = int( Random{ left,right - 1 } );
		const auto randY = int( Random{ top,bottom - 1 } );
		return( Vei2{ randX,randY } );
	}
	constexpr Rect_ GetExpandedBy( T amount ) const
	{
		return( Rect_<T>{ left - amount,right + amount,
			top - amount,bottom + amount } );
	}

	constexpr Vec2_<T> GetTopLeft() const
	{
		return( Vei2{ left,top } );
	}
	constexpr Vec2_<T> GetCenter() const
	{
		return Vec2_<T>( ( left + right ) / T( 2 ),( top + bottom ) / T( 2 ) );
	}
	constexpr T GetWidth() const
	{
		return( right - left );
	}
	constexpr T GetHeight() const
	{
		return( bottom - top );
	}
	constexpr Vec2_<T> GetSize() const
	{
		return( Vec2_<T>{ GetWidth(),GetHeight() } );
	}
public:
	T left;
	T right;
	T top;
	T bottom;
};

typedef Rect_<float> Rect;
typedef Rect_<int> RectI;