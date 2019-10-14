#pragma once

#include <vector>
#include "Rect.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Camera.h"
#include "Timer.h"

class CardHandler
{
private:
	class CardSlot
	{
	public:
		RectI area;
		bool hovering;
	};
public:
	CardHandler( const RectI& cardArea );

	void Update( const Camera& cam,
		const Keyboard& kbd,Mouse& mouse );
	void Draw( const Camera& cam,Graphics& gfx ) const;

	bool PlaySelectedCard( float dt );

	bool HasSelectedCard() const;
	bool DoneWithTurn() const;
	Vei2 GetTarget() const;
private:
	static constexpr int nCards = 3;
	static constexpr int padding = 5;
	std::vector<CardSlot> cardSlots;
	Vei2 mousePos = { -1,-1 };
	int selectedCard = -1;
	Timer playTime = Timer::turnTime;
	Vei2 selectedSquare = { -1,-1 };
	bool doneWithTurn = false;
};