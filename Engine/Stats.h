#pragma once

#include <memory>
#include <vector>
#include <cassert>

class Stats
{
public:
	void UpdateStats( const std::vector<std::unique_ptr<class Card>>& cards );
public:
	int health = 1;
	int defense = 1;
	int regen = 1;
	int attack = 1;
	int magic = 1;
};