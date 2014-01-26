#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../../engine/directx9.h"
#include "../../game/objects/PlayerShip.h"

class WinApp;

class Camera
{
private:
	float	m_PosX;
	float	m_PosY;

	float	m_OffsetX;
	float	m_OffsetY;

	float	m_PrevX, m_PrevY;

	float	m_lerpTimer;

	float lerp(float _start, float _end, float _percent)
	{
		return (_start + _percent * (_end - _start));
	}

public:
	Camera(void){}
	~Camera(void){}

	const D3DXVECTOR2 inline GetPos(void)
	{
		D3DXVECTOR2 pos;
		pos.x = m_PrevX;
		pos.y = m_PrevY;
		return pos;
	}

	void Initialize(PlayerShip* _player);
	void Update(float _dt, PlayerShip* _player, WinApp* _app);
};

#endif