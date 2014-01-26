#include "Asteroids.h"
#include "../AIManager.h"
#include "Projectile.h"

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
	this->SetDir(D3DXVECTOR2((float)(rand()%200 - 100), (float)(rand()%200 - 100)));

	if(rand()%2 == 0)
		m_RotDir = -1.0f;
	else
		m_RotDir = 1.0f;

	m_RotDir *= float(rand()%150)/100.0f;
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

	if(GetPos().x + GetSize() < 0)
	{
		SetPos(D3DXVECTOR2(0 + GetSize(), GetPos().y));
		m_ConstantVel.x = -m_ConstantVel.x;
	}
	else if(GetPos().x + GetSize() * 4 > 1024 * 4)
	{
		SetPos(D3DXVECTOR2(1024*4 - GetSize() * 4, GetPos().y));
		m_ConstantVel.x = -m_ConstantVel.x;
	}

	if(GetPos().y - GetSize() < 0)
	{
		SetPos(D3DXVECTOR2(GetPos().x, 0 + GetSize()));
		m_ConstantVel.y = -m_ConstantVel.y;
	}
	else if(GetPos().y + GetSize() * 4 > 768 * 4)
	{
		SetPos(D3DXVECTOR2(GetPos().x, 768*4 - GetSize() * 4));
		m_ConstantVel.y = -m_ConstantVel.y;
	}

	this->SetVel(m_ConstantVel);

	this->SetRot(this->GetRot() + m_RotDir*_dt);
	D3DXVECTOR2 forward = Rotate2D( D3DXVECTOR2(0,-1), this->GetRot() );
	this->SetDir(forward);
}

bool Asteroids::CheckCollision( IEntity* _other )
{
	if(_other->GetType() == Entity_Asteroid || _other->GetType() == Entity_PlayerShip ||
		_other->GetType() == Entity_Projectile || _other->GetType() == Entity_EnemyShip ||
		_other->GetType() == Entity_LaserBeam || _other->GetType() == Entity_Reveal)
		return true;

	return false;
}

void Asteroids::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{
	if( _other->GetType() == Entity_Asteroid || _other->GetType() == Entity_PlayerShip ||
		_other->GetType() == Entity_EnemyShip )
	{
		this->SetPos( this->GetPos() + D3DXVECTOR2(_dirX,_dirY) * _dist);
		D3DXVECTOR2 dir(_dirX,_dirY);
		D3DXVec2Scale(&m_ConstantVel,&dir,-50.0f);
	}
	else if((_other->GetType() == Entity_Projectile && ((Projectile*)_other)->GetOwner()->GetType() != Entity_EnemyShip)
		|| _other->GetType() == Entity_Reveal )
	{
		// TODO:: spawn ship, possibly, do animation, spawn particles
		if(rand()%2 != 0)
			AIManager::GetInstance()->SpawnEnemy(this->GetPos());
		this->SetIsAlive(false);
	}
}
