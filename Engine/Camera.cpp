#include "Camera.h"

Camera::Camera( Graphics& gfx )
	:
	gfx( gfx )
{}

void Camera::RenderRect( const Vec2& pos,Color c ) const
{
	if( viewArea.GetExpandedBy( 1.0f ).OverlapsPoint( pos ) )
	{
		gfx.DrawRectSafe(
			int( ( pos.x - viewArea.left ) * float( tileSize ) ),
			int( ( pos.y - viewArea.top ) * float( tileSize ) ),
			tileSize,tileSize,
			c );
	}
}

void Camera::RenderRectRelative( const Vec2& pos,Color c ) const
{
	if( pos.x >= 0 && pos.x < viewArea.GetWidth() &&
		pos.y >= 0 && pos.y < viewArea.GetHeight() )
	{
		RenderRect( pos + viewArea.GetTopLeft(),c );
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
