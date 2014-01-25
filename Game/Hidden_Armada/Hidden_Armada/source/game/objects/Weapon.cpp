#include "Weapon.h"
#include "../ObjectFactory.h"
#include "Projectile.h"

Weapon::Weapon( void )
{
	m_FireTimer = 0.0f;
	m_ROF = 0.1f;
	m_Damage = 1;
	m_Level = 1;
}

void Weapon::Release( void )
{

}

void Weapon::Render( int _x, int _y )
{
	BaseEntity::Render(_x,_y);
}

void Weapon::Update( float _dt )
{
	// don't update dat position shiz
	if(m_FireTimer > 0.0f)
		m_FireTimer -= _dt;
}

void Weapon::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{
	// no collision
}

void Weapon::Fire( IEntity* _owner )
{
	if(m_FireTimer <= 0.0f)
	{
		// Fire projectile
		IEntity* proj;
		if( ObjectFactory::GetInstance()->Create(&proj,Entity_Projectile) )
		{
			((Projectile*)proj)->Initialize();
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