#include "Projectile.h"

Projectile::Projectile( void )
{
	this->m_Type = Entity_Projectile;
	this->m_IsAlive = true;

	m_Damage = 0;
	m_Life = 0.0f;
}

void Projectile::Initialize( void )
{
	this->SetMaxSpeed(500);
	RECT source = {0,0,64,64};
	this->SetImgSource(source);
	this->SetSize(8);
	m_Life = 5.0f;
}

void Projectile::Release( void )
{

}

void Projectile::Render( int _x, int _y )
{
	BaseEntity::Render(_x,_y);
}

void Projectile::Update( float _dt )
{
	BaseEntity::Update(_dt);
	D3DXVECTOR2 vel = this->GetDir() * this->GetMaxSpeed();
	this->SetVel(vel);

	m_Life -= _dt;
	if(m_Life <= 0.0f)
	{
		m_Life = 5.0f;
		this->SetIsAlive(false);
	}
}

void Projectile::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{
	if( _other->GetType() != Entity_PlayerShip && _other->GetType() != Entity_Projectile )
		this->SetIsAlive(false);
}
