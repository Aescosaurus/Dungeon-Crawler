#pragma once

#include "Card.h"

class BasicStrike
	:
	public Card
{
public:
	BasicStrike()
		:
		Card( "Basic Strike",50,1,Card::Type::Typeless,
			"Images/Cards/BasicStrike.bmp",
			"Images/Cards/BasicStrikeAnim.bmp" )
	{}

	int Play( CardUpdateInfo& info ) override
	{
		return( info.enemy.Attack( CalcDamage( info.stats.attack ) ) );
	}
};