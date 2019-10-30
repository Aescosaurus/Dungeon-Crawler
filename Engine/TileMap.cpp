#include "TileMap.h"
#include "Vec2.h"
#include "Rect.h"

TileMap::TileMap()
{
	GenerateRooms( RangeI{ 5,7 },RangeI{ 4,10 },RangeI{ 30,50 } );
	LoadTileSprites( "Images/Tilemaps/Grass.bmp" );
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
			// const auto col = ( GetTile( x,y ) == TileType::Wall )
			// 	? Colors::Green3 : Colors::Green1;
			// cam.RenderRect( Vec2( Vei2{ x,y } ),col );
			const auto& spr = tileSprites[int( GetTile( x,y ) )];
			cam.RenderImage( Vec2( Vei2{ x,y } ),
				&spr,spr.GetRect() );
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

	for( int y = 0; y < height; ++y )
	{
		for( int x = 0; x < width; ++x )
		{
			UpdateWallTile( x,y );
		}
	}
}

void TileMap::LoadTileSprites( const std::string& src )
{
	const Surface tileSheet = src;
	tileSprites.clear();
	std::vector<Surface> rawSprites;
	for( int y = 0; y < tileSheet.GetHeight(); y += Camera::tileSize )
	{
		for( int x = 0; x < tileSheet.GetWidth(); x += Camera::tileSize )
		{
			rawSprites.emplace_back( tileSheet.GetClipped( RectI{
				x,x + Camera::tileSize,y,y + Camera::tileSize } ) );
		}
	}

	tileSprites.emplace_back( rawSprites[0] );
	tileSprites.emplace_back( rawSprites[1] );
	tileSprites.emplace_back( rawSprites[2] );
	tileSprites.emplace_back( rawSprites[3] );
	tileSprites.emplace_back( rawSprites[4] );
	tileSprites.emplace_back( rawSprites[5] );
	tileSprites.emplace_back( rawSprites[6] );
	tileSprites.emplace_back( rawSprites[6].GetXReversed() );
	tileSprites.emplace_back( rawSprites[7] );
	tileSprites.emplace_back( rawSprites[7].GetXReversed() );
	tileSprites.emplace_back( rawSprites[8] );
	tileSprites.emplace_back( rawSprites[8].GetYReversed() );
	tileSprites.emplace_back( rawSprites[9] );
	tileSprites.emplace_back( rawSprites[9].GetXReversed() );
	tileSprites.emplace_back( rawSprites[10] );
	tileSprites.emplace_back( rawSprites[10].GetYReversed() );
	tileSprites.emplace_back( rawSprites[11] );
	tileSprites.emplace_back( rawSprites[11].GetXReversed() );
}

TileMap::TileType TileMap::GetTile( int x,int y ) const
{
	if( x < 0 || x >= width ||
		y < 0 || y >= height )
	{
		return( TileType::WallCoated );
	}
	else
	{
		return( tiles[y * width + x] );
	}
}

TileMap::TileType TileMap::GetTile( const Vei2& pos ) const
{
	return( GetTile( pos.x,pos.y ) );
}

Vei2 TileMap::GetRandFloorPos() const
{
	auto randPos = Vei2{ -1,-1 };
	while( GetTile( randPos.x,randPos.y ) >= TileType::Wall )
	{
		randPos.x = int( Random{ 0,width - 1 } );
		randPos.y = int( Random{ 0,height - 1 } );
	}
	return( randPos );
}

void TileMap::SetTile( int x,int y,TileType t )
{
	assert( x >= 0 );
	assert( x < width );
	assert( y >= 0 );
	assert( y < height );
	tiles[y * width + x] = t;
}

void TileMap::UpdateWallTile( int x,int y )
{
	const auto curTile = GetTile( x,y );
	if( curTile == TileType::Floor )
	{
		if( int( Random{ 0,100 } ) < 20 )
		{
			SetTile( x,y,TileType::FloorSpecial );
		}
	}
	else
	{
		assert( curTile == TileType::Wall );
		const auto nAdjacentWalls = CountAdjacentWalls( x,y );
		const auto adjTiles = GetAdjacentTiles( x,y );
		typedef std::vector<int> vi;

		switch( nAdjacentWalls )
		{
		case 0:
			SetTile( x,y,TileType::Wall );
			break;
		case 1:
			// up down left right
		{
			if( adjTiles == vi{ 1,0,0,0 } )
			{
				SetTile( x,y,TileType::WallOutDown );
			}
			else if( adjTiles == vi{ 0,1,0,0 } )
			{
				SetTile( x,y,TileType::WallOutUp );
			}
			else if( adjTiles == vi{ 0,0,1,0 } )
			{
				SetTile( x,y,TileType::WallOutRight );
			}
			else if( adjTiles == vi{ 0,0,0,1 } )
			{
				SetTile( x,y,TileType::WallOutLeft );
			}
		}
		break;
		case 2:
			// up down, left right,
			// up right, right down, down left, left up
		{
			if( adjTiles == vi{ 1,1,0,0 } )
			{
				SetTile( x,y,TileType::WallHallTall );
			}
			else if( adjTiles == vi{ 0,0,1,1 } )
			{
				SetTile( x,y,TileType::WallHall );
			}
			else if( adjTiles == vi{ 1,0,0,1 } )
			{
				SetTile( x,y,TileType::WallCornerDL );
			}
			else if( adjTiles == vi{ 0,1,0,1 } )
			{
				SetTile( x,y,TileType::WallCornerUL );
			}
			else if( adjTiles == vi{ 0,1,1,0 } )
			{
				SetTile( x,y,TileType::WallCornerUR );
			}
			else if( adjTiles == vi{ 1,0,1,0 } )
			{
				SetTile( x,y,TileType::WallCornerDR );
			}
		}
		break;
		case 3:
			// up down left right
		{
			if( adjTiles == vi{ 0,1,1,1 } )
			{
				SetTile( x,y,TileType::WallTop );
			}
			else if( adjTiles == vi{ 1,0,1,1 } )
			{
				SetTile( x,y,TileType::WallBottom );
			}
			else if( adjTiles == vi{ 1,1,0,1 } )
			{
				SetTile( x,y,TileType::WallLeft );
			}
			else if( adjTiles == vi{ 1,1,1,0 } )
			{
				SetTile( x,y,TileType::WallRight );
			}
		}
		break;
		case 4:
			SetTile( x,y,TileType::WallCoated );
			break;
		default:
			assert( false );
			break;
		}
	}
}

int TileMap::CountAdjacentWalls( int x,int y )
{
	int walls = 0;
	if( GetTile( x,y - 1 ) >= TileType::Wall ) ++walls;
	if( GetTile( x,y + 1 ) >= TileType::Wall ) ++walls;
	if( GetTile( x - 1,y ) >= TileType::Wall ) ++walls;
	if( GetTile( x + 1,y ) >= TileType::Wall ) ++walls;
	return( walls );
}

std::vector<int> TileMap::GetAdjacentTiles( int x,int y )
{
	std::vector<int> temp;
	temp.reserve( 4 );

	temp.emplace_back( GetTile( x,y - 1 ) >= TileType::Wall ? 1 : 0 );
	temp.emplace_back( GetTile( x,y + 1 ) >= TileType::Wall ? 1 : 0 );
	temp.emplace_back( GetTile( x - 1,y ) >= TileType::Wall ? 1 : 0 );
	temp.emplace_back( GetTile( x + 1,y ) >= TileType::Wall ? 1 : 0 );

	return( temp );
}
