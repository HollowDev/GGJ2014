#ifndef _PAUSE_STATE_H_
#define _PAUSE_STATE_H_

#include "../../engine/app/BaseState.h"

class PauseState : public BaseState
{
public:
	PauseState( void );
	~PauseState( void ) { Release(); }

	bool Initialize( WinApp* _app );
	void Release( void );
	
	void Render( void );
	void Update( float _dt );
	bool Input( void );
};

#endif