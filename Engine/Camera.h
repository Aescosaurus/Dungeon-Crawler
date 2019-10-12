#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include "Rect.h"

class Camera
{
public:
	Camera( Graphics& gfx );

	// Render rect using absolute coordinates.
	void RenderRect( const Vec2& pos,Color c ) const;
	// Render rect using screen coordinates.
	void RenderRectRelative( const Vec2& pos,Color c ) const;

	void CenterOn( const Vec2& pos );

	const Rect& GetViewArea() const;
public:
	static constexpr int tileSize = 60;
private:
	static constexpr int width = Graphics::ScreenWidth / tileSize - 3;
	static constexpr int height = Graphics::ScreenHeight / tileSize;
	Rect viewArea = { 0.0f,float( width ),0.0f,float( height ) };
	Graphics& gfx;
};