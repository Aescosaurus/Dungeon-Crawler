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

void Camera::RenderImage( const Vec2& pos,CSurfPtr img,
	const RectI& area,Dir::Direction rotation ) const
{
	if( viewArea.GetExpandedBy( 1.0f ).OverlapsPoint( pos ) )
	{
		gfx.DrawSprite(
			int( ( pos.x - viewArea.left ) * float( tileSize ) ),
			int( ( pos.y - viewArea.top ) * float( tileSize ) ),
			*img,area,
			SpriteEffect::Chroma{ Colors::Magenta },
			Dir::Dir2Mat( rotation )
		);
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

bool Camera::IsOnScreen( const Vei2& pos ) const
{
	return( pos.x >= 0 && pos.x < viewArea.GetWidth() &&
		pos.y >= 0 && pos.y < viewArea.GetHeight() );
}

Vec2 Camera::RelativeToAbsolute( const Vec2& rel ) const
{
	// assert( rel.x >= 0 && rel.x < viewArea.GetWidth() &&
	// 	rel.y >= 0 && rel.y < viewArea.GetHeight() );

	return( rel + viewArea.GetTopLeft() );
}
