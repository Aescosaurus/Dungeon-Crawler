#pragma once

#include "Camera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "CardHandler.h"
#include <vector>
#include <string>

class SideMenu
{
public:
	SideMenu( const Camera& cam );

	void Update( const Keyboard& kbd,const Mouse& mouse );
	void Draw( const Camera& cam,Graphics& gfx ) const;

	static void LogMessage( const std::string& message );

	CardHandler& GetCardHandler();
private:
	static constexpr int maxMessages = 10;
	static std::vector<std::string> messageLog;
	RectI area;
	RectI cardArea;
	CardHandler cardHandler;
};