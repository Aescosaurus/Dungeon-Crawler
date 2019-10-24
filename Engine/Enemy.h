#pragma once

#include "Vec2.h"
#include "Camera.h"
#include "TileMap.h"
#include "Timer.h"

class EnemyUpdateInfo
{
public:
	TileMap& tilemap;
	float dt;
};

class Enemy
{
protected:
	enum class TurnType
	{
		None,
		Move,
		Attack
	};
public:
	Enemy( const Vec2& pos,Color c );

	virtual bool StartTurn( EnemyUpdateInfo& info ) = 0;
	bool UpdateTurn( float dt );
	bool EndTurn();
	void Draw( const Camera& cam ) const;
protected:
	void Move( const Vei2& dir );
protected:
	TurnType action = TurnType::None;
	Vec2 pos;
private:
	Color c;
	Vei2 target = Vei2::Zero();
	Vei2 move = Vei2::Zero();
	Timer moveTimer = Timer::turnTime;
};