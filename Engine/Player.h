#pragma once

#include "Vec2.h"
#include "Camera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "TileMap.h"
#include "Timer.h"
#include "SideMenu.h"
#include "Stats.h"
#include "Codex.h"
#include "Dir.h"
#include "Animation.h"

class Player
{
private:
	enum class TurnType
	{
		None,
		Movement,
		Attack
	};
public:
	Player( const Vec2& pos,const TileMap& tilemap,
		Camera& cam,SideMenu& menu );

	bool StartTurn( const Keyboard& kbd,Mouse& mouse,
		const std::vector<std::unique_ptr<class Enemy>>& enemies );
	bool UpdateTurn( const Mouse& mouse,float dt );
	bool EndTurn( std::vector<std::unique_ptr<class Enemy>>& enemies,
		std::vector<HitNumber>& hitNums );
	void Draw( const Camera& cam ) const;

	const Vec2& GetPos() const;
private:
	const TileMap& tilemap;
	Camera& cam;
	SideMenu& menu;
	CardHandler& cardHandler;
	MessageLog& msgLog;
	Vec2 pos;
	Vei2 move = { 0,0 };
	Vei2 target = { 0,0 };
	Timer moveTimer = Timer::turnTime;
	TurnType turn = TurnType::None;
	Stats stats;
	CSurfPtr sprSheet = SurfCodex::Fetch( "Images/Player.bmp" );
	// std::vector<RectI> frames;
	// Animation lookAnim;
	std::vector<Animation> anims;
	static constexpr int frameOrder[] = { 0,1,0,2 };
	int curAnimFrame = 0;
	Dir::Direction lookDir = Dir::Direction::Up;
};