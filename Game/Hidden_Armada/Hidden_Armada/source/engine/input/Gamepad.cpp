#include "Gamepad.h"

#include <amp_math.h>

int Gamepad::GetPort()
{
	return m_cID + 1;
}

bool Gamepad::CheckConnection()
{
	int cID = -1;

	for(DWORD i = 0; i < XUSER_MAX_COUNT && cID == -1; ++i)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if(XInputGetState(i, &state) == ERROR_SUCCESS)
			cID = i;
	}

	m_cID = cID;

	return (cID != -1);
}

void Gamepad::CheckButtons( WORD _buttons, WORD _button )
{
	if( (_buttons & _button) != 0)
	{
		// if it was pressed last frame, then it's now down
		if( (m_Pressed & _button) != 0 || (m_Down & _button) != 0)
		{
			m_Down |= _button;
			m_Pressed &= ~_button;
		}
		else
		{
			m_Pressed |= _button;
			m_Down &= ~_button;
		}
	}
	else
	{
		if( (m_Down & _button) != 0 || (m_Pressed & _button) != 0)
			m_Up |= _button;

		m_Down &= ~_button;
		m_Pressed &= ~_button;
	}
}

void Gamepad::Update()
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	if(XInputGetState(m_cID, &state) == ERROR_SUCCESS)
	{
		m_isConnected = true;

		CheckButtons(state.Gamepad.wButtons, XINPUT_GAMEPAD_A);
		CheckButtons(state.Gamepad.wButtons, XINPUT_GAMEPAD_B);
		CheckButtons(state.Gamepad.wButtons, XINPUT_GAMEPAD_X);
		CheckButtons(state.Gamepad.wButtons, XINPUT_GAMEPAD_Y);

		CheckButtons(state.Gamepad.wButtons, XINPUT_GAMEPAD_DPAD_LEFT);
		CheckButtons(state.Gamepad.wButtons, XINPUT_GAMEPAD_DPAD_RIGHT);
		CheckButtons(state.Gamepad.wButtons, XINPUT_GAMEPAD_DPAD_UP);
		CheckButtons(state.Gamepad.wButtons, XINPUT_GAMEPAD_DPAD_DOWN);

		CheckButtons(state.Gamepad.wButtons, XINPUT_GAMEPAD_LEFT_SHOULDER);
		CheckButtons(state.Gamepad.wButtons, XINPUT_GAMEPAD_RIGHT_SHOULDER);

		CheckButtons(state.Gamepad.wButtons, XINPUT_GAMEPAD_LEFT_THUMB);
		CheckButtons(state.Gamepad.wButtons, XINPUT_GAMEPAD_RIGHT_THUMB);

		CheckButtons(state.Gamepad.wButtons, XINPUT_GAMEPAD_BACK);
		CheckButtons(state.Gamepad.wButtons, XINPUT_GAMEPAD_START);

		float normLX = max(-1, (float) state.Gamepad.sThumbLX / 32767);
		float normLY = max(-1, (float) state.Gamepad.sThumbLY / 32767);

		m_LeftStickX = (abs(normLX) < m_DeadzoneX ? 0 : (abs(normLX) - m_DeadzoneX) * (normLX / abs(normLX)));
		m_LeftStickY = (abs(normLY) < m_DeadzoneY ? 0 : (abs(normLY) - m_DeadzoneY) * (normLY / abs(normLY)));

		float normRX = max(-1, (float) state.Gamepad.sThumbRX / 32767);
		float normRY = max(-1, (float) state.Gamepad.sThumbRY / 32767);

		m_RightStickX = (abs(normRX) < m_DeadzoneX ? 0 : (abs(normRX) - m_DeadzoneX) * (normRX / abs(normRX)));
		m_RightStickY = (abs(normRY) < m_DeadzoneY ? 0 : (abs(normRY) - m_DeadzoneY) * (normRY / abs(normRY)));

		
	}
	else
		m_isConnected = false;
}

bool Gamepad::ButtonPressed( WORD _button )
{
	if(m_isConnected)
	{
		if((m_Pressed & _button) != 0)
			return true;
	}
	return false;
}

bool Gamepad::ButtonDown( WORD _button )
{
	if(m_isConnected)
	{
		if((m_Down & _button) != 0)
			return true;
	}
	return false;
}

bool Gamepad::ButtonUp( WORD _button )
{
	if(m_isConnected)
	{
		if((m_Up & _button) != 0)
			return true;
	}
	return false;
}

void Gamepad::Release(void)
{

}