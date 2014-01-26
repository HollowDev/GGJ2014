#ifndef _GAMEPLAY_STATE_H_
#define _GAMEPLAY_STATE_H_

#include "../../engine/app/BaseState.h"
#include "../objects/PlayerShip.h"
#include "../../engine/input/InputController.h"

class GameplayState : public BaseState
{
	PlayerShip* m_Player1;

	IEntity* m_AsteroidTest[100];
	IEntity* m_EnemyShip[100];

	InputController* m_Input;

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