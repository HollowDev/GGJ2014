#include "LaserGun.h"
#include "../ObjectFactory.h"
#include "Projectile.h"
#include "../AssetManager.h"

#include "../../engine/renderer/TextureManager.h"

LaserGun::LaserGun( void )
{
	m_Type = 69;
	m_WeaponType = (int)Weapon_Laser;
	m_LaserBeam = nullptr;
	m_Firing = false;
}

void LaserGun::Initialize( void )
{
	RECT source = {0,0,64,64};
	BaseEntity::Initialize(AssetManager::GetInstance()->GetAsset(Asset_WeaponLaser01),source,D3DXVECTOR2(32,32),D3DXVECTOR2(0,0),0,0);
}

void LaserGun::Release( void )
{

}

void LaserGun::Render( int _x, int _y )
{
	Weapon::Render(_x,_y);
}

void LaserGun::Update( float _dt )
{
	if(m_PrevLevel != m_Level)
	{
		if(m_Level == 1)
			this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_WeaponLaser01));
		else if(m_Level == 2)
			this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_WeaponLaser02));
		else
			this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_WeaponLaser03));
	}

	Weapon::Update(_dt);

	if(!m_Firing && m_LaserBeam)
		m_LaserBeam->SetIsAlive(false);

	m_Firing = false;
}

bool LaserGun::CheckCollision( IEntity* _other )
{
	if(_other->GetType() != Entity_PlayerShip)
		return true;

	return false;
}

void LaserGun::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{
}

void LaserGun::Fire( IEntity* _owner )
{
	m_Firing = true;
	if(m_LaserBeam == nullptr || m_LaserBeam->GetIsAlive() == false)
	{
		ObjectFactory::GetInstance()->Create(((IEntity**)&m_LaserBeam),Entity_LaserBeam);
	}
	m_LaserBeam->SetIsAlive(true);
	m_LaserBeam->SetPos(this->GetPos());
	m_LaserBeam->SetDir(this->GetDir());
	m_LaserBeam->SetRot(this->GetRot());
	m_LaserBeam->SetOwner(_owner);
}