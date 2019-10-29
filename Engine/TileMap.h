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
		FloorSpecial,
		Wall,
		WallCoated,
		WallHall,
		WallHallTall,
		WallCornerDL,
		WallCornerDR,
		WallCornerUL,
		WallCornerUR,
		WallOutUp,
		WallOutDown,
		WallOutLeft,
		WallOutRight,
		WallTop,
		WallBottom,
		WallLeft,
		WallRight
	};
public:
	TileMap();

	void Draw( const Camera& cam ) const;

	void GenerateRooms( const RangeI& nRooms,
		const RangeI& roomSize,const RangeI& mapSize );
	void LoadTileSprites( const std::string& src );

	TileType GetTile( int x,int y ) const;
	TileType GetTile( const Vei2& pos ) const;
	Vei2 GetRandFloorPos() const;
private:
	void SetTile( int x,int y,TileType t );

	void UpdateWallTile( int x,int y );
	int CountAdjacentWalls( int x,int y );
	std::vector<int> GetAdjacentTiles( int x,int y );
private:
	int width;
	int height;
	std::vector<TileType> tiles;
	std::vector<Surface> tileSprites;
};