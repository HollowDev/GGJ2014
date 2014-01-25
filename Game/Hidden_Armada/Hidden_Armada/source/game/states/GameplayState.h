#ifndef _GAMEPLAY_STATE_H_
#define _GAMEPLAY_STATE_H_

#include "../../engine/app/BaseState.h"
#include "../objects/Ship.h"

class GameplayState : public BaseState
{
	Ship* m_Player1, *m_Player2;

	IEntity* m_AsteroidTest[100];

public:
	GameplayState( void );
	~GameplayState( void ) { Release(); }

	bool Initialize( WinApp* _app );
	void Release( void );
	
	void Render( void );
	void Update( float _dt );
	bool Input( void );
};

#endif