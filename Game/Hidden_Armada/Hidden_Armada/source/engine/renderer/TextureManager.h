/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Title : TextureManager.h
Author : Evan Wright

Description : A wrapper to allow easy 2D rendering, using the DX9 Sprite system. 
			 It loads and manages all textures and allows use of textures with a reference 
			 to an integer. MAGIC

Created :  01/24/2014
Modified : 01/24/2014
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include "../directx9.h"

#include <tchar.h>
#include <vector>
using std::vector;

class TextureManager
{
	struct Texture
	{
		TCHAR				filename[_MAX_PATH];
		int					ref;
		LPDIRECT3DTEXTURE9	texture;
		int					width;
		int					height;
		Texture(void)
		{
			filename[0] = '\0';
			ref = 0;
			texture = nullptr;
			width = 0;
			height = 0;
		};
	};

	vector<Texture>			m_Textures;
	LPDIRECT3DDEVICE9		m_Device;
	LPD3DXSPRITE			m_Sprite;
	static TextureManager	m_Instance;

	TextureManager( void );
	~TextureManager( void ) { Release(); }
public:
	static TextureManager* GetInstance( void ) { return &m_Instance; }

	bool Initialize( LPDIRECT3DDEVICE9 _device, LPD3DXSPRITE _sprite );
	void Release( void );

	int LoadTexture( const TCHAR* _filename, DWORD _colorkey = 0 );
	void UnloadTexture( int _id );

	int GetTextureWidth( int _id );
	int GetTextureHeight( int _id );

	//bool Draw( int _id, int _x, int _y, float _scaleX = 1.0f, float _scaleY = 1.0f,
	//		RECT* _section = nullptr, float _rotCenterX = 0.0f, float _rotCenterY = 0.0f,
	//		float _rot = 0.0f, int _r = 255, int _g = 255, int _b = 255, int _a = 255 );
	bool Draw( int _id, int _x, int _y, float _scaleX = 1.0f, float _scaleY = 1.0f,
			RECT* _section = nullptr, float _rotCenterX = 0.0f, float _rotCenterY = 0.0f,
			float _rot = 0.0f, DWORD _color = 0xFFFFFFFF );
};

#endif