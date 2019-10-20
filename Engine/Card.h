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

	void Discard();
	void Reset();

	bool IsDiscarded() const;
protected:
	// Name: Name of the card.
	// Damage: Damage, as percent of attack (0=0%,100=100%).
	// Range: Range, in tiles.
	// Type: What type of card is it.
	// ImgSrc: Path to icon.
	Card( const std::string& name,int damage,int range,
		Type type,const std::string& imgSrc );
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
	CSurfPtr img;
	bool discarded = false;
};