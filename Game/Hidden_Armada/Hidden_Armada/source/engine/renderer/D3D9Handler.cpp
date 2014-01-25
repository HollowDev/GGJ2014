#include "D3D9Handler.h"
#include "../memory_macros.h"

HWND						D3D9Handler::m_hWnd;
HINSTANCE					D3D9Handler::m_hInstance;
D3DCAPS9					D3D9Handler::m_Caps;
D3DPRESENT_PARAMETERS		D3D9Handler::m_PP;
D3DDISPLAYMODE				D3D9Handler::m_DisplayMode;
IDirect3D9*					D3D9Handler::m_Object		= nullptr;
IDirect3DDevice9*			D3D9Handler::m_Device		= nullptr;
ID3DXSprite*				D3D9Handler::m_Sprite		= nullptr;
ID3DXLine*					D3D9Handler::m_Line			= nullptr;
BOOL						D3D9Handler::m_IsWindowed;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Cleans up resources
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void D3D9Handler::Release()
{
	SAFE_RELEASE( m_Device );
	SAFE_RELEASE( m_Object );
	SAFE_RELEASE( m_Sprite );
	SAFE_RELEASE( m_Line );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Initializes Direct3D.
Parameters:
[in] hWnd - Handle to the window
[in] windowed - TRUE for windowed mode, FALSE for fullscreen mode
Returns: TRUE on success. FALSE on failure
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
BOOL D3D9Handler::Initialize(HWND hWnd, BOOL windowed)
{
	m_IsWindowed = windowed;
	m_hWnd = hWnd;
	Release();

	// Create the object
	m_Object = Direct3DCreate9(D3D_SDK_VERSION);

	m_Object->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &m_DisplayMode );
	m_Object->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_Caps );

	if( !BuildPresentParameters() )
	{
		SAFE_RELEASE( m_Object );
		return FALSE;
	}

	// Create the Device
	m_Object->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_PP, &m_Device );
	
	// Create the sprite
	D3DXCreateSprite(m_Device, &m_Sprite);

	// Create the line
	D3DXCreateLine(m_Device, &m_Line);
	m_Line->SetAntialias(TRUE);
	m_Line->SetWidth(1.0f);
	
	return TRUE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Builds the D3DPRESENT_PARAMETERS structure.
Returns: TRUE on success. FALSE on failure
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
BOOL D3D9Handler::BuildPresentParameters()
{
	ZeroMemory( &m_PP, sizeof(m_PP) );
	D3DFORMAT adapterFormat = (m_IsWindowed) ? m_DisplayMode.Format : D3DFMT_X8R8G8B8;
    if ( SUCCEEDED( m_Object->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, adapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24S8 ) ) )
    {
        m_PP.AutoDepthStencilFormat = D3DFMT_D24S8;
    }
    else if ( SUCCEEDED( m_Object->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, adapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24X8 ) ) )
    {
        m_PP.AutoDepthStencilFormat = D3DFMT_D24X8;
    }
    else if ( SUCCEEDED( m_Object->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, adapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16 ) ) )
    {
        m_PP.AutoDepthStencilFormat = D3DFMT_D16;
    }
	else
	{
		return FALSE;
	}

	m_PP.BackBufferWidth			= (m_IsWindowed) ? 0 : m_DisplayMode.Width;
	m_PP.BackBufferHeight           = (m_IsWindowed) ? 0 : m_DisplayMode.Height;
	m_PP.BackBufferFormat           = adapterFormat;
	m_PP.BackBufferCount            = 1;
	m_PP.MultiSampleType            = D3DMULTISAMPLE_NONE;
	m_PP.MultiSampleQuality         = 0;
	m_PP.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	m_PP.hDeviceWindow              = m_hWnd;
	m_PP.Windowed                   = m_IsWindowed;
	m_PP.EnableAutoDepthStencil     = TRUE; 
	m_PP.FullScreen_RefreshRateInHz = (m_IsWindowed) ? 0 : m_DisplayMode.RefreshRate;
	m_PP.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	return TRUE;
}

void D3D9Handler::DrawRect(RECT _area, unsigned char _r, unsigned char _g, unsigned char _b)
{
	D3DRECT d3dRect;
	d3dRect.x1 = _area.left;
	d3dRect.y1 = _area.top;
	d3dRect.x2 = _area.right;
	d3dRect.y2 = _area.bottom;

	m_Device->Clear(1, &d3dRect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(_r, _g, _b), 1.0f, 0);
}

void D3D9Handler::DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, unsigned char _r, unsigned char _g, unsigned char _b)
{
	D3DXVECTOR2 verts[2];

	verts[0].x = (float)p1.x;
	verts[0].y = (float)p1.y;
	verts[1].x = (float)p2.x;
	verts[1].y = (float)p2.y;

	m_Line->Draw(verts, 2, D3DCOLOR_XRGB(_r, _g, _b));
}