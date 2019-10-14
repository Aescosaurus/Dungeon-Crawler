#include "MessageLog.h"

MessageLog::MessageLog( const RectI& messageArea )
	:
	messageStart( messageArea.GetTopLeft() )
{
	for( int i = 0; i < nMessages; ++i )
	{
		messages.push_back( "" );
	}
}

void MessageLog::Draw( Graphics& gfx ) const
{
	std::string text = "";
	for( const std::string& message : messages )
	{
		text += message + '\n';
	}

	unluckyPixel->DrawText( text,messageStart,gfx );
}

void MessageLog::Log( const std::string& message )
{
	messages.pop_front();
	messages.push_back( message );
}
