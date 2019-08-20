#include "Camera.h"

Camera::Camera( Graphics& gfx )
	:
	gfx( gfx )
{}

void Camera::RenderRect( const Vec2& pos,Color c ) const
{
	if( viewArea.OverlapsPoint( pos ) )
	{
		gfx.DrawRect(
			int( ( pos.x - viewArea.left ) * float( tileSize ) ),
			int( ( pos.y - viewArea.top ) * float( tileSize ) ),
			tileSize,tileSize,
			c );
	}
}

void Camera::CenterOn( const Vec2& pos )
{
	viewArea.MoveTo( pos - Vec2( Vei2( viewArea.GetSize() ) / 2 ) );
}

const Rect& Camera::GetViewArea() const
{
	return( viewArea );
}
