#pragma once

#include "Surface.h"
#include "Camera.h"

class Animation
{
public:
	Animation( int x,int y,int width,int height,int count,
		const Surface& sheet,float holdTime = 0.2f )
		:
		sheet( &sheet ),
		holdTime( holdTime )
	{
		for( int i = 0; i < count; ++i )
		{
			frames.emplace_back( x + i * width,
				x + ( i + 1 ) * width,y,y + height );
		}
	}

	void Update( float dt )
	{
		curFrameTime += dt;
		while( curFrameTime >= holdTime )
		{
			++curFrame;
			if( curFrame >= int( frames.size() ) )
			{
				// curFrame = 0;
				--curFrame;
				finished = true;
			}

			curFrameTime -= holdTime;
		}
	}
	void Draw( const Vec2& pos,const Camera& cam ) const
	{
		// gfx.DrawSprite( pos.x,pos.y,frames[curFrame],
		// 	*sheet,centered,eff );
		cam.RenderImage( pos,sheet,frames[curFrame] );
	}

	void Reset()
	{
		curFrameTime = 0.0f;
		curFrame = 0;
		finished = false;
	}

	bool IsDone() const
	{
		return( finished );
	}
private:
	const Surface* sheet;
	float holdTime;
	std::vector<RectI> frames;
	float curFrameTime = 0.0f;
	int curFrame = 0;
	bool finished = false;
};