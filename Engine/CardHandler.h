#pragma once

#include <vector>
#include "Rect.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class CardHandler
{
public:
	CardHandler( const RectI& cardArea );

	void Update( const Keyboard& kbd,const Mouse& mouse );
	void Draw( Graphics& gfx ) const;
private:
	static constexpr int nCards = 3;
	static constexpr int padding = 5;
	std::vector<RectI> cardSlots;
};