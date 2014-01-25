#include "InputController.h"

#include "../../engine/app/BaseState.h"
#include "../memory_macros.h"


InputController::InputController(void)
{
}

void InputController::Initialize( HWND _hWnd, HINSTANCE _hInst )
{
	m_Gamepad = new Gamepad();
	m_Gamepad->Init(0);
	m_Gamepad->Update();

	m_Keyboard = new Keyboard();
	m_Keyboard->Initialize(_hWnd, _hInst);
}

void InputController::Release( void )
{
	SAFE_DELETE(m_Gamepad);
	SAFE_RELEASE(m_Keyboard);
}

void InputController::CheckInput( PlayerShip* _player, BaseState* _state )
{
	if(_player == nullptr)	// On a menu
	{
		if(m_Gamepad->CheckConnection())	// Gamepad connected
		{
			m_Gamepad->Update();
		}
		else	// No gamepad, use the keyboard/mouse
		{
			if(!m_Keyboard->Update())
				return;
		}
	}
	else	// In the game
	{

	}
}

bool InputController::Input_UpDown(void)
{
	if(m_Gamepad->CheckConnection())
	{
		if(m_Gamepad->ButtonPressed(XINPUT_GAMEPAD_DPAD_UP))
		{
			return true;
		}
	}
	else
	{
		if(m_Keyboard->KeyPressed(DIK_UP))
			return true;
	}
	return false;
}

bool InputController::Input_DownDown(void)
{
	if(m_Gamepad->CheckConnection())
	{
		if(m_Gamepad->ButtonPressed(XINPUT_GAMEPAD_DPAD_DOWN))
		{
			return true;
		}
	}
	else
	{
		if(m_Keyboard->KeyPressed(DIK_DOWN))
			return true;
	}
	return false;
}

bool InputController::Input_LeftDown(void)
{
	if(m_Gamepad->CheckConnection())
	{
		if(m_Gamepad->ButtonPressed(XINPUT_GAMEPAD_DPAD_LEFT))
			return true;
	}
	else
	{
		if(m_Keyboard->KeyPressed(DIK_LEFT))
			return true;
	}
	return false;
}

bool InputController::Input_RightDown(void)
{
	if(m_Gamepad->CheckConnection())
	{
		if(m_Gamepad->ButtonPressed(XINPUT_GAMEPAD_DPAD_RIGHT))
			return true;
	}
	else
	{
		if(m_Keyboard->KeyPressed(DIK_RIGHT))
			return true;
	}
	return false;
}

bool InputController::Input_Confirm(void)
{
	if(m_Gamepad->CheckConnection())
	{
		if(m_Gamepad->ButtonPressed(XINPUT_GAMEPAD_A))
			return true;
	}
	else
	{
		if(m_Keyboard->KeyPressed(DIK_RETURN))
			return true;
	}
	return false;
}

bool InputController::Input_Cancel(void)
{
	if(m_Gamepad->CheckConnection())
	{
		if(m_Gamepad->ButtonPressed(XINPUT_GAMEPAD_B))
			return true;
	}
	else
	{
		if(m_Keyboard->KeyPressed(DIK_ESCAPE))
			return true;
	}
	return false;
}

bool InputController::Input_StartPressed(void)
{
	if(m_Gamepad->CheckConnection())
	{
		if(m_Gamepad->ButtonPressed(XINPUT_GAMEPAD_START))
			return true;
	}
	else
	{
		if(m_Keyboard->KeyPressed(DIK_RETURN))
			return true;
	}
	return false;
}