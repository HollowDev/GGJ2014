#include "AIManager.h"
#include "ObjectFactory.h"

AIManager AIManager::m_Instance;

void AIManager::Initialize( IEntity* _target, int _smallID, int _mediumID, int _largeID, int _weaponID )
{
	m_Target = (PlayerShip*)_target;

	m_SmallID = _smallID;
	m_MediumID = _mediumID;
	m_LargeID = _largeID;
	m_WeaponID = _weaponID;
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
		((EnemyShip*)enemy)->Initialize("assets/data/ships/ship1.txt",_pos,m_WeaponID);
		((EnemyShip*)enemy)->SetImgID(m_SmallID);
		((EnemyShip*)enemy)->SetImgSource(source);
		((EnemyShip*)enemy)->SetImgCenter(D3DXVECTOR2(64,64));
		((EnemyShip*)enemy)->SetSize(20);
		((EnemyShip*)enemy)->SetTarget(m_Target);
		((EnemyShip*)enemy)->SetHP(1);
		((EnemyShip*)enemy)->SetMaxHP(1);
	}
}
