#include "CardHandler.h"

CardHandler::CardHandler( const RectI& cardArea)
{
	const auto width = cardArea.GetWidth();
	const auto height = cardArea.GetHeight() / 3;

	cardSlots.reserve( nCards );
	for( int i = 0; i < nCards; ++i )
	{
		CardSlot temp;
		temp.area = RectI{ Vei2{ cardArea.left + padding / 2,
			cardArea.top + i * height + padding / 2 },
			width - padding,height - padding };
		temp.hovering = false;
		cardSlots.emplace_back( temp );
	}
}

void CardHandler::Update( const Keyboard& kbd,const Mouse& mouse )
{
	for( int i = 0; i < nCards; ++i )
	{
		auto& curCard = cardSlots[i];

		curCard.hovering = curCard.area.ContainsPoint( mouse.GetPos() );

		if( ( curCard.hovering && mouse.LeftIsPressed() ) ||
			kbd.KeyIsPressed( i ) )
		{
			selectedCard = i;
		}
	}

	if( selectedCard != -1 )
	{
		mousePos = mouse.GetPos() / Camera::tileSize;

		if( mouse.LeftIsPressed() )
		{
			// if card works at this spot
			//  donewithturn = true
		}
	}

	playTime.Reset();
}

void CardHandler::Draw( const Camera& cam,Graphics& gfx ) const
{
	for( const auto& slot : cardSlots )
	{
		gfx.DrawRectDim( slot.area,slot.hovering
			? Colors::White
			: Colors::LightGray );
	}

	if( selectedCard != -1 )
	{
		cam.RenderRectRelative( Vec2( mousePos ),Colors::White );
	}
}

bool CardHandler::PlaySelectedCard( float dt )
{
	playTime.Update( dt );

	return( playTime.IsDone() );
}

bool CardHandler::HasSelectedCard() const
{
	return( selectedCard != -1 );
}

Vei2 CardHandler::GetTarget() const
{
	return( mousePos );
}
