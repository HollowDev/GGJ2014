#include "Powerup.h"
#include "../../engine/renderer/TextureManager.h"

Powerup::Powerup( void )
{
	m_Type = Entity_Powerup;
	m_PowerType = -1;
	m_Life = 1.0f;

	RECT source = {0,0,16,16};
	this->SetImgSource(source);
	this->SetSize(8);
	this->SetImgCenter(D3DXVECTOR2(8,8)); 
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

	// TODO:: Add blinking when life is almost up.

	m_Life -= _dt;
	if(m_Life <= 0.0f)
	{
		this->SetIsAlive(false);
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
