#ifndef _BOSS_ENEMY_H_
#define _BOSS_ENEMY_H_

#include "EnemyShip.h"

class BossEnemy : public EnemyShip
{
	Weapon* m_Cannons[4];
	D3DXVECTOR2 m_Offsets[4];

	float m_SpecialRot;

public:
	BossEnemy( void );
	~BossEnemy( void ) { Release(); }

	void Initialize( void );
	void Release( void );

	void Render( int _x, int _y );
	void Update( float _dt );
	bool CheckCollision( IEntity* _other );
	void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );
};

#endif