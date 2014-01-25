#ifndef _D3D9HANDLER_H_
#define _D3D9HANDLER_H_

#include "../directx9.h"

class D3D9Handler
{ 
public:
	static HWND						m_hWnd;
	static HINSTANCE				m_hInstance;
	static D3DCAPS9					m_Caps;
	static D3DPRESENT_PARAMETERS	m_PP;
	static D3DDISPLAYMODE			m_DisplayMode;
	static IDirect3D9*				m_Object;
	static IDirect3DDevice9*		m_Device;
	static ID3DXSprite*				m_Sprite;
	static ID3DXLine*				m_Line;
	static BOOL						m_IsWindowed;

	D3D9Handler( void );
	~D3D9Handler( void ) { Release(); }
	static BOOL Initialize( HWND hWnd, BOOL windowed );
	static void Release( void );
	static BOOL BuildPresentParameters( void );

	static void DrawRect(RECT _area, unsigned char _r, unsigned char _g, unsigned char _b);
	static void DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, unsigned char _r, unsigned char _g, unsigned char _b);
};

#endif