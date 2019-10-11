#include "SideMenu.h"

SideMenu::SideMenu( const Camera& cam )
	:
	area( int( cam.GetViewArea().right ) * Camera::tileSize,
		Graphics::ScreenWidth,0,Graphics::ScreenHeight ),
	cardArea( area.left,area.right,area.top + 100,area.top + 300 ),
	cardHandler( cardArea )
{}

void SideMenu::Update( const Keyboard& kbd,const Mouse& mouse )
{
}

void SideMenu::Draw( Graphics& gfx ) const
{
	gfx.DrawRectDim( area.left,area.top,
		area.right,area.bottom,
		Colors::Gray );

	cardHandler.Draw( gfx );
}
