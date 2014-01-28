#ifndef _OPTIONS_STATE_H_
#define _OPTIONS_STATE_H_

#include "../../engine/app/BaseState.h"
#include "../Quadtree.h"

class TestState : public BaseState
{
public:
	TestState( void );
	~TestState( void ) { Release(); }

	bool Initialize( WinApp* _app );
	void Release( void );
	
	void Render( void );
	void Update( float _dt );
	bool Input( void );
};

#endif