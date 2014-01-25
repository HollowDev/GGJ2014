#ifndef _GAME_MODE_STATE_H_
#define _GAME_MODE_STATE_H_

#include "../../engine/app/BaseState.h"

class GameModeState : public BaseState
{
public:
	GameModeState( void );
	~GameModeState( void ) { Release(); }

	bool Initialize( WinApp* _app );
	void Release( void );
	
	void Render( void );
	void Update( float _dt );
	bool Input( void );
};

#endif