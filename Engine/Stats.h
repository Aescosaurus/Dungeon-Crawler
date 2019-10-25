#pragma once

#include "Card.h"
#include <memory>
#include <vector>
#include <cassert>

class Stats
{
public:
	void UpdateStats( const std::vector<std::unique_ptr<Card>>& cards )
	{
		health = 1;
		defense = 1;
		regen = 1;
		attack = 1;
		magic = 1;

		for( const auto& card : cards )
		{
			switch( card->GetType() )
			{
			case Card::Type::Typeless:
				health += 1;
				defense += 1;
				// regen += 1;
				attack += 1;
				// magic += 1;
				break;
			case Card::Type::Fire:
				attack += 5;
				break;
			case Card::Type::Poison:
				regen += 1;
				break;
			case Card::Type::Ice:
				health += 5;
				defense += 2;
				break;
			case Card::Type::Ghost:
				magic += 6;
				break;
			default:
				assert( false );
				break;
			}
		}
	}
public:
	int health = 1;
	int defense = 1;
	int regen = 1;
	int attack = 1;
	int magic = 1;
};