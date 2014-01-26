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
#include "../AssetManager.h"

GameplayState::GameplayState( void )
{

}

bool GameplayState::Initialize( WinApp* _app )
{
	m_App = _app;

	m_Input = new InputController();
	m_Input->Initialize(m_App->GetHWND(), m_App->GetHINSTANCE());

	int p1ID = AssetManager::GetInstance()->GetAsset(Asset_PlayerShip02);
	int weaponID = AssetManager::GetInstance()->GetAsset(Asset_WeaponLaser03);
	RECT source = {0,0,128,128};

	m_Camera = new Camera();

	m_Player1 = new PlayerShip();
	m_Player1->Initialize("assets/data/ships/ship1.txt",D3DXVECTOR2(400,400),weaponID, m_Input, m_Camera);
	m_Player1->SetImgID(p1ID);
	m_Player1->SetImgSource(source);

	m_Camera->Initialize(m_Player1);

	ObjectManager::GetInstance()->AddObject(m_Player1,2);

	ObjectFactory::GetInstance()->Initialize();
	int asteroid[4] =
	{
		AssetManager::GetInstance()->GetAsset(Asset_Asteroid01),
		AssetManager::GetInstance()->GetAsset(Asset_Asteroid02),
		AssetManager::GetInstance()->GetAsset(Asset_Asteroid03),
		AssetManager::GetInstance()->GetAsset(Asset_Asteroid04)		
	};
	for(int i = 0; i < 100; ++i)
	{
		ObjectFactory::GetInstance()->Create(&m_AsteroidTest[i], Entity_Asteroid);
		((Asteroids*)m_AsteroidTest[i])->SetImgID(asteroid[rand()%4]);
	}

	AIManager::GetInstance()->Initialize(m_Player1);

	//RECT enemySource = {0,0,128,128};
	//int enemyShipID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/enemyships/enemyship2.png");
	//for(unsigned int i = 0; i < 100; ++i)
	//{
	//	AIManager::GetInstance()->SpawnEnemy( D3DXVECTOR2(i*50,200) );
	//}
	m_Font.Initialize(AssetManager::GetInstance()->GetAsset(Asset_Font),5*2,7*2,3,32);
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
			ObjectManager::GetInstance()->Render(-(int)m_Camera->GetPos().x, -(int)m_Camera->GetPos().y);

			m_Font.Print("test this shit, mother fucker.", 10, 10, D3DCOLOR_ARGB(255,255,255,255));
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

	m_Camera->Update(_dt, m_Player1, m_App);
}

bool GameplayState::Input( void )
{
	if(m_Input->Input_Cancel())
	{
		StateSystem::GetInstance()->ChangeState(new MainMenuState());
	}

	return true;
}
