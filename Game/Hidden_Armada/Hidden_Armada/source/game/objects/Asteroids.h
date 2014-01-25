#ifndef _ASTEROIDS_H_
#define _ASTEROIDS_H_

#include "BaseEntity.h"

class Asteroids : public BaseEntity
{
	int m_HP;
	D3DXVECTOR2 m_ConstantVel;

public:
	Asteroids( void );
	~Asteroids( void ) { Release(); }

	void Initialize( void );
	void Release( void );

	void Render( int _x, int _y );
	void Update( float _dt );
	virtual bool CheckCollision( IEntity* _other );
	void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );

	virtual Sphere GetSphere( void ) { return Sphere(GetPos()+this->GetImgCenter(), float(this->GetSize())); }
};

#endif