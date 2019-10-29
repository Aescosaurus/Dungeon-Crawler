#include "Card.h"
#include "SpriteEffect.h"

void Card::Draw( const RectI& area,Graphics& gfx ) const
{
	std::string info = name + "\nDamage: " +
		std::to_string( damage ) + "%\nRange: " +
		std::to_string( range );
	unluckyPixel->DrawText( info,area.GetTopLeft() +
		Vei2{ padding,padding },textCol,gfx );

	gfx.DrawSprite( area.right - icon->GetWidth() - padding,
		area.top + padding,*icon,SpriteEffect::Chroma{} );
}

void Card::Discard()
{
	discarded = true;
}

void Card::Reset()
{
	discarded = false;
}

Animation& Card::GetAnimRef()
{
	return( anim );
}

Card::Type Card::GetType() const
{
	return( type );
}

bool Card::IsDiscarded() const
{
	return( discarded );
}

const std::string& Card::GetName() const
{
	return( name );
}

Card::Card( const std::string& name,int damage,int range,
	Type type,const std::string& imgSrc,
	const std::string& animSrc )
	:
	name( name ),
	damage( damage ),
	range( range ),
	type( type ),
	textCol( Type2Color( type ) ),
	icon( SurfCodex::Fetch( imgSrc ) ),
	sprSheet( SurfCodex::Fetch( animSrc ) ),
	anim( 0,0,60,60,4,*sprSheet )
{}

int Card::CalcDamage( int attackStat ) const
{
	// Round damage up to benefit early game and fall off later.
	return( int( std::ceil( float( attackStat ) *
		float( damage ) / 100.0f ) ) );
}

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
