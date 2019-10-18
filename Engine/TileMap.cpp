#include "TileMap.h"
#include "Vec2.h"
#include "Rect.h"

TileMap::TileMap()
{
	GenerateRooms( RangeI{ 5,7 },RangeI{ 4,10 },RangeI{ 30,50 } );
}

void TileMap::Draw( const Camera& cam ) const
{
	const auto viewArea = RectI( cam.GetViewArea() );

	// for( int y = 0; y < height; ++y )
	for( int y = viewArea.top - 1; y < viewArea.bottom + 1; ++y )
	{
		// for( int x = 0; x < width; ++x )
		for( int x = viewArea.left - 1; x < viewArea.right + 1; ++x )
		{
			const auto col = ( GetTile( x,y ) == TileType::Wall )
				? Colors::Orange3 : Colors::Orange1;
			cam.RenderRect( Vec2( Vei2{ x,y } ),col );
		}
	}
}

void TileMap::GenerateRooms( const RangeI& nRooms,
	const RangeI& roomSize,const RangeI& mapSize )
{
	width = mapSize.Rand();
	height = mapSize.Rand();

	// Create rooms.
	const int roomCount = nRooms.Rand();
	std::vector<RectI> rooms;
	rooms.reserve( roomCount );
	for( int i = 0; i < roomCount; ++i )
	{
		const auto roomWidth = roomSize.Rand();
		const auto roomHeight = roomSize.Rand();
		const auto roomX = int( Random{ 1,width - roomWidth - 1 } );
		const auto roomY = int( Random{ 1,height - roomHeight - 1 } );
		rooms.emplace_back( RectI{ Vei2{ roomX,roomY },
			roomWidth,roomHeight } );
	}

	// Create connections.
	std::vector<Vei2> conns;
	conns.reserve( roomCount );
	for( int i = 1; i < roomCount; ++i )
	{
		conns.emplace_back( Vei2{ i,i - 1 } );
	}

	// Fill tilemap vector with walls.
	tiles.clear();
	tiles.reserve( width * height );
	for( int i = 0; i < width * height; ++i )
	{
		tiles.emplace_back( TileType::Wall );
	}

	// Place rooms in tilemap vec.
	for( const auto& room : rooms )
	{
		for( int y = room.top; y < room.bottom; ++y )
		{
			for( int x = room.left; x < room.right; ++x )
			{
				tiles[y * width + x] = TileType::Floor;
			}
		}
	}

	// Place corridors in tilemap vec.
	for( const auto& conn : conns )
	{
		const auto target1 = rooms[conn.x].GetRandPoint();
		const auto target2 = rooms[conn.y].GetRandPoint();
		const auto diff = target2 - target1;

		if( Random::Chance( 50.0f ) )
		{
			Vei2 pos = target1;
			for( int x = 0; x < std::abs( diff.x ); ++x )
			{
				pos.x += ( diff.x / std::abs( diff.x ) );
				tiles[pos.y * width + pos.x] = TileType::Floor;
			}
			for( int y = 0; y < std::abs( diff.y ); ++y )
			{
				pos.y += ( diff.y / std::abs( diff.y ) );
				tiles[pos.y * width + pos.x] = TileType::Floor;
			}
		}
		else
		{
			Vei2 pos = target1;
			for( int y = 0; y < std::abs( diff.y ); ++y )
			{
				pos.y += ( diff.y / std::abs( diff.y ) );
				tiles[pos.y * width + pos.x] = TileType::Floor;
			}
			for( int x = 0; x < std::abs( diff.x ); ++x )
			{
				pos.x += ( diff.x / std::abs( diff.x ) );
				tiles[pos.y * width + pos.x] = TileType::Floor;
			}
		}
	}

	// TODO: Randomize tiletypes to create cool looking floors.
}

TileMap::TileType TileMap::GetTile( int x,int y ) const
{
	if( x < 0 || x >= width ||
		y < 0 || y >= height )
	{
		return( TileType::Wall );
	}
	else
	{
		return( tiles[y * width + x] );
	}
}

Vei2 TileMap::GetRandFloorPos() const
{
	auto randPos = Vei2{ -1,-1 };
	while( GetTile( randPos.x,randPos.y ) == TileType::Wall )
	{
		randPos.x = int( Random{ 0,width - 1 } );
		randPos.y = int( Random{ 0,height - 1 } );
	}
	return( randPos );
}
