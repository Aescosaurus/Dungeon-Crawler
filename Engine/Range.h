#pragma once

#include "Random.h"

template<typename T>
class Range_
{
public:
	Range_( const T& min,const T& max )
		:
		min( min ),
		max( max )
	{}

	T Rand() const
	{
		return( T( Random{ min,max } ) );
	}
public:
	T min;
	T max;
};

typedef Range_<float> RangeF;
typedef Range_<int> RangeI;