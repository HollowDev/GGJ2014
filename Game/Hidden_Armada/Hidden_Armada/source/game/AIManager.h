#ifndef _AI_MANAGER_H_
#define _AI_MANAGER_H_

#include "objects\EnemyShip.h"
#include "objects\PlayerShip.h"

#include <vector>
using std::vector;

class AIManager
{
	PlayerShip* m_Target;	// TODO:: change to targets for multiplayer
	
	int m_SmallID;
	int m_MediumID;
	int m_LargeID;

	int m_WeaponID;

	vector<EnemyShip*> m_Enemies;

	static AIManager m_Instance;

	AIManager( void ) {}
	~AIManager( void ) {}
public:

	static AIManager* GetInstance( void ) { return &m_Instance; }

	void Initialize( IEntity* _target );
	void Release( void );

	void Update( float _dt );
	void SpawnEnemy( D3DXVECTOR2 _pos );

	IEntity* GetClosestEnemy( D3DXVECTOR2 _pos );
	PlayerShip* GetTarget( void ) { return m_Target; }
};

#endif