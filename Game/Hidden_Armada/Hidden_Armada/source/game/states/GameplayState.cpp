#include "GameplayState.h"
#include "../../engine/app/WinApp.h"
#include "../../engine/renderer/D3D9Handler.h"
#include "../../engine/renderer/TextureManager.h"

#include "../ObjectManager.h"
#include "../ObjectFactory.h"

#include "../../engine/app/StateSystem.h"
#include "MainMenuState.h"

#include "../objects/EnemyShip.h"

GameplayState::GameplayState( void )
{

}

bool GameplayState::Initialize( WinApp* _app )
{
	m_App = _app;

	int p1ID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/ships/Playership3.png");
	int weaponID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/weapons/machinegun2.png");
	RECT source = {0,0,128,128};

	m_Player1 = new PlayerShip();
	m_Player1->Initialize("assets/data/ships/ship1.txt",D3DXVECTOR2(400,400),weaponID);
	m_Player1->SetImgID(p1ID);
	m_Player1->SetImgSource(source);

	ObjectManager::GetInstance()->AddObject(m_Player1,2);

	ObjectFactory::GetInstance()->Initialize();
	int asteroid = TextureManager::GetInstance()->LoadTexture(L"assets/textures/asteroids/asteroid001.png");
	//for(int i = 0; i < 100; ++i)
	//{
	//	ObjectFactory::GetInstance()->Create(&m_AsteroidTest[i], Entity_Asteroid);
	//	((Asteroids*)m_AsteroidTest[i])->SetImgID(asteroid);
	//}

	int weapon2ID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/playershipeffects/Missile.png");

	RECT enemySource = {0,0,128,128};

	int enemyShipID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/enemyships/enemyship2.png");
	for(unsigned int i = 0; i < 100; ++i)
	{
		ObjectFactory::GetInstance()->Create(&m_EnemyShip[i], Entity_EnemyShip);
		((EnemyShip*)m_EnemyShip[i])->Initialize("assets/data/ships/ship1.txt",D3DXVECTOR2(i*50,300),weaponID);
		((EnemyShip*)m_EnemyShip[i])->SetImgID(enemyShipID);
		((EnemyShip*)m_EnemyShip[i])->SetImgSource(enemySource);
		((EnemyShip*)m_EnemyShip[i])->SetImgCenter(D3DXVECTOR2(64,64));
		((EnemyShip*)m_EnemyShip[i])->SetSize(20);
		((EnemyShip*)m_EnemyShip[i])->SetTarget(m_Player1);
	}
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

	if(GetAsyncKeyState(VK_ESCAPE))
	{
		StateSystem::GetInstance()->ChangeState(new MainMenuState());
		while(GetAsyncKeyState(VK_ESCAPE));
	}

	return true;
}
