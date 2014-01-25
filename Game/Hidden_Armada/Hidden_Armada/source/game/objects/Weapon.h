#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "BaseEntity.h"

class Weapon : public BaseEntity
{
	float m_FireTimer;
	float m_ROF;
	int m_Damage;
	int m_Level;

public:
	Weapon( void );
	~Weapon( void ) { Release(); }

	virtual void Release( void );

	virtual void Render( int _x, int _y );
	virtual void Update( float _dt );
	virtual bool CheckCollision( IEntity* _other ) { return false; }
	virtual void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );
	virtual Sphere GetSphere( void ) { return Sphere(GetPos(), float(GetSize())); }

	void Fire( void );
};

#endif