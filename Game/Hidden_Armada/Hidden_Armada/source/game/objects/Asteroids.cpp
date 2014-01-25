#include "Asteroids.h"

Asteroids::Asteroids( void )
{
	this->m_Type = Entity_Asteroid;
	m_HP = 2;
}

void Asteroids::Initialize( void )
{
	m_ConstantVel.x = (rand()%200 - 100) / 10.0f;
	m_ConstantVel.y = (rand()%200 - 100) / 10.0f; 
	this->SetPos(D3DXVECTOR2(200,200));
	RECT source = {0,0,64,64};
	this->SetImgSource(source);
	this->SetSize(30);
	this->SetImgCenter(D3DXVECTOR2(32,32));
}

void Asteroids::Release( void )
{
	BaseEntity::Release();
}

void Asteroids::Render( int _x, int _y )
{
	BaseEntity::Render(_x,_y);
}

void Asteroids::Update( float _dt )
{
	BaseEntity::Update(_dt);

	this->SetVel(m_ConstantVel);
}

void Asteroids::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{
	if(_other->GetType() == Entity_Asteroid || _other->GetType() == Entity_PlayerShip )
	{
		this->SetPos( this->GetPos() + D3DXVECTOR2(_dirX,_dirY) * _dist);
		D3DXVECTOR2 dir(_dirX,_dirY);
		D3DXVec2Scale(&m_ConstantVel,&dir,-50.0f);
	}
	else if(_other->GetType() == Entity_Projectile)
	{
		// TODO:: spawn ship, possibly, do animation, spawn particles
		this->SetIsAlive(false);
	}
}
