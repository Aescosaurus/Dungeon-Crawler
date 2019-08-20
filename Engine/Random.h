#pragma once

#include <random>
#include <cassert>

// Use like int( Random{ 0,6 } ) for a random number
//  between the 2 parameters (including min and max).
class Random
{
public:
	Random( int min,int max )
	{
		assert( min <= max );
		std::uniform_int_distribution<int> dist( min,max );
		value = double( dist( Generate() ) );
	}
	Random( float min,float max )
	{
		assert( min <= max );
		std::uniform_real_distribution<float> dist( min,max );
		value = double( dist( Generate() ) );
	}
	Random( double min,double max )
	{
		assert( min <= max );
		std::uniform_real_distribution<double> dist( min,max );
		value = double( dist( Generate() ) );
	}

	template<typename T>
	static bool Chance( T chance )
	{
		return( T( Random{ T( 0.0 ),T( 100.0 ) } ) < chance );
	}

	operator int() const
	{
		return( int( value ) );
	}
	operator float() const
	{
		return( float( value ) );
	}
	operator double() const
	{
		return( double( value ) );
	}
private:
	static std::mt19937& Generate()
	{
		static std::mt19937 rng{ std::random_device{}( ) };
		return( rng );
	}
private:
	double value;
};