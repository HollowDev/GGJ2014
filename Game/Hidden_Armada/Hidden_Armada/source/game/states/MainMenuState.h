#ifndef _MAIN_MENU_STATE_H_
#define _MAIN_MENU_STATE_H_

#include "../../engine/app/BaseState.h"
#include <vector>

class InputController;

class MainMenuState : public BaseState
{
	int m_TextImg;
	int m_Background;
	int m_TestMusic;
	int m_MenuLoopMusic;
	int m_MoveSFX;
	std::vector<spriteButtons*> m_Buttons;

	bool	isTitle;
	float	m_FlashTimer;
	bool	m_IsInvis;
	bool	m_IsMoving;
	float	m_MoveTimer;
	float	m_MusicTimer;

	int		m_Selected;

	InputController* m_Input;
	

	enum Button{ PLAY_GAME, OPTIONS, EXIT_GAME, BACKGROUND, PRESS_START };

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