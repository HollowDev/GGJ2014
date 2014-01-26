#ifndef _PLAYER_SHIP_H_
#define _PLAYER_SHIP_H_

#include "Ship.h"
#include "../../engine/input/InputController.h"
#include "Shield.h"

class Camera;
class PlayerShip : public Ship
{
	int m_Score;

	// TODO:: Place controller here
	InputController* m_Input;
	Camera*			 m_Camera;
	Shield*			m_Shield;
	IEntity*		m_Reveal;

	float			m_RespawnTimer;
	float			m_RechargeTimer;
	float			m_LastHit;
	float			m_InvulnTimer;

public:
	PlayerShip( void );
	~PlayerShip( void ) { Release(); }

	void Initialize( const char* _filepath, D3DXVECTOR2 _pos, int _weaponID, InputController* _input, Camera* _camera );
	virtual void Release( void );

	virtual void Render( int _x, int _y );
	virtual void Update( float _dt );
	virtual bool CheckCollision( IEntity* _other );
	virtual void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );

	virtual Sphere GetSphere( void ) { return Sphere(GetPos()+this->GetImgCenter(), float(this->GetSize())); }

	void UseReveal( void );
	void UseBoost( void );

	// accessors
	inline int GetScore( void ) { return m_Score; }
	inline Shield* GetShield( void ) { return m_Shield; }

	// mutators
	inline void SetScore( int _score ) { m_Score = _score; }
	inline void SetShield( Shield* _shield ) { m_Shield = _shield; }

	inline void AddToScore( int _toAdd ) { m_Score += _toAdd; }
};

#endif