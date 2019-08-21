#pragma once

#include <algorithm>

class Timer
{
public:
	Timer( float time )
		:
		maxTime( time ),
		curTime( 0.0f )
	{}

	void Update( float dt )
	{
		if( curTime <= maxTime ) curTime += dt;
	}

	void Reset()
	{
		curTime = 0.0f;
	}

	bool IsDone() const
	{
		return( curTime >= maxTime );
	}
	float GetMaxTime() const
	{
		return( maxTime );
	}
	float GetPercent() const
	{
		return( std::min( 1.0f,curTime / maxTime ) );
	}
public:
	static constexpr float turnTime = 0.3f;
private:
	float maxTime;
	float curTime;
};