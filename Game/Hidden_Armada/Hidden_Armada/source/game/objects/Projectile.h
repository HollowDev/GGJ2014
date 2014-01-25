#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "BaseEntity.h"

class Projectile : public BaseEntity
{
	float m_Damage;
	float m_Life;
	IEntity* m_Owner;

public:
	Projectile( void );
	~Projectile( void ) { Release(); }

	void Initialize( void );
	virtual void Release( void );

	void Render( int _x, int _y );
	void Update( float _dt );
	bool CheckCollision( IEntity* _other );
	void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );

	virtual Sphere GetSphere( void ) { return Sphere(GetPos(), float(GetSize())); }

	inline void SetOwner( IEntity* _owner ) { m_Owner = _owner; }

	inline IEntity* GetOwner( void ) { return m_Owner; }
};

#endif