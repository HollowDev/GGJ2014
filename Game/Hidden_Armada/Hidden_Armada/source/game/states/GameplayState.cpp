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

	int p1ID = AssetManager::GetInstance()->GetAsset(Asset_PlayerShip03);
	int weaponID = AssetManager::GetInstance()->GetAsset(Asset_WeaponMissle03);
	RECT source = {0,0,128,128};

	m_Camera = new Camera();

	m_Player1 = new PlayerShip();
	m_Player1->Initialize("assets/data/ships/ship1.txt",D3DXVECTOR2(400,400),weaponID, m_Input, m_Camera);
	m_Player1->SetImgID(p1ID);
	m_Player1->SetImgSource(source);
	m_Player1->SetMaxHP(6);
	m_Player1->SetHP(6);

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
	//for(int i = 0; i < 100; ++i)
	//{
	//	ObjectFactory::GetInstance()->Create(&m_AsteroidTest[i], Entity_Asteroid);
	//	((Asteroids*)m_AsteroidTest[i])->SetImgID(asteroid[rand()%4]);
	//}

	AIManager::GetInstance()->Initialize(m_Player1);

	IEntity* newShield;
	ObjectFactory::GetInstance()->Create(&newShield, Entity_Shield);
	m_Player1->SetShield((Shield*)newShield);
	m_Player1->GetShield()->SetMaxShield(15);
	m_Player1->GetShield()->SetCurrShield(15);

	m_AsteroidManager.Initialize(4,4,30,m_Player1);

	//RECT enemySource = {0,0,128,128};
	//int enemyShipID = TextureManager::GetInstance()->LoadTexture(L"assets/textures/enemyships/enemyship2.png");
	//for(unsigned int i = 0; i < 100; ++i)
	//{
	//	AIManager::GetInstance()->SpawnEnemy( D3DXVECTOR2(i*50,200) );
	//}
	m_Font.Initialize(AssetManager::GetInstance()->GetAsset(Asset_Font),5*2,7*2,3,32);

	m_HudBackgroundID = AssetManager::GetInstance()->GetAsset(Asset_HudOutline);
	m_ShieldBarID = AssetManager::GetInstance()->GetAsset(Asset_HudShieldBar);
	m_HealthBarID = AssetManager::GetInstance()->GetAsset(Asset_HudHealthNotch);

	m_HudBackground.color = D3DCOLOR_ARGB(150, 255, 255, 255);
	m_HudBackground.posX = 25;
	m_HudBackground.posY = m_App->GetHeight() - 175;

	m_ShieldBar.color = D3DCOLOR_ARGB(150, 255, 255, 255);
	m_ShieldBar.posX = 177;
	m_ShieldBar.posY = m_App->GetHeight() - 95;
	m_ShieldBar.sourceRect.left = 2;
	m_ShieldBar.sourceRect.top = 1;
	m_ShieldBar.sourceRect.right = 55;
	m_ShieldBar.sourceRect.bottom = 17;

	m_HealthBar1.color = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_HealthBar1.posX = 177;
	m_HealthBar1.posY = m_App->GetHeight() - 63;

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
			m_AsteroidManager.Render(-(int)m_Camera->GetPos().x, -(int)m_Camera->GetPos().y);

			ObjectManager::GetInstance()->Render(-(int)m_Camera->GetPos().x, -(int)m_Camera->GetPos().y);

			TextureManager::GetInstance()->Draw(m_HudBackgroundID, m_HudBackground.posX, m_HudBackground.posY, 1.15f, 1.15f, nullptr, 0.0f, 0.0f, 0.0f, m_HudBackground.color);
			TextureManager::GetInstance()->Draw(m_ShieldBarID, m_ShieldBar.posX, m_ShieldBar.posY, 1.15f, 1.15f, &m_ShieldBar.sourceRect, 0.0f, 0.0f, 0.0f, m_ShieldBar.color);
			for(int i = 0; i < m_Player1->GetHP(); ++i)
			{
				TextureManager::GetInstance()->Draw(m_HealthBarID, m_HealthBar1.posX + (17 * i), m_HealthBar1.posY, 1.15f, 1.15f, nullptr, 0.0f, 0.0f, 0.0f, m_HealthBar1.color);
			}

			char score[256];
			sprintf_s(score, "%i", m_Player1->GetScore());
			m_Font.Print(score, 155, m_App->GetHeight() - 131, D3DCOLOR_ARGB(255, 255, 255, 255));
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

	m_Camera->Update(_dt, m_Player1, m_App, m_AsteroidManager.GetRows(), m_AsteroidManager.GetCols());

	m_AsteroidManager.Update(_dt);
}

bool GameplayState::Input( void )
{
	if(m_Input->Input_Cancel())
	{
		StateSystem::GetInstance()->ChangeState(new MainMenuState());
	}

	return true;
}
