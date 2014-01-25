#ifndef _IENTITY_H_
#define _IENTITY_H_

#include "../../engine/collision/CollisionVolume.h"

enum Entity_Type
{
	Entity_None = 0, Entity_PlayerShip, Entity_EnemyShip, Entity_Projectile,
	Entity_Asteroid,
	Entity_NumTypes
};

class IEntity
{
protected:
	Entity_Type m_Type;
	bool m_IsAlive;

public:
	virtual ~IEntity( void ) = 0 {}
	// The Interface
	virtual void Release( void ) = 0;

	virtual void Render( int _x, int _y ) = 0;
	virtual void Update( float _dt ) = 0;
	virtual void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY ) = 0;

	virtual Sphere GetSphere( void ) = 0;
	
	inline Entity_Type GetType( void ) { return m_Type; }
	inline bool GetIsAlive( void ) { return m_IsAlive; }

	inline void SetIsAlive( bool _isAlive ) { m_IsAlive = _isAlive; }
};

#endif