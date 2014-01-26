#ifndef _INPUT_CONTROLLER_H_
#define _INPUT_CONTROLLER_H_
#include "InputManager.h"
#include "Gamepad.h"
#include "Keyboard.h"

class PlayerShip;
class BaseState;
class Camera;

class InputController
{
private:
	Gamepad*	m_Gamepad;
	Keyboard*	m_Keyboard;

public:
	InputController(void);
	~InputController(void) { Release(); }

	void Initialize(HWND _hWnd, HINSTANCE _hInst);
	void Release(void);

	void CheckInput(PlayerShip* _player, BaseState* _state, Camera* _camera);

	bool Input_UpDown(void);
	bool Input_DownDown(void);
	bool Input_LeftDown(void);
	bool Input_RightDown(void);

	bool Input_Confirm(void);
	bool Input_Cancel(void);
	bool Input_StartPressed(void);
};

#endif