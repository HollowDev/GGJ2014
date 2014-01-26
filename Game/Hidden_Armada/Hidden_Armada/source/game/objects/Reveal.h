#ifndef _REVEAL_H_
#define _REVEAL_H_

#include "BaseEntity.h"

class Reveal : public BaseEntity
{
	float m_Timer;
	float m_Scale;

	float Lerp(float _p1, float _p2, float _delta)
	{
		return _p1 + _delta * (_p2 - _p1);
	}
public:
	Reveal( void );
	~Reveal( void ) { Release(); }

	void Initialize( void );
	virtual void Release( void );

	virtual void Render( int _x, int _y );
	virtual void Update( float _dt );
	virtual bool CheckCollision( IEntity* _other );
	virtual void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );

	virtual Sphere GetSphere( void ) { return Sphere(GetPos(), float(GetSize())); }

};

#endif