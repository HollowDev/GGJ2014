#include "AIManager.h"
#include "ObjectFactory.h"

#include "AssetManager.h"

AIManager AIManager::m_Instance;

void AIManager::Initialize( IEntity* _target )
{
	m_Target = (PlayerShip*)_target;
}

void AIManager::Release( void )
{

}

void AIManager::SpawnEnemy( D3DXVECTOR2 _pos )
{
	IEntity* enemy;
	if( ObjectFactory::GetInstance()->Create(&enemy, Entity_EnemyShip) )
	{
		RECT source = {0,0,128,128};
		
		int result = rand()%3;
		if(result == 0)
		{
			((EnemyShip*)enemy)->Initialize("assets/data/ships/enemy01.txt",_pos,AssetManager::GetInstance()->GetAsset(Asset_WeaponMachineGun03));
			((EnemyShip*)enemy)->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_EnemyShip01));
			((EnemyShip*)enemy)->SetSize(20);
			((EnemyShip*)enemy)->SetHP(1);
			((EnemyShip*)enemy)->SetMaxHP(1);
		}
		else if(result == 1)
		{
			((EnemyShip*)enemy)->Initialize("assets/data/ships/enemy02.txt",_pos,AssetManager::GetInstance()->GetAsset(Asset_WeaponLaser03));
			((EnemyShip*)enemy)->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_EnemyShip02));
			((EnemyShip*)enemy)->SetSize(20);
			((EnemyShip*)enemy)->SetHP(2);
			((EnemyShip*)enemy)->SetMaxHP(2);
		}
		else
		{
			((EnemyShip*)enemy)->Initialize("assets/data/ships/enemy03.txt",_pos,AssetManager::GetInstance()->GetAsset(Asset_WeaponMissle01));
			((EnemyShip*)enemy)->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_EnemyShip03));
			((EnemyShip*)enemy)->SetSize(45);
			((EnemyShip*)enemy)->SetHP(5);
			((EnemyShip*)enemy)->SetMaxHP(5);
		}
		((EnemyShip*)enemy)->SetImgSource(source);
		((EnemyShip*)enemy)->SetTarget(m_Target);
		((EnemyShip*)enemy)->SetIsAlive(true);
	}
}
