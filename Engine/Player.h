#pragma once

#include "Vec2.h"
#include "Camera.h"
#include "Keyboard.h"

class Player
{
public:
	Player( const Vec2& pos );

	void Update( const Keyboard& kbd );
	void Draw( const Camera& cam ) const;

	const Vec2& GetPos() const;
private:
	Vec2 pos;
};