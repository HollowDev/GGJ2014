#ifndef _MAIN_MENU_STATE_H_
#define _MAIN_MENU_STATE_H_

#include "../../engine/app/BaseState.h"

class MainMenuState : public BaseState
{
	int m_TestImg;
public:
	MainMenuState( void );
	~MainMenuState( void ) { Release(); }

	bool Initialize( WinApp* _app );
	void Release( void );
	
	void Render( void );
	void Update( float _dt );
	bool Input( void );
};

#endif