#pragma once

#include <string>

class Card
{
public:
	enum class Type
	{
		Fire,
		Poison,
		Ice,
		Ghost
	};
public:
private:
	std::string name;
	int damage;
};