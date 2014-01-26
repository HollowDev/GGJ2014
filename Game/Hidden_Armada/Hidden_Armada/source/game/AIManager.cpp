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

void AIManager::Update( float _dt )
{
	vector<EnemyShip*> newList;
	for(unsigned int i = 0; i < m_Enemies.size(); ++i)
	{
		if(m_Enemies[i]->GetIsAlive())
			newList.push_back(m_Enemies[i]);
	}

	m_Enemies = newList;
}


IEntity* AIManager::GetClosestEnemy( D3DXVECTOR2 _pos )
{
	if(m_Enemies.size() == 0)
		return nullptr;

	int closestIndex = -1;
	float closestDist = FLT_MAX;
	for(unsigned int i = 0; i < m_Enemies.size(); ++i)
	{
		D3DXVECTOR2 toTarget = m_Enemies[i]->GetPos() - _pos;
		float dist = D3DXVec2Length(&toTarget);
		if(dist < closestDist)
		{
			closestDist = dist;
			closestIndex = i;
		}
	}

	if(closestIndex == -1)
		return nullptr;

	return m_Enemies[closestIndex];
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
		if(rand()%6 == 0)
		{
			((EnemyShip*)enemy)->SwitchWeapons(Weapon_Missle);
			((EnemyShip*)enemy)->GetWeapon()->SetROF(1.5f);
		}
		else
			((EnemyShip*)enemy)->SwitchWeapons(Weapon_MachineGun);

		m_Enemies.push_back( (EnemyShip*)enemy );
	}
}
