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

	// for( int i = 0; i < 4; ++i )
	// {
	// 	frames.emplace_back( RectI{
	// 		( img->GetWidth() / 4 ) * i,
	// 		( img->GetWidth() / 4 ) * ( i + 1 ),
	// 		0,img->GetHeight() } );
	// }
	for( int i = 0; i < 4; ++i )
	{
		anims.emplace_back( Animation{ 0,i * 60,60,60,4,
			*sprSheet } );
	}
}

bool Player::StartTurn( const Keyboard& kbd,Mouse& mouse,
	const std::vector<std::unique_ptr<Enemy>>& enemies )
{
	// Move turn.
	move = Vei2::Zero();
	if( kbd.KeyIsPressed( 'W' ) ) --move.y;
	else if( kbd.KeyIsPressed( 'S' ) ) ++move.y;
	else if( kbd.KeyIsPressed( 'A' ) ) --move.x;
	else if( kbd.KeyIsPressed( 'D' ) ) ++move.x;

	// Play card turn.
	menu.Update( kbd,mouse );

	if( move != Vei2::Zero() )
	{
		// lookAnim.SetFrame( int( Dir::Vec2Dir( move ) ) );

		if( tilemap.GetTile( Vei2( pos ) + move ) <
			TileMap::TileType::Wall &&
			std::find_if( enemies.begin(),enemies.end(),[&]
			( const std::unique_ptr<Enemy>& curEnemy )
		{
			return( curEnemy->GetPos() == pos + move );
		} ) == enemies.end() )
		{
			lookDir = Dir::Vec2Dir( move );
			target = Vei2( pos ) + move;
			if( ++curAnimFrame >= 4 ) curAnimFrame = 0;
			anims[int( lookDir )].SetFrame( frameOrder[curAnimFrame] );
			turn = TurnType::Movement;
			return( true );
		}
		else
		{
			lookDir = Dir::Vec2Dir( move );
			return( false );
		}
	}
	else if( cardHandler.DoneWithTurn() )
	{
		target = Vei2( pos ) + Dir::Dir2Vec( lookDir );
		cardHandler.StartTurn( target,lookDir );
		turn = TurnType::Attack;
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

bool Player::EndTurn( std::vector<std::unique_ptr<Enemy>>& enemies,
	std::vector<HitNumber>& hitNums )
{
	switch( turn )
	{
	case TurnType::None:
		break;
	case TurnType::Movement:
		//// msgLog.Log( "Moving!" );
		anims[int( lookDir )].SetFrame( 0 );
		pos = target;
		cam.CenterOn( pos );
		move = { 0,0 };
		break;
	case TurnType::Attack:
	{
		Enemy* enemy = nullptr;
		for( auto& e : enemies )
		{
			if( e->GetPos() == target )
			{
				enemy = e.get();
			}
		}
		// msgLog.Log( "Attacking!" );
		cardHandler.EndTurn( enemy,stats,msgLog,hitNums,cam );
	}
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
	// cam.RenderImage( pos,img,frames[int( lookDir )] );
	// lookAnim.Draw( pos,cam );
	anims[int( lookDir )].Draw( pos,cam );
}

const Vec2& Player::GetPos() const
{
	return( pos );
}
