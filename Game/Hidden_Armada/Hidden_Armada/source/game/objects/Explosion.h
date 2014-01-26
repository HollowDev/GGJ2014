#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "BaseEntity.h"

class Explosion : public BaseEntity
{
	float m_FrameTimer;
	float m_FrameDur;
	int m_CurrFrame;
	bool m_IsBig;
	bool m_IsSingularity;

public:
	Explosion( void );
	~Explosion( void ) { Release(); }

	void Initialize( bool _isBig = false, bool _isSingularity = false );
	virtual void Release( void );

	virtual void Render( int _x, int _y );
	virtual void Update( float _dt );
	virtual bool CheckCollision( IEntity* _other );
	virtual void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );

	virtual Sphere GetSphere( void ) { return Sphere(GetPos(), float(GetSize())); }

	inline void SetIsBig( bool _isBig ) { m_IsBig = _isBig; }
};

#endif