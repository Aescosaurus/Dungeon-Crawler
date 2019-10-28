#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include <string>
#include "Timer.h"
#include "Codex.h"

class HitNumber
{
public:
	HitNumber( const Vec2& pos,int number )
		:
		pos( pos ),
		text( "-" + std::to_string( number ) )
	{}

	void Update( float dt )
	{
		pos += vel * dt;

		fadeTimer.Update( dt );
	}
	void Draw( Graphics& gfx ) const
	{
		unluckyPixel->DrawText( text,Vei2( pos ),
			Colors::Black1,gfx,true );
	}

	bool IsDone() const
	{
		return( fadeTimer.IsDone() );
	}
private:
	static constexpr Vec2 vel = { 0.0f,-12.5f };
	CFontPtr unluckyPixel = FontCodex::Fetch( "Fonts/UnluckyPixel.bmp" );
	Vec2 pos;
	std::string text;
	Timer fadeTimer = 0.5f;
};