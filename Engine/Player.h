#pragma once

#include "Vec2.h"
#include "Camera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "TileMap.h"
#include "Timer.h"

class Player
{
public:
	Player( const Vec2& pos,const TileMap& tilemap,
		Camera& cam );

	bool StartTurn( const Keyboard& kbd,const Mouse& mouse );
	bool UpdateTurn( const Mouse& mouse,float dt );
	bool EndTurn();
	void Draw( const Camera& cam ) const;

	const Vec2& GetPos() const;
private:
	const TileMap& tilemap;
	Camera& cam;
	Vec2 pos;
	Vei2 move = { 0,0 };
	Vei2 target = { 0,0 };
	Timer moveTimer = Timer::turnTime;
};