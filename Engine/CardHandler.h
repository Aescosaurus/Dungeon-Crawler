#pragma once

#include "Mouse.h"

class CardHandler
{
public:
	bool StartTurn( const Mouse& mouse );
	bool UpdateTurn( const Mouse& mouse,float dt );
	bool EndTurn();
private:
};