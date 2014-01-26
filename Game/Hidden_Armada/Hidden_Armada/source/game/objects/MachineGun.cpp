#include "MachineGun.h"
#include "../ObjectFactory.h"
#include "Projectile.h"
#include "../AssetManager.h"

MachineGun::MachineGun( void )
{
	m_WeaponType = (int)Weapon_MachineGun;
}

void MachineGun::Initialize( void )
{
	RECT source = {0,0,64,64};
	BaseEntity::Initialize(AssetManager::GetInstance()->GetAsset(Asset_WeaponMachineGun01),source,D3DXVECTOR2(32,32),D3DXVECTOR2(0,0),0,0);
}

void MachineGun::Release( void )
{

}

void MachineGun::Render( int _x, int _y )
{
	Weapon::Render(_x,_y);
}

void MachineGun::Update( float _dt )
{
	if(m_PrevLevel != m_Level)
	{
		if(m_Level == 1)
			this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_WeaponMachineGun01));
		else if(m_Level == 2)
			this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_WeaponMachineGun02));
		else
			this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_WeaponMachineGun03));
	}

	Weapon::Update(_dt);
}

void MachineGun::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{

}

void MachineGun::Fire( IEntity* _owner )
{
	if(m_FireTimer <= 0.0f)
	{
		// Fire projectile
		IEntity* proj;
		if( ObjectFactory::GetInstance()->Create(&proj,Entity_Projectile) )
		{
			((Projectile*)proj)->Initialize();
			((Projectile*)proj)->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_MachineGunProjectile));
			((Projectile*)proj)->SetPos(GetPos() + GetImgCenter());
			((Projectile*)proj)->SetDir(GetDir());
			((Projectile*)proj)->SetMaxSpeed(500);
			((Projectile*)proj)->Rotate();
			((Projectile*)proj)->SetOwner(_owner);
		}
		// update fire timer
		m_FireTimer = m_ROF;
	}
}