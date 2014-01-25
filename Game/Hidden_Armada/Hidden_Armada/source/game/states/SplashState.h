#ifndef _SPLASH_STATE_H_
#define _SPLASH_STATE_H_

#include "../../engine/app/BaseState.h"

class SplashState : public BaseState
{
public:
	SplashState( void );
	~SplashState( void ) { Release(); }

	bool Initialize( WinApp* _app );
	void Release( void );
	
	void Render( void );
	void Update( float _dt );
	bool Input( void );
};

#endif