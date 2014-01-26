#include "Keyboard.h"

Keyboard::Keyboard( void )
{
	m_DirectInput = 0;
	m_Keyboard = 0;
	m_Mouse = 0;
}

Keyboard::~Keyboard( void )
{

}

bool Keyboard::Initialize(HWND _hWnd, HINSTANCE _hInst)
{
	HRESULT hr;
	m_MouseX = 0;
	m_MouseY = 0;

	m_hWnd = _hWnd;
	m_hInst	= _hInst;

	hr = DirectInput8Create(_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_DirectInput, NULL);
	if(FAILED(hr))
		return false;

	hr = m_DirectInput->CreateDevice(GUID_SysKeyboard, &m_Keyboard, NULL);
	if(FAILED(hr))
		return false;

	hr = m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
		return false;

	hr = m_Keyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if(FAILED(hr))
		return false;

	hr = m_Keyboard->Acquire();
	if(FAILED(hr))
		return false;

	hr = m_DirectInput->CreateDevice(GUID_SysMouse, &m_Mouse, NULL);
	if(FAILED(hr))
		return false;

	hr = m_Mouse->SetDataFormat(&c_dfDIMouse);
	if(FAILED(hr))
		return false;

	hr = m_Mouse->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if(FAILED(hr))
		return false;

	hr = m_Mouse->Acquire();
	if(FAILED(hr))
		return false;

	return true;
}

void Keyboard::Release()
{
	if(m_Mouse)
	{
		m_Mouse->Unacquire();
		m_Mouse->Release();
		m_Mouse = 0;
	}

	if(m_Keyboard)
	{
		m_Keyboard->Acquire();
		m_Keyboard->Release();
		m_Keyboard = 0;
	}

	if(m_DirectInput)
	{
		m_DirectInput->Release();
		m_DirectInput = 0;
	}
}
bool Keyboard::Update()
{
	bool result;

	result = ReadKeyboard();
	if(!result)
		return false;

	result = ReadMouse();
	if(!result)
		return false;

	ProcessInput();

	return true;
}

bool Keyboard::ReadKeyboard()
{
	HRESULT hr;

	memcpy(m_PrevKeyboardState, m_KeyboardState, sizeof(unsigned char) * 256);

	hr = m_Keyboard->GetDeviceState(sizeof(m_KeyboardState), (LPVOID)&m_KeyboardState);
	if(FAILED(hr))
	{
		if((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
			m_Keyboard->Acquire();
		else
			return false;
	}

	return true;
}

bool Keyboard::ReadMouse()
{
	HRESULT hr = m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_MouseState);
	if(FAILED(hr))
	{
		if((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
			m_Mouse->Acquire();
		else
			return false;
	}
	return true;
}

void Keyboard::ProcessInput()
{
	m_MouseX += m_MouseState.lX;
	m_MouseY += m_MouseState.lY;

	if(m_MouseX < 0) { m_MouseX = 0; }
	if(m_MouseY < 0) { m_MouseY = 0; }

	if(m_MouseX > 1024) { m_MouseX = 1024; }
	if(m_MouseY > 768) { m_MouseY = 768; }
}

bool Keyboard::KeyPressed(unsigned char _key)
{
	if(!(m_PrevKeyboardState[_key] & 0x80) && (m_KeyboardState[_key] & 0x80))
	{
		return true;
	}
	return false;
}

bool Keyboard::KeyDown(unsigned char _key)
{
	if(m_KeyboardState[_key] & 0x80)
		return true;
	return false;
}

bool Keyboard::KeyUp(unsigned char _key)
{
	if(((m_PrevKeyboardState[_key] & 0x80)) && !(m_KeyboardState[_key] & 0x80))
		return true;
	return false;
}

void Keyboard::GetMouseLocation( int& _mouseX, int& _mouseY )
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(m_hWnd, &mouse);
	_mouseX = (int)mouse.x;
	_mouseY = (int)mouse.y;
}
