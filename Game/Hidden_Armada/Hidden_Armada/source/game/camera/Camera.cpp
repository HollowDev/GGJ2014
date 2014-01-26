#include "Camera.h"
#include "../../engine/app/WinApp.h"

void Camera::Initialize( PlayerShip* _player )
{
	m_PosX = _player->GetPos().x;
	m_PosY = _player->GetPos().y;

	m_PrevX = 0.0f;
	m_PrevY = 0.0f;

	m_lerpTimer = 0.0f;
}

void Camera::Update( float _dt, PlayerShip* _player, WinApp* _app, int _rows, int _cols )
{
	if(m_PrevX != _player->GetPos().x || m_PrevY != _player->GetPos().y)
	{
		m_PosX = _player->GetPos().x + _player->GetImgCenter().x;
		m_PosY = _player->GetPos().y + _player->GetImgCenter().y;

		if(m_PosX < _app->GetWidth() / 2)
			m_PosX = 0.0f;
		else if(m_PosX > (1024*_cols) - _app->GetWidth() / 2)
			m_PosX = (float)(1024*_cols) - _app->GetWidth();
		else 
			m_PosX -= (float)_app->GetWidth() / 2;

		if(m_PosY < _app->GetHeight() / 2)
			m_PosY = 0.0f;
		else if(m_PosY > (768*_rows) - _app->GetHeight() / 2)
			m_PosY = (float)(768*_rows) - _app->GetHeight();
		else 
			m_PosY -= (float)_app->GetHeight() / 2;
	}
	
	m_lerpTimer += _dt * 0.05f;

	m_PrevX = lerp(m_PrevX, m_PosX, _dt * 5.0f);
	m_PrevY = lerp(m_PrevY, m_PosY, _dt * 5.0f);

	if(m_lerpTimer > 1.0f)
		m_lerpTimer = 0.0f;
	
}
