#include "Card.h"

void Card::Draw( const RectI& area,Graphics& gfx ) const
{
	unluckyPixel->DrawText( name,area.GetTopLeft() +
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
		Colors::LightGray1,
		Colors::Orange1,
		Colors::Green1,
		Colors::Blue1,
		Colors::Purple1
	};

	return( colors[int( t )] );
}
