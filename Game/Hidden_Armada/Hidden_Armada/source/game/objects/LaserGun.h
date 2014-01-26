#ifndef _LASER_GUN_H_
#define _LASER_GUN_H_

#include "Weapon.h"

class LaserGun : public Weapon
{
public:
	LaserGun( void );
	~LaserGun( void ) { Release(); }	
	
	virtual void Initialize( void );
	virtual void Release( void );

	virtual void Render( int _x, int _y );
	virtual void Update( float _dt );
	virtual bool CheckCollision( IEntity* _other ) { return false; }
	virtual void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );
	virtual Sphere GetSphere( void ) { return Sphere(GetPos(), float(GetSize())); }

	virtual void Fire( IEntity* _owner );
};

#endif