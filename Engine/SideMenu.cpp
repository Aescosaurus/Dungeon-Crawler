#include "SideMenu.h"

SideMenu::SideMenu( const Camera& cam )
	:
	cam( cam ),
	area( int( cam.GetViewArea().right ) * Camera::tileSize,
		Graphics::ScreenWidth,0,Graphics::ScreenHeight ),
	cardArea( area.left,area.right,area.top + 150,area.top + 350 ),
	logArea( area.left,area.right,area.top + 350,area.bottom ),
	cardHandler( cardArea ),
	msgLog( logArea )
{}

void SideMenu::Update( const Keyboard& kbd,Mouse& mouse )
{
	cardHandler.Update( cam,kbd,mouse );
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

MessageLog& SideMenu::GetMessageLog()
{
	return( msgLog );
}
