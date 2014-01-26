#ifndef _PAUSE_STATE_H_
#define _PAUSE_STATE_H_

#include "../../engine/app/BaseState.h"

#include <vector>

class InputController;

class PauseState : public BaseState
{
private:
	int m_TextImg;
	int m_Background;
	int m_IntroMusic;
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
	bool*	m_Paused;
	bool*	m_QuitGame;

	InputController* m_Input;

	float lerp(float _start, float _end, float _percent)
	{
		return (_start + _percent * (_end - _start));
	}

	enum Button{ PLAY_GAME, OPTIONS, EXIT_GAME, BACKGROUND};
public:
	PauseState( InputController* _input, bool& _gamePaused, bool& _quitGame);
	~PauseState( void ) { Release(); }

	bool Initialize( WinApp* _app );
	void Release( void );
	
	void Render( void );
	void Update( float _dt );
	bool Input( void );
};

#endif