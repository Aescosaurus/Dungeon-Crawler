#pragma once

#include <vector>
#include "Rect.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Camera.h"
#include "Timer.h"
#include "Deck.h"
#include "MessageLog.h"

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

	void StartTurn( const Vec2& target,Dir::Direction dir );
	bool PlaySelectedCard( float dt );
	void EndTurn( Enemy* enemy,const Stats& stats,
		MessageLog& msgLog );
	void DeselectCard();

	bool HasSelectedCard() const;
	bool DoneWithTurn() const;
	const std::vector<std::unique_ptr<Card>>& GetCards() const;
private:
	static constexpr int nCards = 3;
	static constexpr int padding = 5;
	std::vector<CardSlot> cardSlots;
	Vei2 mousePos = { -1,-1 };
	int selectedCard = -1;
	// Timer playTime = Timer::turnTime;
	Vei2 selectedSquare = { -1,-1 };
	bool doneWithTurn = false;
	Deck deck;
	Animation* curCardAnim = nullptr;
	Vec2 cardAnimSpot = Vec2::Zero();
	Dir::Direction cardDir = Dir::Direction::Up;
};