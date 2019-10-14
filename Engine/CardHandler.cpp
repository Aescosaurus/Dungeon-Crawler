#include "CardHandler.h"

CardHandler::CardHandler( const RectI& cardArea )
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

void CardHandler::Update( const Camera& cam,
	const Keyboard& kbd,Mouse& mouse )
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

		selectedSquare = mousePos;

		bool released = false;
		while( !mouse.IsEmpty() )
		{
			if( mouse.Read().GetType() == Mouse::Event::Type::LRelease )
			{
				released = true;
			}
		}

		if( cam.IsOnScreen( selectedSquare ) &&
			// !mouse.LeftIsPressed() &&
			released &&
			selectedSquare != Vei2{ -1,-1 } )
		{
			doneWithTurn = true;
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
		cam.RenderRect( cam.RelativeToAbsolute(
			Vec2( mousePos ) ),Colors::White );
	}
}

bool CardHandler::PlaySelectedCard( float dt )
{
	playTime.Update( dt );

	if( playTime.IsDone() )
	{
		selectedCard = -1;
		doneWithTurn = false;
	}

	return( playTime.IsDone() );
}

bool CardHandler::HasSelectedCard() const
{
	return( selectedCard != -1 );
}

bool CardHandler::DoneWithTurn() const
{
	return( doneWithTurn );
}

Vei2 CardHandler::GetTarget() const
{
	return( mousePos );
}
