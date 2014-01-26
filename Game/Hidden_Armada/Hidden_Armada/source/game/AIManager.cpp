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
		((EnemyShip*)enemy)->Initialize("assets/data/ships/ship1.txt",_pos,AssetManager::GetInstance()->GetAsset(Asset_WeaponMachineGun01));
		((EnemyShip*)enemy)->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_EnemyShip01));
		((EnemyShip*)enemy)->SetImgSource(source);
		((EnemyShip*)enemy)->SetImgCenter(D3DXVECTOR2(64,64));
		((EnemyShip*)enemy)->SetSize(20);
		((EnemyShip*)enemy)->SetTarget(m_Target);
		((EnemyShip*)enemy)->SetHP(1);
		((EnemyShip*)enemy)->SetMaxHP(1);
		((EnemyShip*)enemy)->SetIsAlive(true);
	}
}
