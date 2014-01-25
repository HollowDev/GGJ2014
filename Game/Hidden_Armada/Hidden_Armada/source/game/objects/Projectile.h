#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "BaseEntity.h"

class Projectile : public BaseEntity
{
	float m_Damage;
	float m_Life;

public:
	Projectile( void );
	~Projectile( void ) { Release(); }

	void Initialize( void );
	virtual void Release( void );

	virtual void Render( int _x, int _y );
	virtual void Update( float _dt );
	virtual void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );

	virtual Sphere GetSphere( void ) { return Sphere(GetPos(), float(GetSize())); }
};

#endif