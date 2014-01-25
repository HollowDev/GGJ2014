#ifndef _AI_MANAGER_H_
#define _AI_MANAGER_H_

#include "objects\EnemyShip.h"
#include "objects\PlayerShip.h"

class AIManager
{
	PlayerShip* m_Target;	// TODO:: change to targets for multiplayer
	
	int m_SmallID;
	int m_MediumID;
	int m_LargeID;

	int m_WeaponID;

	static AIManager m_Instance;

	AIManager( void ) {}
	~AIManager( void ) {}
public:

	static AIManager* GetInstance( void ) { return &m_Instance; }

	void Initialize( IEntity* _target, int _smallID, int _mediumID, int _largeID, int _weaponID );
	void Release( void );

	void SpawnEnemy( D3DXVECTOR2 _pos );
};

#endif