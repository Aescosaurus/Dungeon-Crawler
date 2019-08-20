#pragma once

#include <vector>
#include "Range.h"
#include "Camera.h"

class TileMap
{
public:
	enum class TileType
	{
		Floor,
		Wall
	};
public:
	TileMap();

	void Draw( const Camera& cam ) const;

	void GenerateRooms( const RangeI& nRooms,
		const RangeI& roomSize,const RangeI& mapSize );

	TileType GetTile( int x,int y ) const;
	Vei2 GetRandFloorPos() const;
private:
	int width;
	int height;
	std::vector<TileType> tiles;
};