#ifndef _POWERUP_H_
#define _POWERUP_H_

#include "BaseEntity.h"

class Powerup : public BaseEntity
{
	int m_PowerType;
	float m_Life;
public:
	Powerup( void );
	~Powerup( void ) { Release(); }

	void Release( void );

	void Render( int _x, int _y );
	void Update( float _dt );
	bool CheckCollision( IEntity* _other );
	void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );

	Sphere GetSphere( void ) { return Sphere(GetPos(), float(GetSize())); }

	// accessors
	inline int GetPowerType( void ) { return m_PowerType; }
	inline float GetLife( void ) { return m_Life; }
	
	// Mutators
	inline void SetPowerType( int _powerType ) { m_PowerType = _powerType; }
	inline void SetLife( float _life ) { m_Life = _life; }
};

#endif