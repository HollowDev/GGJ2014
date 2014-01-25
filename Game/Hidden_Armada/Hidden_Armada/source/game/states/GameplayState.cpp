#include "GameplayState.h"
#include "../../engine/app/WinApp.h"
#include "../../engine/renderer/D3D9Handler.h"
#include "../../engine/renderer/TextureManager.h"

#include "../ObjectManager.h"
#include "../ObjectFactory.h"

#include "../../engine/app/StateSystem.h"
#include "MainMenuState.h"

GameplayState::GameplayState( void )
{

}

bool GameplayState::Initialize( WinApp* _app )
{
	m_App = _app;

	int p1ID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/ships/Playership3.png");
	int weaponID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/weapons/machinegun2.png");
	RECT source = {0,0,128,128};

	m_Player1 = new Ship();
	m_Player1->Initialize("assets/data/ships/ship1.txt",D3DXVECTOR2(0,0),weaponID);
	m_Player1->SetImgID(p1ID);
	m_Player1->SetImgSource(source);

	p1ID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/ships/Playership2.png");
	m_Player2 = new Ship();
	m_Player2->Initialize("assets/data/ships/ship1.txt",D3DXVECTOR2(0,0),weaponID);
	m_Player2->SetImgID(p1ID);
	m_Player2->SetImgSource(source);

	ObjectManager::GetInstance()->AddObject(m_Player1,2);
	ObjectManager::GetInstance()->AddObject(m_Player2,2);

	ObjectFactory::GetInstance()->Initialize();
	int asteroid = TextureManager::GetInstance()->LoadTexture(L"assets/textures/asteroids/asteroid001.png");
	for(int i = 0; i < 100; ++i)
	{
		ObjectFactory::GetInstance()->Create(&m_AsteroidTest[i], Entity_Asteroid);
		((Asteroids*)m_AsteroidTest[i])->SetImgID(asteroid);
	}

	weaponID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/playershipeffects/Missile.png");

	return true;
}

void GameplayState::Release( void )
{

}

void GameplayState::Render( void )
{
	D3D9Handler::m_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
	D3D9Handler::m_Device->BeginScene();
	{
		D3D9Handler::m_Sprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			ObjectManager::GetInstance()->Render(0,0);
		}
		D3D9Handler::m_Sprite->End();
	}
	D3D9Handler::m_Device->EndScene();
	D3D9Handler::m_Device->Present(0,0,0,0);
}

void GameplayState::Update( float _dt )
{
	ObjectManager::GetInstance()->Update(_dt);
	ObjectManager::GetInstance()->CheckCollision();

	ObjectFactory::GetInstance()->ProcessDestroy();
}

bool GameplayState::Input( void )
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(m_App->GetHWND(),&mouse);
	m_Player1->RotateWeaponToMouse((int)mouse.x,(int)mouse.y);

	if(GetAsyncKeyState('W'))
	{
		m_Player1->SetVel(m_Player1->GetVel() + D3DXVECTOR2(0,-m_Player1->GetMaxSpeed()));
	}
	else if(GetAsyncKeyState('S'))
	{
		m_Player1->SetVel(m_Player1->GetVel() + D3DXVECTOR2(0,m_Player1->GetMaxSpeed()));
	}

	if(GetAsyncKeyState('A'))
	{
		m_Player1->SetVel(m_Player1->GetVel() + D3DXVECTOR2(-m_Player1->GetMaxSpeed(),0));
	}
	else if(GetAsyncKeyState('D'))
	{
		m_Player1->SetVel(m_Player1->GetVel() + D3DXVECTOR2(m_Player1->GetMaxSpeed(),0));
	}

	if(GetAsyncKeyState(VK_UP))
	{
		m_Player2->SetVel(m_Player2->GetVel() + D3DXVECTOR2(0,-m_Player2->GetMaxSpeed()));
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		m_Player2->SetVel(m_Player2->GetVel() + D3DXVECTOR2(0,m_Player2->GetMaxSpeed()));
	}

	if(GetAsyncKeyState(VK_LEFT))
	{
		m_Player2->SetVel(m_Player2->GetVel() + D3DXVECTOR2(-m_Player2->GetMaxSpeed(),0));
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		m_Player2->SetVel(m_Player2->GetVel() + D3DXVECTOR2(m_Player2->GetMaxSpeed(),0));
	}

	if(GetAsyncKeyState(VK_ESCAPE))
	{
		StateSystem::GetInstance()->ChangeState(new MainMenuState());
		while(GetAsyncKeyState(VK_ESCAPE));
	}

	return true;
}
