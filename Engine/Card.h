#pragma once

#include <string>
#include "Graphics.h"
#include "Codex.h"

class Card
{
public:
	enum class Type
	{
		Typeless,
		Fire,
		Poison,
		Ice,
		Ghost
	};
public:
	void Draw( const RectI& area,Graphics& gfx ) const;
protected:
	Card( const std::string& name,int damage,int range,
		Type type );
private:
	Color Type2Color( Type t );
private:
	static constexpr int padding = 5;
	CFontPtr unluckyPixel = FontCodex::Fetch( "Fonts/UnluckyPixel.bmp" );
	std::string name;
	int damage;
	int range;
	Type type;
	Color textCol;
};