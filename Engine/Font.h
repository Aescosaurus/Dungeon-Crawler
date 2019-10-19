#pragma once

#include <string>
#include <vector>
#include "Rect.h"
#include "Surface.h"
#include "Graphics.h"
#include "SpriteEffect.h"

class Font
{
public:
	Font( const std::string& sheet )
		:
		fontSheet( sheet,Vei2{ 1,1 } )
	{
		const int rowHeight = fontSheet.GetHeight();
		glyphRects.emplace_back( RectI{ 0,0,0,rowHeight } );
		for( int x = 0; x < fontSheet.GetWidth(); ++x )
		{
			if( fontSheet.GetPixel( x,0 ) == Colors::Magenta )
			{
				glyphRects.back().right = x - 1;
				glyphRects.emplace_back( RectI{
					x + 1,0,0,rowHeight } );
			}
		}

		// static constexpr int expandSize = 2;
		// fontSheet = fontSheet.GetExpandedBy( Vei2{
		// 	expandSize,expandSize } );
		// for( auto& rect : glyphRects )
		// {
		// 	rect.left *= expandSize;
		// 	rect.right *= expandSize;
		// 	rect.bottom *= expandSize;
		// }
	}

	void DrawText( const std::string& text,
		const Vei2& loc,Color textCol,Graphics& gfx ) const
	{
		Vei2 drawPos = loc;
		for( auto c : text )
		{
			if( c == '\n' )
			{
				drawPos.x = loc.x;
				drawPos.y += fontSheet.GetHeight() + lineHeight;
			}
			else
			{
				const auto& glyphRect = GetGlyphRect( c );

				gfx.DrawSprite( drawPos.x,drawPos.y,
					fontSheet,glyphRect,SpriteEffect::Substitution{
						Colors::White,textCol } );

				drawPos.x += glyphRect.GetWidth();
			}
		}
	}

	int CalculateTextWidth( const std::string& text ) const
	{
		int width = 0;
		for( char c : text )
		{
			const auto& glyphRect = GetGlyphRect( c );
			width += glyphRect.GetWidth();
		}
		return( width );
	}
private:
	const RectI& GetGlyphRect( char c ) const
	{
		const int glyphIndex = c - ' ';
		const auto& glyphRect = glyphRects[glyphIndex];
		return( glyphRect );
	}
private:
	Surface fontSheet;
	std::vector<RectI> glyphRects;
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
	static constexpr int lineHeight = 5;
};