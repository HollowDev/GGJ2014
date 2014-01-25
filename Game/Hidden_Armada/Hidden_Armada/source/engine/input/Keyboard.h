#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

class Keyboard
{
private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

	IDirectInput8* m_DirectInput;
	IDirectInputDevice8* m_Keyboard;
	IDirectInputDevice8* m_Mouse;

	unsigned char m_KeyboardState[256];
	unsigned char m_PrevKeyboardState[256];
	DIMOUSESTATE m_MouseState;

	int m_MouseX, m_MouseY;

public:
	Keyboard(void);
	~Keyboard(void);

	bool Initialize(HWND _hWnd, HINSTANCE _hInst);
	void Release();
	bool Update();

	bool KeyPressed(unsigned char _key);
	bool KeyDown(unsigned char _key);
	bool KeyUp(unsigned char _key);
	void GetMouseLocation(int& _mouseX, int& _mouseY);
};

#endif