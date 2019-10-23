#pragma once

#include <vector>
#include <memory>
#include "Card.h"
#include <algorithm>

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

		for( int i = 0; i < 4; ++i )
		{
			AddCard( new BasicStrike );
		}
	}

	// Pass a new card, we take ownership.
	void AddCard( Card* c )
	{
		cards.emplace_back( c );
	}
	void Discard( int card )
	{
		assert( card >= 0 );
		assert( card < nCards );

		cards[hand[card]]->Discard();
		hand[card] = -1;
		for( int i = 0; i < int( cards.size() ); ++i )
		{
			if( !cards[i]->IsDiscarded() &&
				std::find( hand.begin(),hand.end(),i ) ==
				hand.end() )
			{
				hand[card] = i;
			}
			// for( int j = 0; j < int( hand.size() ); ++j )
			// {
			// 	if( !cards[i]->IsDiscarded() &&
			// 		i != hand[j] )
			// 	{
			// 		hand[card] = i;
			// 	}
			// }
		}
	}

	const Card* const GetCard( int slot ) const
	{
		assert( slot >= 0 );
		assert( slot < nCards );

		if( hand[slot] == -1 ) return( nullptr );
		else return( cards[hand[slot]].get() );
	}
	bool CardExists( int slot ) const
	{
		assert( slot >= 0 );
		assert( slot < nCards );

		return( hand[slot] != -1 );
	}
private:
	std::vector<std::unique_ptr<Card>> cards;
	std::vector<int> hand;
	int nCards;
};