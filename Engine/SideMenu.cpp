#include "SideMenu.h"

SideMenu::SideMenu( const Camera& cam )
	:
	area( int( cam.GetViewArea().right ) * Camera::tileSize,
		Graphics::ScreenWidth,0,Graphics::ScreenHeight ),
	cardArea( area.left,area.right,area.top + 150,area.top + 350 ),
	logArea( area.left,area.right,area.top + 350,area.bottom ),
	cardHandler( cardArea ),
	msgLog( logArea )
{}

void SideMenu::Update( const Keyboard& kbd,const Mouse& mouse )
{
	cardHandler.Update( kbd,mouse );

	for( char i = 'A'; i < 'Z'; ++i )
	{
		if( kbd.KeyIsPressed( i ) )
		{
			msgLog.Log( std::to_string( int( i ) ) );
		}
	}
}

void SideMenu::Draw( const Camera& cam,Graphics& gfx ) const
{
	gfx.DrawRectDim( area.left,area.top,
		area.right,area.bottom,
		Colors::Gray );

	cardHandler.Draw( cam,gfx );
	msgLog.Draw( gfx );
}

CardHandler& SideMenu::GetCardHandler()
{
	return( cardHandler );
}
