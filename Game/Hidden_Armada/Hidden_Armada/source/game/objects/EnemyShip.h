#ifndef _ENEMY_SHIP_H_
#define _ENEMY_SHIP_H_

#include "Ship.h"

class EnemyShip : public Ship
{
	BaseEntity* m_Target;

public:
	EnemyShip( void );
	~EnemyShip( void ) { Release(); }

	void Initialize( void );
	virtual void Release( void );

	virtual void Render( int _x, int _y );
	virtual void Update( float _dt );
	virtual bool CheckCollision( IEntity* _other );
	virtual void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );

	// Accessors
	inline BaseEntity* GetTarget( void ) { return m_Target; }

	// Mutators
	inline void SetTarget( BaseEntity* _target ) { m_Target = _target; }
};

#endif