#pragma once

#include <vector>
#include <memory>
#include "Card.h"

#include "BasicStrike.h"

class Deck
{
public:
	Deck( int nCards )
		:
		nCards( nCards )
	{
		for( int i = 0; i < nCards; ++i )
		{
			hand.emplace_back( i );
		}

		for( int i = 0; i < 3; ++i )
		{
			AddCard( new BasicStrike );
		}
	}

	// Pass a new card, we take ownership.
	void AddCard( Card* c )
	{
		cards.emplace_back( c );
	}

	const Card& GetCard( int slot ) const
	{
		assert( slot < nCards );

		return( *cards[hand[slot]] );
	}
private:
	std::vector<std::unique_ptr<Card>> cards;
	std::vector<int> hand;
	int nCards;
};