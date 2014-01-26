#ifndef _BOOST_TRAIL_H_
#define _BOOST_TRAIL_H_

#include "BaseEntity.h"

class BoostTrail : public BaseEntity
{
	float m_Life;

public:
	BoostTrail( void );
	~BoostTrail( void ) { Release(); }

	void Initialize( void );
	virtual void Release( void );

	virtual void Render( int _x, int _y );
	virtual void Update( float _dt );
	virtual bool CheckCollision( IEntity* _other );
	virtual void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );

	virtual Sphere GetSphere( void ) { return Sphere(GetPos(), float(GetSize())); }
};

#endif