#include "InputController.h"

#include "../../engine/app/BaseState.h"
#include "../memory_macros.h"


InputController::InputController(void)
{
}

void InputController::Initialize( void )
{
	m_Gamepad = new Gamepad();
	m_Gamepad->Init(0);
	m_Gamepad->Update();
}

void InputController::Release( void )
{
	SAFE_DELETE(m_Gamepad);
}

void InputController::CheckInput( PlayerShip* _player, BaseState* _state )
{
	if(_player == nullptr)	// On a menu
	{
		if(m_Gamepad->CheckConnection())	// Gamepad connected
		{
			m_Gamepad->Update();
			//// Move option up
			//if(m_Gamepad->ButtonDown(XINPUT_GAMEPAD_DPAD_UP) || m_Gamepad->m_LeftStickY < 0)
			//{
			//	if()
			//}
			//// Move option down
			//else if(m_Gamepad->ButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || m_Gamepad->m_LeftStickY > 0)
			//{

			//}

			//// Move option left
			//if(m_Gamepad->ButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || m_Gamepad->m_LeftStickY > 0)
			//{

			//}
			//// Move option right
			//else if(m_Gamepad->ButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || m_Gamepad->m_LeftStickY > 0)
			//{

			//}

			//// Select option
			//if(m_Gamepad->ButtonPressed(XINPUT_GAMEPAD_A))
			//{

			//}

			//// Go Back
			//if(m_Gamepad->ButtonPressed(XINPUT_GAMEPAD_B))
			//{

			//}

			//// Start pressed
			//if(m_Gamepad->ButtonPressed(XINPUT_GAMEPAD_START))
			//{

			//}
		}
		else	// No gamepad, use the keyboard/mouse
		{
			// Move player up
			if( m_Gamepad->m_LeftStickY < 0)
			{

			}
			// Move player down
			else if( m_Gamepad->m_LeftStickY > 0)
			{

			}

			// Move player left
			if( m_Gamepad->m_LeftStickY > 0)
			{

			}
			// Move player right
			else if( m_Gamepad->m_LeftStickY > 0)
			{

			}
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
	return false;
}

bool InputController::Input_LeftDown(void)
{
	if(m_Gamepad->CheckConnection())
	{
		if(m_Gamepad->ButtonPressed(XINPUT_GAMEPAD_DPAD_LEFT))
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
	return false;
}

bool InputController::Input_Confirm(void)
{
	if(m_Gamepad->CheckConnection())
	{
		if(m_Gamepad->ButtonPressed(XINPUT_GAMEPAD_A))
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
	return false;
}

bool InputController::Input_StartPressed(void)
{
	if(m_Gamepad->CheckConnection())
	{
		if(m_Gamepad->ButtonPressed(XINPUT_GAMEPAD_START))
			return true;
	}
	return false;
}