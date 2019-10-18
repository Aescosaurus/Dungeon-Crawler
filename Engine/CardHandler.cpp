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
			kbd.KeyIsPressed( char( ( i + 1 ) + '0' ) ) )
		{
			selectedCard = i;
		}
	}

	if( selectedCard != -1 )
	{
		selectedSquare = mouse.GetPos() / Camera::tileSize;

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

	mousePos = mouse.GetPos();
}

void CardHandler::Draw( const Camera& cam,Graphics& gfx ) const
{
	// for( const auto& slot : cardSlots )
	for( int i = 0; i < int( cardSlots.size() ); ++i )
	{
		const auto& slot = cardSlots[i];

		if( selectedCard != i )
		{
			gfx.DrawRectDim( slot.area,
				slot.hovering
				? Colors::White1
				: Colors::LightGray1 );
		}
		else
		{
			gfx.DrawRectDim( slot.area,
				Colors::Gray1 );
		}
	}

	if( selectedCard != -1 )
	{
		// cam.RenderRect( cam.RelativeToAbsolute(
		// 	Vec2( mousePos ) ),Colors::White1 );

		const auto& curCard = cardSlots[selectedCard];

		// gfx.DrawRectDim( curCard.area.GetMovedBy( mousePos ),
		// 	Colors::White1 );
		const int width = curCard.area.GetWidth();
		const int height = curCard.area.GetHeight();
		gfx.DrawRectSafe( mousePos.x - width / 2,
			mousePos.y - height / 2,
			width,height,
			Colors::White1 );
	}
}

bool CardHandler::PlaySelectedCard( float dt )
{
	playTime.Update( dt );

	if( playTime.IsDone() )
	{
		// selectedCard = -1;
		doneWithTurn = false;
	}

	return( playTime.IsDone() );
}

void CardHandler::EndTurn()
{
	// Deal damage to enemy.

	selectedCard = -1;
}

bool CardHandler::HasSelectedCard() const
{
	return( selectedCard != -1 );
}

bool CardHandler::DoneWithTurn() const
{
	return( doneWithTurn );
}
