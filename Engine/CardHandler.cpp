#include "CardHandler.h"

CardHandler::CardHandler( const RectI& cardArea)
{
	const auto width = cardArea.GetWidth();
	const auto height = cardArea.GetHeight() / 3;

	cardSlots.reserve( nCards );
	for( int i = 0; i < nCards; ++i )
	{
		cardSlots.emplace_back( RectI{
			Vei2{ cardArea.left + padding / 2,
			cardArea.top + i * height + padding / 2 },
			width - padding,height - padding } );
	}
}

void CardHandler::Update( const Keyboard& kbd,const Mouse& mouse )
{
}

void CardHandler::Draw( Graphics& gfx ) const
{
	for( const auto& slot : cardSlots )
	{
		gfx.DrawRectDim( slot,Colors::LightGray );
	}
}
