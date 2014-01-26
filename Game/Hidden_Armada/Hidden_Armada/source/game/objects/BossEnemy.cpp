#include "BossEnemy.h"
#include "../AssetManager.h"
#include "../../engine/memory_macros.h"

BossEnemy::BossEnemy( void )
{
	this->m_Type = Entity_Boss;

	for(int i = 0; i < 4; ++i)
		m_Cannons[i] = nullptr;

	m_SpecialRot = 0.0f;
}

void BossEnemy::Initialize( void )
{
	this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_CrimsonDoom));
	this->SetImgCenter(D3DXVECTOR2(64,64));
	RECT source = {0,0,128,128};
	this->SetImgSource(source);

	this->SetSize(64);
	this->SetMaxSpeed(50);
	this->SetHP(100);
	this->SetMaxHP(100);

	// 38, 38		90, 38
	//
	// 38, 90		90, 90
	m_Offsets[0] = D3DXVECTOR2(38,38) - this->GetImgCenter() - D3DXVECTOR2(32,32);
	m_Offsets[1] = D3DXVECTOR2(90,38) - this->GetImgCenter() - D3DXVECTOR2(32,32);
	m_Offsets[2] = D3DXVECTOR2(38,90) - this->GetImgCenter() - D3DXVECTOR2(32,32);
	m_Offsets[3] = D3DXVECTOR2(90,90) - this->GetImgCenter() - D3DXVECTOR2(32,32);

	for(int i = 0; i < 4; ++i)
	{
		m_Cannons[i] = new MachineGun();
		m_Cannons[i]->Initialize();
		m_Cannons[i]->SetROF(1.0f);
	}
}

void BossEnemy::Release( void )
{
	for(int i = 0; i < 4; ++i)
		SAFE_DELETE(m_Cannons[i]);
}

void BossEnemy::Render( int _x, int _y )
{
	BaseEntity::Render(_x,_y);

	for(int i = 0; i < 4; ++i)
		m_Cannons[i]->Render(_x,_y);
}

void BossEnemy::Update( float _dt )
{
	BaseEntity::Update(_dt);

	if(m_Target != nullptr)
	{
		TurnToTarget(_dt);
		this->SetVel( this->GetDir() * this->GetMaxSpeed() );

		D3DXVECTOR2 pos = m_Target->GetPos() + m_Target->GetImgCenter();

		for(int i = 0; i < 4; ++i)
		{
			RotateWeaponToMouse(m_Cannons[i],(int)pos.x,(int)pos.y);
			m_Cannons[i]->Fire(this);
		}
	}

	// Update weapon, for it's dir
	for(int i = 0; i < 4; ++i)
	{
		m_Cannons[i]->Update(_dt);
		D3DXVECTOR2 offset = this->GetPos() - m_Offsets[i];
		m_Cannons[i]->SetPos(offset);
	}
}

bool BossEnemy::CheckCollision( IEntity* _other )
{
	if(_other->GetType() == Entity_Powerup)
		return false;

	return false;
}

void BossEnemy::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{
	if(!_other->GetIsAlive())
		return;

	if(_other->GetType() != Entity_Projectile && _other->GetType() != Entity_LaserBeam)
		this->SetPos( this->GetPos() + D3DXVECTOR2(_dirX,_dirY) * _dist);
	else if(_other->GetType() == Entity_Projectile || _other->GetType() == Entity_LaserBeam )
		this->SetHP(this->GetHP()-1);
}