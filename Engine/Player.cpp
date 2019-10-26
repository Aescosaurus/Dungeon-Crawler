#include "Player.h"
#include <algorithm>
#include "Enemy.h"

Player::Player( const Vec2& pos,const TileMap& tilemap,
	Camera& cam,SideMenu& menu )
	:
	pos( pos ),
	tilemap( tilemap ),
	cam( cam ),
	menu( menu ),
	cardHandler( menu.GetCardHandler() ),
	msgLog( menu.GetMessageLog() )
{
	stats.UpdateStats( cardHandler.GetCards() );

	for( int i = 0; i < 4; ++i )
	{
		frames.emplace_back( RectI{
			( img->GetWidth() / 4 ) * i,
			( img->GetWidth() / 4 ) * ( i + 1 ),
			0,img->GetHeight() } );
	}
}

bool Player::StartTurn( const Keyboard& kbd,Mouse& mouse,
	const std::vector<std::unique_ptr<Enemy>>& enemies )
{
	// Move turn.
	move = { 0,0 };
	if( kbd.KeyIsPressed( 'W' ) ) --move.y;
	else if( kbd.KeyIsPressed( 'S' ) ) ++move.y;
	else if( kbd.KeyIsPressed( 'A' ) ) --move.x;
	else if( kbd.KeyIsPressed( 'D' ) ) ++move.x;

	// Play card turn.
	menu.Update( kbd,mouse );

	if( ( move.x != 0 || move.y != 0 ) &&
		tilemap.GetTile( Vei2( pos ) + move ) ==
		TileMap::TileType::Floor &&
		std::find_if( enemies.begin(),enemies.end(),[&]
		( const std::unique_ptr<Enemy>& curEnemy )
	{
		return( curEnemy->GetPos() == pos + move );
	} ) == enemies.end() )
	{
		lookDir = Dir::Vec2Dir( move );
		target = Vei2( pos ) + move;
		turn = TurnType::Movement;
		return( true );
	}
	else if( cardHandler.DoneWithTurn() )
	{
		turn = TurnType::Attack;
		// target = cardHandler.GetTarget();
		return( true );
	}
	else if( kbd.KeyIsPressed( VK_SPACE ) )
	{
		turn = TurnType::None;
		return( true );
	}
	else
	{
		return( false );
	}
}

bool Player::UpdateTurn( const Mouse& mouse,float dt )
{
	if( turn != TurnType::Attack )
	{
		cardHandler.DeselectCard();
	}

	switch( turn )
	{
	case TurnType::None:
		return( true );
		break;
	case TurnType::Movement:
		pos += Vec2( move ) / moveTimer.GetMaxTime() * dt;
		cam.CenterOn( pos );

		moveTimer.Update( dt );
		if( moveTimer.IsDone() )
		{
			moveTimer.Reset();
			return( true );
		}
		else
		{
			return( false );
		}
		break;
	case TurnType::Attack:
		return( cardHandler.PlaySelectedCard( dt ) );
		break;
	default:
		assert( false );
		return( false );
		break;
	}
}

bool Player::EndTurn()
{
	switch( turn )
	{
	case TurnType::None:
		break;
	case TurnType::Movement:
		msgLog.Log( "Moving!" );
		pos = target;
		cam.CenterOn( pos );
		move = { 0,0 };
		break;
	case TurnType::Attack:
		msgLog.Log( "Attacking!" );
		cardHandler.EndTurn();
		break;
	default:
		assert( false );
		break;
	}

	return( true );
}

void Player::Draw( const Camera& cam ) const
{
	// cam.RenderRect( pos,Colors::Blue1 );
	cam.RenderImage( pos,img,frames[int( lookDir )] );
}

const Vec2& Player::GetPos() const
{
	return( pos );
}
