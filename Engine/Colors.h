/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Colors.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once

class Color
{
public:
	unsigned int dword;
public:
	constexpr Color() : dword() {}
	constexpr Color( const Color& col )
		:
		dword( col.dword )
	{}
	constexpr Color( unsigned int dw )
		:
		dword( dw )
	{}
	constexpr Color( unsigned char x,unsigned char r,unsigned char g,unsigned char b )
		:
		dword( (x << 24u) | (r << 16u) | (g << 8u) | b )
	{}
	constexpr Color( unsigned char r,unsigned char g,unsigned char b )
		:
		dword( (r << 16u) | (g << 8u) | b )
	{}
	constexpr Color( Color col,unsigned char x )
		:
		Color( (x << 24u) | col.dword )
	{}
	Color& operator =( Color color )
	{
		dword = color.dword;
		return *this;
	}
	constexpr bool operator==( const Color& rhs )
	{
		return( dword == rhs.dword );
	}
	constexpr bool operator!=( const Color& rhs )
	{
		return( !( *this == rhs ) );
	}
	constexpr unsigned char GetX() const
	{
		return dword >> 24u;
	}
	constexpr unsigned char GetA() const
	{
		return GetX();
	}
	constexpr unsigned char GetR() const
	{
		return (dword >> 16u) & 0xFFu;
	}
	constexpr unsigned char GetG() const
	{
		return (dword >> 8u) & 0xFFu;
	}
	constexpr unsigned char GetB() const
	{
		return dword & 0xFFu;
	}
	void SetX( unsigned char x )
	{
		dword = (dword & 0xFFFFFFu) | (x << 24u);
	}
	void SetA( unsigned char a )
	{
		SetX( a );
	}
	void SetR( unsigned char r )
	{
		dword = (dword & 0xFF00FFFFu) | (r << 16u);
	}
	void SetG( unsigned char g )
	{
		dword = (dword & 0xFFFF00FFu) | (g << 8u);
	}
	void SetB( unsigned char b )
	{
		dword = (dword & 0xFFFFFF00u) | b;
	}
};

namespace Colors
{
	static constexpr Color MakeRGB( unsigned char r,unsigned char g,unsigned char b )
	{
		return (r << 16) | (g << 8) | b;
	}
	// static constexpr Color White = MakeRGB( 255u,255u,255u );
	// static constexpr Color Black = MakeRGB( 0u,0u,0u );
	// static constexpr Color Gray = MakeRGB( 0x80u,0x80u,0x80u );
	// static constexpr Color LightGray = MakeRGB( 0xD3u,0xD3u,0xD3u );
	// static constexpr Color DarkGray = MakeRGB( 0x40u,0x40u,0x40u );
	// static constexpr Color Red = MakeRGB( 255u,0u,0u );
	// static constexpr Color Green = MakeRGB( 0u,255u,0u );
	// static constexpr Color Blue = MakeRGB( 0u,0u,255u );
	// static constexpr Color Yellow = MakeRGB( 255u,255u,0u );
	// static constexpr Color Cyan = MakeRGB( 0u,255u,255u );
	// static constexpr Color Magenta = MakeRGB( 255u,0u,255u );

	static constexpr Color White = MakeRGB( 255u,255u,255u );
	static constexpr Color Black = MakeRGB( 0u,0u,0u );
	static constexpr Color Magenta = MakeRGB( 255u,0u,255u );

	static constexpr Color Green1 = MakeRGB( 0u,255u,77u );
	static constexpr Color Green2 = MakeRGB( 0u,235u,71u );
	static constexpr Color Green3 = MakeRGB( 0u,181u,51u );
	static constexpr Color Purple1 = MakeRGB( 255u,0u,231u );
	static constexpr Color Purple2 = MakeRGB( 194u,0u,224u );
	static constexpr Color Purple3 = MakeRGB( 147u,0u,246u );
	static constexpr Color Purple4 = MakeRGB( 187u,0u,161u );
	static constexpr Color Purple5 = MakeRGB( 240u,0u,99u );
	static constexpr Color Orange1 = MakeRGB( 255u,143u,57u );
	static constexpr Color Orange2 = MakeRGB( 255u,87u,37u );
	static constexpr Color Orange3 = MakeRGB( 184u,60u,23u );
	static constexpr Color Orange4 = MakeRGB( 239u,18u,36u );
	static constexpr Color Blue1 = MakeRGB( 0u,255u,253u );
	static constexpr Color Blue2 = MakeRGB( 0u,235u,175u );
	static constexpr Color Blue3 = MakeRGB( 0u,181u,177u );
	static constexpr Color Blue4 = MakeRGB( 0u,175u,227u );
	static constexpr Color Blue5 = MakeRGB( 24u,127u,247u );
	static constexpr Color Black1 = MakeRGB( 17u,17u,17u );
	static constexpr Color Gray1 = MakeRGB( 51u,51u,46u );
	static constexpr Color Gray2 = MakeRGB( 95u,85u,85u );
	static constexpr Color Gray3 = MakeRGB( 62u,66u,69u );
	static constexpr Color Gray4 = MakeRGB( 85u,91u,94u );
	static constexpr Color LightGray1 = MakeRGB( 145u,154u,160u );
	static constexpr Color LightGray2 = MakeRGB( 167u,179u,185u );
	static constexpr Color White1 = MakeRGB( 238u,238u,238u );
}