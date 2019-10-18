#pragma once

#include "Rect.h"
#include "Graphics.h"
#include <deque>
#include <string>
#include "Codex.h"

class MessageLog
{
public:
	MessageLog( const RectI& messageArea );

	void Draw( Graphics& gfx ) const;

	void Log( const std::string& message );
private:
	void AddMessage( const std::string& message );
private:
	static constexpr int padding = 5;
	Vei2 messageStart;
	int minMessageX;
	int maxMessageX;
	std::deque<std::string> messages;
	CFontPtr unluckyPixel = FontCodex::Fetch( "Fonts/UnluckyPixel.bmp" );
	static constexpr int nMessages = 11;
};