#ifndef _MAIN_MENU_STATE_H_
#define _MAIN_MENU_STATE_H_

#include "../../engine/app/BaseState.h"

#include "../../engine/windows.h"
#include <vector>

class MainMenuState : public BaseState
{
	int m_TestImg;
	int m_TextImg;
	std::vector<RECT> m_Buttons;

	enum Button{ PLAY_GAME, OPTIONS, EXIT_GAME };

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