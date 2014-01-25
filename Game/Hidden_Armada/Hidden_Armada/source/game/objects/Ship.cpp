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

	RECT source = {0,0,64,64};
	m_Weapon = new Weapon();
	m_Weapon->Initialize(_weaponID,source,D3DXVECTOR2(32,32),D3DXVECTOR2(0,0),0,0);
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

void Ship::RotateWeaponToMouse( int _mouseX, int _mouseY )
{
	// Calculate the vector from this token to the Target's position
	D3DXVECTOR2 vToTarget(0,0);
	D3DXVECTOR2 tDefault(0,-1);

	vToTarget.x = _mouseX - (m_Weapon->GetPos().x + m_Weapon->GetImgCenter().x);
	vToTarget.y = _mouseY - (m_Weapon->GetPos().y + m_Weapon->GetImgCenter().y);

	// Calculate forward vector
	D3DXVECTOR2 forward = Rotate2D( tDefault, m_Weapon->GetRot() );
	// calculate the angle between the vectors
	float angle = AngleBetweenVectors( vToTarget, forward );

	if(Steering(forward, vToTarget) < 0.0f)
		m_Weapon->SetRot(m_Weapon->GetRot() - angle);
	else
		m_Weapon->SetRot(m_Weapon->GetRot() + angle);

	D3DXVec2Normalize(&vToTarget,&vToTarget);
	m_Weapon->SetDir(vToTarget);
}
