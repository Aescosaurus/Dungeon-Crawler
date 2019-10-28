#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include <string>
#include "Timer.h"

class HitNumber
{
public:
	HitNumber( const Vec2& pos,int number )
		:
		pos( pos ),
		text( std::to_string( number ) )
	{}

	void Update( float dt )
	{
		pos += vel * dt;

		fadeTimer.Update( dt );
	}
	void Draw( Graphics& gfx ) const
	{

	}

	bool IsDone() const
	{
		return( fadeTimer.IsDone() );
	}
private:
	static constexpr Vec2 vel = { 0.0f,-0.1f };
	Vec2 pos;
	std::string text;
	Timer fadeTimer = 0.2f;
};