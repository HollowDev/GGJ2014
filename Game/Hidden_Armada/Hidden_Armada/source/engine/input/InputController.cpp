#include "InputController.h"

#include "../../engine/app/BaseState.h"
#include "../memory_macros.h"
#include "../../game/objects/PlayerShip.h"
#include "../../game/camera/Camera.h"


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
	m_Keyboard->Release();
	delete m_Keyboard;
}

void InputController::CheckInput( PlayerShip* _player, BaseState* _state, Camera* _camera )
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
		if(m_Gamepad->CheckConnection())	// Gamepad connected
		{
			m_Gamepad->Update();

			// RightStick moved, FIRE!
			if(m_Gamepad->m_RightStickX != 0.0f || m_Gamepad->m_RightStickY != 0.0f)
			{
				int posX = (int)(_player->GetWeapon()->GetPos().x + _player->GetWeapon()->GetImgCenter().x + m_Gamepad->m_RightStickX*10);
				int posY = (int)(_player->GetWeapon()->GetPos().y + _player->GetWeapon()->GetImgCenter().y - m_Gamepad->m_RightStickY*10);
				_player->RotateWeaponToMouse(posX,posY);
				_player->GetWeapon()->Fire(_player);
			}

			// LeftStick moved, MOVE!
			if(m_Gamepad->m_LeftStickX != 0.0f || m_Gamepad->m_LeftStickY != 0.0f)
			{
				if(m_Gamepad->m_LeftStickY > 0.0f)
					_player->SetVel(_player->GetVel() + D3DXVECTOR2(0, -_player->GetMaxSpeed()));
				else if(m_Gamepad->m_LeftStickY < 0.0f)
					_player->SetVel(_player->GetVel() + D3DXVECTOR2(0, _player->GetMaxSpeed()));

				if(m_Gamepad->m_LeftStickX < 0.0f)
					_player->SetVel(_player->GetVel() + D3DXVECTOR2(-_player->GetMaxSpeed(), 0));
				else if(m_Gamepad->m_LeftStickX > 0.0f)
					_player->SetVel(_player->GetVel() + D3DXVECTOR2(_player->GetMaxSpeed(), 0));
			}

			if(m_Gamepad->ButtonDown(XINPUT_GAMEPAD_RIGHT_SHOULDER))
			{
				_player->UseReveal();
			}
		}
		else	// No gamepad, use the keyboard/mouse
		{
			if(!m_Keyboard->Update())
				return;
			int x, y;

			m_Keyboard->GetMouseLocation(x, y);
			_player->RotateWeaponToMouse(x + (int)_camera->GetPos().x, y + (int)_camera->GetPos().y);

			if(m_Keyboard->KeyDown(DIK_W))
				_player->SetVel(_player->GetVel() + D3DXVECTOR2(0, -_player->GetMaxSpeed()));
			else if(m_Keyboard->KeyDown(DIK_S))
				_player->SetVel(_player->GetVel() + D3DXVECTOR2(0, _player->GetMaxSpeed()));

			if(m_Keyboard->KeyDown(DIK_A))
				_player->SetVel(_player->GetVel() + D3DXVECTOR2(-_player->GetMaxSpeed(), 0));
			else if(m_Keyboard->KeyDown(DIK_D))
				_player->SetVel(_player->GetVel() + D3DXVECTOR2(_player->GetMaxSpeed(), 0));

			if(GetAsyncKeyState(VK_LBUTTON))
				_player->GetWeapon()->Fire(_player);
			else if(GetAsyncKeyState(VK_RBUTTON))
				_player->UseReveal();
		}
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