#ifndef _GAMEPLAY_STATE_H_
#define _GAMEPLAY_STATE_H_

#include "../../engine/app/BaseState.h"
#include "../objects/PlayerShip.h"
#include "../../engine/input/InputController.h"
#include "../../engine/renderer/BitmapFont.h"
#include "../camera/Camera.h"
#include "../AsteroidManager.h"

class GameplayState : public BaseState
{
	PlayerShip* m_Player1;
	BitmapFont m_Font;

	IEntity* m_AsteroidTest[100];
	IEntity* m_EnemyShip[100];

	Camera*	m_Camera;

	InputController* m_Input;
	AsteroidManager m_AsteroidManager;

	int		m_HudBackgroundID;
	int		m_ShieldBarID;
	int		m_HealthBarID;
	
	spriteButtons m_ShieldBar;
	spriteButtons m_HudBackground;

	spriteButtons m_HealthBar1;

public:
	GameplayState( void );
	~GameplayState( void ) { Release(); }

	bool Initialize( WinApp* _app );
	void Release( void );

	void Render( void );
	void Update( float _dt );
	bool Input( void );
};

#endif