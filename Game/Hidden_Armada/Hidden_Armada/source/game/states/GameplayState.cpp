#include "GameplayState.h"
#include "../../engine/app/WinApp.h"
#include "../../engine/renderer/D3D9Handler.h"
#include "../../engine/renderer/TextureManager.h"

#include "../ObjectManager.h"
#include "../ObjectFactory.h"
#include "../AIManager.h"

#include "../../engine/app/StateSystem.h"
#include "MainMenuState.h"

#include "../objects/EnemyShip.h"

GameplayState::GameplayState( void )
{

}

bool GameplayState::Initialize( WinApp* _app )
{
	m_App = _app;

	m_Input = new InputController();
	m_Input->Initialize(m_App->GetHWND(), m_App->GetHINSTANCE());

	int p1ID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/ships/Playership3.png");
	int weaponID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/weapons/machinegun2.png");
	RECT source = {0,0,128,128};

	m_Player1 = new PlayerShip();
	m_Player1->Initialize("assets/data/ships/ship1.txt",D3DXVECTOR2(400,400),weaponID, m_Input);
	m_Player1->SetImgID(p1ID);
	m_Player1->SetImgSource(source);

	ObjectManager::GetInstance()->AddObject(m_Player1,2);

	ObjectFactory::GetInstance()->Initialize();
	int asteroid = TextureManager::GetInstance()->LoadTexture(L"assets/textures/asteroids/asteroid001.png");
	for(int i = 0; i < 100; ++i)
	{
		ObjectFactory::GetInstance()->Create(&m_AsteroidTest[i], Entity_Asteroid);
		((Asteroids*)m_AsteroidTest[i])->SetImgID(asteroid);
	}

	int weapon2ID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/playershipeffects/Missile.png");

	int smallEnemyID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/enemyships/enemyship1.png");
	int mediumEnemyID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/enemyships/enemyship2.png");
	int largeEnemyID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/enemyships/enemyship3.png");
	AIManager::GetInstance()->Initialize(m_Player1,smallEnemyID,mediumEnemyID,largeEnemyID,weaponID);

	//RECT enemySource = {0,0,128,128};
	//int enemyShipID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/enemyships/enemyship2.png");
	//for(unsigned int i = 0; i < 100; ++i)
	//{
	//	AIManager::GetInstance()->SpawnEnemy( D3DXVECTOR2(i*50,200) );
	//}
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
	if(m_Input->Input_Cancel())
	{
		StateSystem::GetInstance()->ChangeState(new MainMenuState());
	}

	return true;
}
