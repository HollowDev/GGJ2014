#ifndef _CREDITS_STATE_H_
#define _CREDITS_STATE_H_

#include "../../engine/app/BaseState.h"

class CreditsState : public BaseState
{
public:
	CreditsState( void );
	~CreditsState( void ) { Release(); }

	bool Initialize( WinApp* _app );
	void Release( void );
	
	void Render( void );
	void Update( float _dt );
	bool Input( void );
};

#endif