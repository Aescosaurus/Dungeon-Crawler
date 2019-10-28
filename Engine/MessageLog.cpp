#include "MessageLog.h"

MessageLog::MessageLog( const RectI& messageArea )
	:
	messageStart( messageArea.GetTopLeft() ),
	minMessageX( messageArea.left + padding ),
	maxMessageX( messageArea.right - padding )
{
	for( int i = 0; i < nMessages; ++i )
	{
		messages.push_back( "" );
	}
}

void MessageLog::Draw( Graphics& gfx ) const
{
	// std::string text = "";
	// for( const std::string& message : messages )
	// {
	// 	text += message + '\n';
	// }
	// 
	// unluckyPixel->DrawText( text,messageStart +
	// 	Vei2::Right() * padding,
	// 	Colors::Black1,gfx );
	unluckyPixel->DrawLines( std::vector<std::string>{
		messages.begin(),messages.end() },
		messageStart + Vei2::Right() * padding,
		Colors::Black1,gfx );
}

void MessageLog::Log( const std::string& message )
{
	if( unluckyPixel->CalcTextWidth( message ) >
		maxMessageX - minMessageX )
	{
		std::vector<std::string> lines;
		lines.emplace_back( "" );

		for( char c : message )
		{
			if( unluckyPixel->CalcTextWidth(
				lines.back() + c ) < maxMessageX - minMessageX )
			{
				lines.back() += c;
			}
			else
			{
				lines.emplace_back( std::string{ c } );
			}
		}

		for( const auto& line : lines )
		{
			AddMessage( line );
		}
	}
	else
	{
		AddMessage( message );
	}
}

void MessageLog::AddMessage( const std::string& message )
{
	assert( unluckyPixel->CalcTextWidth( message ) <=
		maxMessageX - minMessageX );

	messages.pop_front();
	messages.push_back( message );
}
