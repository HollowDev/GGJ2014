#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

#include "../windows.h"
#include <Xinput.h>
#pragma comment(lib, "XInput.lib")

class Gamepad
{
private:
	int m_cID;
	bool m_isConnected;

	float m_DeadzoneX;
	float m_DeadzoneY;

	WORD m_Pressed;
	WORD m_Down;
	WORD m_Up;

	void CheckButtons( WORD _buttons, WORD _button );

public:
	Gamepad(void) : m_DeadzoneX(0.02f), m_DeadzoneY(0.02f) {}
	Gamepad(float _dzX, float _dzY) : m_DeadzoneX(_dzX), m_DeadzoneY(_dzY) {}
	~Gamepad(void) { Release(); }

	float	m_LeftStickX;
	float	m_LeftStickY;
	float	m_RightStickX;
	float	m_RightStickY;
	float	m_LeftTrigger;
	float	m_RightTrigger;

	void Init(int _id) { m_cID = _id; }
	void Release(void);

	int GetPort();
	bool CheckConnection();
	void Update();


	bool ButtonPressed( WORD _button );
	bool ButtonDown( WORD _button );
	bool ButtonUp( WORD _button );
	float	RightStickPosition(void);
	float	LeftStickPosition(void);
};

#endif