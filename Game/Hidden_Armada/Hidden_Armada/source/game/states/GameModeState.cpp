#include "GameModeState.h"
#include "../../engine/renderer/D3D9Handler.h"
#include "../../engine/renderer/TextureManager.h"

GameModeState::GameModeState( void )
{

}

bool GameModeState::Initialize( WinApp* _app )
{
	m_App = _app;

	return true;
}

void GameModeState::Release( void )
{

}

void GameModeState::Render( void )
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

void GameModeState::Update( float _dt )
{

}

bool GameModeState::Input( void )
{
	return true;
}
