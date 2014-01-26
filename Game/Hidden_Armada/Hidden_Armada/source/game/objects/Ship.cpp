#include "Ship.h"
#include <fstream>
using std::fstream;

#include "../ObjectFactory.h"
#include "Projectile.h"

Ship::Ship( void )
{
	m_Type = Entity_PlayerShip;

	m_HP = 0;
	m_MaxHP = 0;
	m_Weapon = nullptr;
}

void Ship::Initialize( const char* _filepath, D3DXVECTOR2 _pos, int _weaponID )
{
	fstream file(_filepath, std::ios_base::in);
	if(file.is_open())
	{
		D3DXVECTOR2 center;
		file >> center.x;
		file >> center.y;
		this->SetImgCenter(center);

		float maxSpeed;
		file >> maxSpeed;
		this->SetMaxSpeed(maxSpeed);

		file.close();
	}

	this->SetSize(20);
	this->SetPos(_pos);

	m_MachineGun.Initialize();
	m_LaserGun.Initialize();
	m_RaptorGun.Initialize();

	SwitchWeapons(0);
}

void Ship::Release( void )
{

}

void Ship::Render( int _x, int _y )
{
	BaseEntity::Render(_x,_y);
	
	// render the weapon
	m_Weapon->Render(_x,_y);
}

void Ship::Update( float _dt )
{
	BaseEntity::Update(_dt);

	// Update weapon, for it's dir
	m_Weapon->Update(_dt);
	D3DXVECTOR2 offset = this->GetPos() + this->GetImgCenter()/2;
	m_Weapon->SetPos(offset);
}

bool Ship::CheckCollision( IEntity* _other )
{
	if(_other->GetType() != Entity_Projectile)
		return true;

	return false;
}

void Ship::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{
	if(_other->GetType() != Entity_Projectile)
		this->SetPos( this->GetPos() + D3DXVECTOR2(_dirX,_dirY) * _dist);
}

void Ship::RotateWeaponToMouse( Weapon* _weapon, int _mouseX, int _mouseY )
{
	// Calculate the vector from this token to the Target's position
	D3DXVECTOR2 vToTarget(0,0);
	D3DXVECTOR2 tDefault(0,-1);

	vToTarget.x = _mouseX - (_weapon->GetPos().x + _weapon->GetImgCenter().x);
	vToTarget.y = _mouseY - (_weapon->GetPos().y + _weapon->GetImgCenter().y);

	// Calculate forward vector
	D3DXVECTOR2 forward = Rotate2D( tDefault, _weapon->GetRot() );
	// calculate the angle between the vectors
	float angle = AngleBetweenVectors( vToTarget, forward );

	if(Steering(forward, vToTarget) < 0.0f)
		_weapon->SetRot(_weapon->GetRot() - angle);
	else
		_weapon->SetRot(_weapon->GetRot() + angle);

	D3DXVec2Normalize(&vToTarget,&vToTarget);
	_weapon->SetDir(vToTarget);
}

void Ship::SwitchWeapons( int _weaponID )
{
	if(m_Weapon && m_Weapon->GetWeaponType() == Weapon_Laser)
	{
		if(m_LaserGun.GetLaserBeam())
			m_LaserGun.GetLaserBeam()->SetIsAlive(false);
	}

	if(_weaponID == Weapon_MachineGun)
	{
		m_MachineGun.SetLevel(1);
		m_Weapon = &m_MachineGun;
	}
	else if(_weaponID == Weapon_Laser)
	{
		m_LaserGun.SetLevel(1);
		m_Weapon = &m_LaserGun;
	}
	else if(_weaponID == Weapon_Missle)
	{
		m_RaptorGun.SetLevel(1);
		m_Weapon = &m_RaptorGun;
	}
}