#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include "Rect.h"
#include "Codex.h"
#include "Dir.h"

class Camera
{
public:
	Camera( Graphics& gfx );

	// Render rect using absolute coordinates.
	void RenderRect( const Vec2& pos,Color c ) const;
	void RenderImage( const Vec2& pos,CSurfPtr img,
		const RectI& area,
		Dir::Direction rotation = Dir::Direction::Up ) const;

	void CenterOn( const Vec2& pos );

	const Rect& GetViewArea() const;
	bool IsOnScreen( const Vei2& pos ) const;
	Vec2 RelativeToAbsolute( const Vec2& rel ) const;
	Vec2 AbsoluteToRelative( const Vec2& loc ) const;
public:
	static constexpr int tileSize = 60;
private:
	static constexpr int width = Graphics::ScreenWidth / tileSize - 3;
	static constexpr int height = Graphics::ScreenHeight / tileSize;
	Rect viewArea = { 0.0f,float( width ),0.0f,float( height ) };
	Graphics& gfx;
};