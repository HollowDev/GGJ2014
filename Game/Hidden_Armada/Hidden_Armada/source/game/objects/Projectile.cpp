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
	RECT source = {0,0,16,32};
	this->SetImgSource(source);
	this->SetSize(8);
	m_Life = 5.0f;
	this->SetIsAlive(true);
	this->SetImgID(3);
	this->SetImgCenter(D3DXVECTOR2(8,16));
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
	// Add the current velocity to the position.
	this->SetPos(this->GetPos() + this->GetVel() * _dt);
	this->SetVel(this->GetVel() * 0.99f);
	
	// Cap max speed
	if(D3DXVec2Length(&this->GetVel()) > this->GetMaxSpeed())
	{
		D3DXVECTOR2 cappedVel;
		D3DXVec2Normalize(&cappedVel,&this->GetVel());
		cappedVel *= this->GetMaxSpeed();
		this->SetVel(cappedVel);
	}

	D3DXVECTOR2 vel = this->GetDir() * this->GetMaxSpeed();
	this->SetVel(vel);

	Rotate();

	m_Life -= _dt;
	if(m_Life <= 0.0f)
	{
		m_Life = 5.0f;
		this->SetIsAlive(false);
	}
}

bool Projectile::CheckCollision( IEntity* _other )
{
	if( _other->GetType() == Entity_EnemyShip && m_Owner->GetType() == Entity_EnemyShip )
		return false;

	if( _other->GetType() == Entity_Asteroid && m_Owner->GetType() == Entity_EnemyShip )
		return false;

	if( _other != m_Owner && _other->GetType() != Entity_Projectile )
		return true;
	
	return false;
}
void Projectile::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{
	if( _other->GetType() == Entity_EnemyShip && m_Owner->GetType() == Entity_EnemyShip )
		return;
	if( _other->GetType() != Entity_Projectile && _other != m_Owner )
		this->SetIsAlive(false);
}
