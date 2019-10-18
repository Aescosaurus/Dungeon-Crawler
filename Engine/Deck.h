#pragma once

#include <vector>
#include <memory>
#include "Card.h"

class Deck
{
public:
	Deck()
	{

	}
private:
	std::vector<std::unique_ptr<Card>> cards;
};