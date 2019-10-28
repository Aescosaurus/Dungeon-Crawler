#pragma once

#include "Vec2.h"
#include "Camera.h"
#include "TileMap.h"
#include "Timer.h"
#include <memory>

class Enemy;

class EnemyUpdateInfo
{
public:
	const TileMap& tilemap;
	const Vec2& playerPos;
	const std::vector<std::unique_ptr<Enemy>>& enemies;
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
	virtual bool StartTurn( EnemyUpdateInfo& info ) = 0;
	bool UpdateTurn( float dt );
	bool EndTurn();
	void Draw( const Camera& cam ) const;

	int Attack( int damage );

	const Vec2& GetPos() const;
	bool IsExpl() const;
protected:
	Enemy( const Vec2& pos,Color c,int health );

	bool Move( const Vei2& dir,EnemyUpdateInfo& info );
protected:
	TurnType action = TurnType::None;
	Vec2 pos;
private:
	Color c;
	int health;
	Vei2 target = Vei2::Zero();
	Vei2 move = Vei2::Zero();
	Timer moveTimer = Timer::turnTime;
};