/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
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
#include "ChiliWin.h"
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"
#include "Rect.h"
#include "Surface.h"
#include "Matrix.h"

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel( int x,int y,Color c );
	void DrawRect( int x,int y,int width,int height,Color c );
	void DrawRectDim( int x1,int y1,int x2,int y2,Color c );
	void DrawRectDim( const RectI& rect,Color c );
	void DrawRectSafe( int x,int y,int width,int height,Color c );
	template<typename Effect>
	void DrawSprite( int x,int y,const Surface& spr,
		Effect eff,const Matrix& mat = Matrix::Up() )
	{
		DrawSprite( x,y,spr,spr.GetRect(),eff,mat );
	}
	template<typename Effect>
	void DrawSprite( int x,int y,const Surface& spr,
		const RectI& srcRect,Effect eff,
		const Matrix& mat = Matrix::Up() )
	{
		DrawSprite( x,y,spr,srcRect,GetScreenRect(),eff,mat );
	}
	template<typename Effect>
	void DrawSprite( int x,int y,const Surface& spr,
		RectI srcRect,const RectI& clip,Effect eff,
		const Matrix& mat = Matrix::Up() )
	{
		assert( srcRect.left >= 0 );
		assert( srcRect.right <= spr.GetWidth() );
		assert( srcRect.top >= 0 );
		assert( srcRect.bottom <= spr.GetHeight() );

		assert( srcRect.left < srcRect.right );
		assert( srcRect.top < srcRect.bottom );

		// Sprite clipping.
		if( x < clip.left )
		{
			srcRect.left += clip.left - x;
			x = clip.left;
		}
		if( y < clip.top )
		{
			srcRect.top += clip.top - y;
			y = clip.top;
		}
		if( x + srcRect.GetWidth() > clip.right )
		{
			srcRect.right -= x + srcRect.GetWidth() - clip.right;
		}
		if( y + srcRect.GetHeight() > clip.bottom )
		{
			srcRect.bottom -= y + srcRect.GetHeight() - clip.bottom;
		}

		const Vec2 center = Vec2{ float( x + srcRect.GetWidth() / 2 ),
			float( y + srcRect.GetHeight() / 2 ) };

		for( int sy = srcRect.top; sy < srcRect.bottom; ++sy )
		{
			for( int sx = srcRect.left; sx < srcRect.right; ++sx )
			{
				if( mat == Matrix::Up() )
				{
					eff( spr.GetPixel( sx,sy ),
						x + sx - srcRect.left,
						y + sy - srcRect.top,
						*this );
				}
				else
				{
					Vec2 drawPos = Vec2{ float( x + sx - srcRect.left ),
						float( y + sy - srcRect.top ) };
					drawPos -= center;
					drawPos = mat * drawPos;
					drawPos += center;
					eff( spr.GetPixel( sx,sy ),
						int( drawPos.x ),int( drawPos.y ),
						*this );
				}
			}
		}
	}
	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;
public:
	static RectI GetScreenRect();
	static constexpr int ScreenWidth = 1920 / 2;
	static constexpr int ScreenHeight = 1080 / 2;
};