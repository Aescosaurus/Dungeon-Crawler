#include "Card.h"

void Card::Draw( const RectI& area,Graphics& gfx ) const
{
	std::string info = name + "\nDamage: " +
		std::to_string( damage ) + "%\nRange: " +
		std::to_string( range );
	unluckyPixel->DrawText( info,area.GetTopLeft() +
		Vei2{ padding,padding },textCol,gfx );
}

Card::Card( const std::string& name,int damage,int range,
	Type type )
	:
	name( name ),
	damage( damage ),
	range( range ),
	type( type ),
	textCol( Type2Color( type ) )
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
