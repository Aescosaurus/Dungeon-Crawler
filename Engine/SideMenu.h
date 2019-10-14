#pragma once

#include "Camera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "CardHandler.h"
#include "MessageLog.h"

class SideMenu
{
public:
	SideMenu( const Camera& cam );

	void Update( const Keyboard& kbd,const Mouse& mouse );
	void Draw( const Camera& cam,Graphics& gfx ) const;

	CardHandler& GetCardHandler();
private:
	RectI area;
	RectI cardArea;
	RectI logArea;
	CardHandler cardHandler;
	MessageLog msgLog;
};