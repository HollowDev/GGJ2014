#include "CreditsState.h"
#include "../../engine/renderer/D3D9Handler.h"
#include "../../engine/renderer/TextureManager.h"

CreditsState::CreditsState( void )
{

}

bool CreditsState::Initialize( WinApp* _app )
{
	m_App = _app;

	return true;
}

void CreditsState::Release( void )
{

}

void CreditsState::Render( void )
{
	D3D9Handler::m_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 25, 25), 1.0f, 0);
	D3D9Handler::m_Device->BeginScene();
	{
		D3D9Handler::m_Sprite->Begin( D3DXSPRITE_ALPHABLEND );
		{

		}
		D3D9Handler::m_Sprite->End();
	}
	D3D9Handler::m_Device->EndScene();
	D3D9Handler::m_Device->Present(0,0,0,0);
}

void CreditsState::Update( float _dt )
{

}

bool CreditsState::Input( void )
{
	return true;
}
