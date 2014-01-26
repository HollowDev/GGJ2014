#ifndef _LASER_BEAM_H_
#define _LASER_BEAM_H_

#include "BaseEntity.h"
#include "../../engine/collision/CollisionVolume.h"
#include <vector>
using std::vector;

class LaserBeam : public BaseEntity
{
	vector<D3DXVECTOR2> m_Laser;
	Segment m_Segment;
	IEntity* m_Owner;
	float m_PrevDist;
	float m_CanDamage;

public:
	LaserBeam( void );
	~LaserBeam( void ) { Release(); }
	
	virtual void Initialize( void );
	virtual void Release( void );

	virtual void Render( int _x, int _y );
	virtual void Update( float _dt );
	virtual bool CheckCollision( IEntity* _other );
	virtual void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );

	Segment GetSegment( void ) { return m_Segment; }

	inline void SetOwner( IEntity* _owner ) { m_Owner = _owner; }

	inline IEntity* GetOwner( void ) { return m_Owner; }
};

#endif