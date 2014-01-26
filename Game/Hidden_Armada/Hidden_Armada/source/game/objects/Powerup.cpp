#include "Powerup.h"
#include "../../engine/renderer/TextureManager.h"

Powerup::Powerup( void )
{
	m_Type = Entity_Powerup;
	m_PowerType = -1;
	m_Life = 1.0f;

	RECT source = {0,0,32,32};
	this->SetImgSource(source);
	this->SetSize(15);
	this->SetImgCenter(D3DXVECTOR2(16,16)); 
	this->SetDir(D3DXVECTOR2(rand()%200 - 100 / 10.0f,rand()%200 - 100 / 10));

	m_AnimTimer = 0.0f;
	m_Frame = 0;
}

void Powerup::Release( void )
{

}

void Powerup::Render( int _x, int _y )
{
	BaseEntity::Render(_x,_y);
}

void Powerup::Update( float _dt )
{
	BaseEntity::Update(_dt);

	RECT source = {m_Frame*32, 32*m_PowerType, 32 + m_Frame*32, 32 + 32*m_PowerType};
	this->SetImgSource(source);

	// TODO:: Add blinking when life is almost up.
	this->SetVel(this->GetDir() * 25 * _dt);

	m_Life -= _dt;
	if(m_Life <= 0.0f)
	{
		this->SetIsAlive(false);
	}

	m_AnimTimer -= _dt;
	if(m_AnimTimer <= 0.0f)
	{
		m_Frame++;
		if(m_Frame > 1)
			m_Frame = 0;

		m_AnimTimer = 0.25f;
	}
}

bool Powerup::CheckCollision( IEntity* _other )
{
	if( _other->GetType() == Entity_PlayerShip )
		return true;

	return false;
}

void Powerup::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{
	if( _other->GetType() == Entity_PlayerShip )
	{
		// TODO:: Add particles when the entity is pickedup.
		this->SetIsAlive(false);
	}
}
