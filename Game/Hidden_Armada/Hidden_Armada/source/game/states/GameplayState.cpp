#include "GameplayState.h"
#include "../../engine/app/WinApp.h"
#include "../../engine/renderer/D3D9Handler.h"
#include "../../engine/renderer/TextureManager.h"
#include "MainMenuState.h"
#include "../../engine/app/StateSystem.h"

GameplayState::GameplayState( void )
{

}

bool GameplayState::Initialize( WinApp* _app )
{
	m_App = _app;

	int p1ID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/ships/Playership1.png");
	RECT source = {0,0,64,64};
	m_Player1.Initialize(p1ID,source,32,D3DXVECTOR2(0,0),50,30);

	return true;
}

void GameplayState::Release( void )
{

}

void GameplayState::Render( void )
{
	D3D9Handler::m_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(25, 25, 25), 1.0f, 0);
	D3D9Handler::m_Device->BeginScene();
	{
		D3D9Handler::m_Sprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			m_Player1.Render(0,0);
		}
		D3D9Handler::m_Sprite->End();
	}
	D3D9Handler::m_Device->EndScene();
	D3D9Handler::m_Device->Present(0,0,0,0);
}

void GameplayState::Update( float _dt )
{
	m_Player1.Update(_dt);
}

bool GameplayState::Input( void )
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(m_App->GetHWND(),&mouse);
	m_Player1.RotateToMouse((int)mouse.x,(int)mouse.y);

	if(GetAsyncKeyState(VK_ESCAPE))
	{
		StateSystem::GetInstance()->ChangeState(new MainMenuState());
		while(GetAsyncKeyState(VK_ESCAPE));
	}

	return true;
}
