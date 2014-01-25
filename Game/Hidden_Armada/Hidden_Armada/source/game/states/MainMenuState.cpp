#include "MainMenuState.h"
#include "../../engine/renderer/D3D9Handler.h"
#include "../../engine/renderer/TextureManager.h"

MainMenuState::MainMenuState( void )
{
	m_TestImg = -1;
}

bool MainMenuState::Initialize( WinApp* _app )
{
	m_App = _app;

	m_TestImg = TextureManager::GetInstance()->LoadTexture(L"assets/textures/HollowDev.png");

	return true;
}

void MainMenuState::Release( void )
{

}

void MainMenuState::Render( void )
{
	D3D9Handler::m_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 25, 25), 1.0f, 0);
	D3D9Handler::m_Device->BeginScene();
	{
		D3D9Handler::m_Sprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			if(m_TestImg != -1)
				TextureManager::GetInstance()->Draw(m_TestImg,0,0);
		}
		D3D9Handler::m_Sprite->End();
	}
	D3D9Handler::m_Device->EndScene();
	D3D9Handler::m_Device->Present(0,0,0,0);
}

void MainMenuState::Update( float _dt )
{

}

bool MainMenuState::Input( void )
{
	return true;
}
