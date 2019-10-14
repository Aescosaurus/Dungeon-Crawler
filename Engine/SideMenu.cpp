#include "SideMenu.h"

std::vector<std::string> SideMenu::messageLog;

SideMenu::SideMenu( const Camera& cam )
	:
	area( int( cam.GetViewArea().right ) * Camera::tileSize,
		Graphics::ScreenWidth,0,Graphics::ScreenHeight ),
	cardArea( area.left,area.right,area.top + 150,area.top + 350 ),
	cardHandler( cardArea )
{}

void SideMenu::Update( const Keyboard& kbd,const Mouse& mouse )
{
	cardHandler.Update( kbd,mouse );
}

void SideMenu::Draw( const Camera& cam,Graphics& gfx ) const
{
	gfx.DrawRectDim( area.left,area.top,
		area.right,area.bottom,
		Colors::Gray );

	cardHandler.Draw( cam,gfx );
}

void SideMenu::LogMessage( const std::string& message )
{

}

CardHandler& SideMenu::GetCardHandler()
{
	return( cardHandler );
}
