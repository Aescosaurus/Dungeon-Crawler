#include "Card.h"
#include "SpriteEffect.h"

void Card::Draw( const RectI& area,Graphics& gfx ) const
{
	std::string info = name + "\nDamage: " +
		std::to_string( damage ) + "%\nRange: " +
		std::to_string( range );
	unluckyPixel->DrawText( info,area.GetTopLeft() +
		Vei2{ padding,padding },textCol,gfx );

	gfx.DrawSprite( area.right - img->GetWidth() - padding,
		area.top + padding,*img,SpriteEffect::Chroma{} );
}

void Card::Discard()
{
	discarded = true;
}

void Card::Reset()
{
	discarded = false;
}

Card::Type Card::GetType() const
{
	return( type );
}

bool Card::IsDiscarded() const
{
	return( discarded );
}

Card::Card( const std::string& name,int damage,int range,
	Type type,const std::string& imgSrc )
	:
	name( name ),
	damage( damage ),
	range( range ),
	type( type ),
	textCol( Type2Color( type ) ),
	img( SurfCodex::Fetch( imgSrc ) )
{}

Color Card::Type2Color( Type t )
{
	static constexpr Color colors[] =
	{
		Colors::Gray1,
		Colors::Orange1,
		Colors::Green1,
		Colors::Blue1,
		Colors::Purple1
	};

	return( colors[int( t )] );
}
