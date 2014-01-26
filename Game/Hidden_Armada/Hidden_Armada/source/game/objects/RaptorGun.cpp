#include "RaptorGun.h"
#include "../ObjectFactory.h"
#include "Projectile.h"
#include "../AssetManager.h"

RaptorGun::RaptorGun( void )
{
	m_WeaponType = (int)Weapon_Missle;
	m_ROF = 0.5f;
	
}

void RaptorGun::Initialize( void )
{
	RECT source = {0,0,64,64};
	BaseEntity::Initialize(AssetManager::GetInstance()->GetAsset(Asset_WeaponMissle01),source,D3DXVECTOR2(32,32),D3DXVECTOR2(0,0),0,0);
}

void RaptorGun::Release( void )
{

}

void RaptorGun::Render( int _x, int _y )
{
	Weapon::Render(_x,_y);
}

void RaptorGun::Update( float _dt )
{
	if(m_PrevLevel != m_Level)
	{
		if(m_Level == 1)
			this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_WeaponMissle01));
		else if(m_Level == 2)
			this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_WeaponMissle02));
		else
			this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_WeaponMissle03));
	}

	Weapon::Update(_dt);
}

void RaptorGun::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{

}

void RaptorGun::Fire( IEntity* _owner )
{
	if(m_FireTimer <= 0.0f)
	{
		// Fire projectile
		IEntity* proj;
		
		for(float deg = -90.0f; deg <= 90.0f; deg+=45.0f)
		{
			if( ObjectFactory::GetInstance()->Create(&proj,Entity_Projectile) )
			{
				((Projectile*)proj)->Initialize();
				((Projectile*)proj)->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_MissleProjectile));
				((Projectile*)proj)->SetPos(GetPos() + GetImgCenter());

				D3DXVECTOR2 forward = Rotate2D( GetDir(), D3DXToRadian(deg) );

				((Projectile*)proj)->SetDir(forward);
				((Projectile*)proj)->SetMaxSpeed(450);
				((Projectile*)proj)->Rotate();
				((Projectile*)proj)->SetIsChaining(false);
				((Projectile*)proj)->SetIsHoming(true);
				((Projectile*)proj)->SetOwner(_owner);
			}
		}
		// update fire timer
		m_FireTimer = m_ROF;
	}
}