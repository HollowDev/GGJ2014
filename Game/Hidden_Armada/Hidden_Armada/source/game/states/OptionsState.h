#ifndef _OPTIONS_STATE_H_
#define _OPTIONS_STATE_H_

#include "../../engine/app/BaseState.h"

class OptionsState : public BaseState
{
public:
	OptionsState( void );
	~OptionsState( void ) { Release(); }

	bool Initialize( WinApp* _app );
	void Release( void );
	
	void Render( void );
	void Update( float _dt );
	bool Input( void );
};

#endif