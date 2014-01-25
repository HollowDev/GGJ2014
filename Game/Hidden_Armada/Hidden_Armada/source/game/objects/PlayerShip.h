#ifndef _PLAYER_SHIP_H_
#define _PLAYER_SHIP_H_

#include "Ship.h"

class PlayerShip : public Ship
{
	int m_Score;

	// TODO:: Place controller here
public:
	PlayerShip( void );
	~PlayerShip( void ) { Release(); }

	void Initialize( const char* _filepath, D3DXVECTOR2 _pos, int _weaponID );
	virtual void Release( void );

	virtual void Render( int _x, int _y );
	virtual void Update( float _dt );
	virtual bool CheckCollision( IEntity* _other );
	virtual void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );

	virtual Sphere GetSphere( void ) { return Sphere(GetPos()+this->GetImgCenter(), float(this->GetSize())); }

};

#endif