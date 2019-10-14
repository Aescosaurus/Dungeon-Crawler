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
	Vei2 messageStart;
	std::deque<std::string> messages;
	CFontPtr unluckyPixel = FontCodex::Fetch( "Fonts/UnluckyPixel.bmp" );
	static constexpr int nMessages = 11;
};