#include "CardHandler.h"

CardHandler::CardHandler( const RectI& cardArea )
	:
	deck( nCards )
{
	const auto width = cardArea.GetWidth();
	const auto height = cardArea.GetHeight() / 3;

	cardSlots.reserve( nCards );
	for( int i = 0; i < nCards; ++i )
	{
		CardSlot temp;
		temp.area = RectI{ Vei2{ cardArea.left + padding,
			cardArea.top + i * ( height + padding / 2 ) },
			width - padding * 2,height - padding };
		temp.hovering = false;
		cardSlots.emplace_back( temp );
	}
}

void CardHandler::Update( const Camera& cam,
	const Keyboard& kbd,Mouse& mouse )
{
	for( int i = 0; i < nCards; ++i )
	{
		auto& curCard = cardSlots[i];

		curCard.hovering = curCard.area.ContainsPoint( mouse.GetPos() );

		if( ( curCard.hovering && mouse.LeftIsPressed() ) ||
			kbd.KeyIsPressed( char( ( i + 1 ) + '0' ) ) )
		{
			if( deck.CardExists( i ) )
			{
				selectedCard = i;
			}
		}
	}

	if( selectedCard != -1 )
	{
		selectedSquare = mouse.GetPos() / Camera::tileSize;

		bool released = false;
		while( !mouse.IsEmpty() )
		{
			if( mouse.Read().GetType() == Mouse::Event::Type::LRelease )
			{
				released = true;
			}
		}

		if( cam.IsOnScreen( selectedSquare ) &&
			// !mouse.LeftIsPressed() &&
			released &&
			selectedSquare != Vei2{ -1,-1 } )
		{
			doneWithTurn = true;
		}
	}

	// playTime.Reset();

	mousePos = mouse.GetPos();
}

void CardHandler::Draw( const Camera& cam,Graphics& gfx ) const
{
	// for( const auto& slot : cardSlots )
	for( int i = 0; i < int( cardSlots.size() ); ++i )
	{
		const auto& slot = cardSlots[i];
		const auto& card = deck.GetCard( i );

		if( i != selectedCard &&
			card != nullptr )
		{
			gfx.DrawRectDim( slot.area,
				slot.hovering
				? Colors::White1
				: Colors::LightGray1 );
			card->Draw( slot.area,gfx );
		}
		else
		{
			gfx.DrawRectDim( slot.area,
				Colors::Gray1 );
		}
	}

	if( selectedCard != -1 )
	{
		assert( deck.CardExists( selectedCard ) );
		// cam.RenderRect( cam.RelativeToAbsolute(
		// 	Vec2( mousePos ) ),Colors::White1 );

		const auto& curCard = cardSlots[selectedCard];

		// gfx.DrawRectDim( curCard.area.GetMovedBy( mousePos ),
		// 	Colors::White1 );
		const int width = curCard.area.GetWidth();
		const int height = curCard.area.GetHeight();
		gfx.DrawRectSafe( mousePos.x - width / 2,
			mousePos.y - height / 2,
			width,height,
			Colors::White1 );
		deck.GetCard( selectedCard )->Draw( RectI{
			Vei2{ mousePos.x - width / 2,
			mousePos.y - height / 2 },width,height },gfx );
	}

	if( curCardAnim != nullptr )
	{
		curCardAnim->Draw( cardAnimSpot,cam,cardDir );
	}
}

void CardHandler::StartTurn( const Vec2& target,Dir::Direction dir )
{
	cardAnimSpot = target;
	cardDir = dir;
	curCardAnim = &deck.GetCardRef( selectedCard ).GetAnimRef();
	curCardAnim->Reset();
}

bool CardHandler::PlaySelectedCard( float dt )
{
	curCardAnim->Update( dt );

	if( curCardAnim->IsDone() )
	{
		doneWithTurn = false;
	}

	return( curCardAnim->IsDone() );
}

void CardHandler::EndTurn( Enemy* enemy,const Stats& stats,
	MessageLog& msgLog,std::vector<HitNumber>& hitNums,
	const Camera& cam )
{
	auto& curCard = deck.GetCardRef( selectedCard );
	if( enemy != nullptr )
	{
		const auto dmg = curCard.Play(
			CardUpdateInfo{ *enemy,stats } );

		// hitNums.emplace_back( HitNumber{ Vei2( cam.AbsoluteToRelative(
		// 	enemy->GetPos() ) ) * Camera::tileSize +
		// 	Vei2{ Camera::tileSize / 2,10 },dmg } );

		msgLog.Log( curCard.GetName() + " did " +
			std::to_string( dmg ) + " damage to " +
			enemy->GetName() + "!" );

		if( enemy->IsExpl() )
		{
			msgLog.Log( enemy->GetName() + " has been defeated!" );
		}
	}
	else
	{
		msgLog.Log( curCard.GetName() + " missed!" );
	}
	
	deck.Discard( selectedCard );
	curCardAnim = nullptr;

	selectedCard = -1;
}

void CardHandler::DeselectCard()
{
	selectedCard = -1;
}

bool CardHandler::HasSelectedCard() const
{
	return( selectedCard != -1 );
}

bool CardHandler::DoneWithTurn() const
{
	return( doneWithTurn );
}

const std::vector<std::unique_ptr<Card>>& CardHandler::GetCards() const
{
	return( deck.GetCards() );
}
