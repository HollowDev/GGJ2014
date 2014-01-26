#include "PlayerShip.h"
#include <fstream>
using std::fstream;

#include "../ObjectFactory.h"
#include "Projectile.h"
#include "../camera/Camera.h"

PlayerShip::PlayerShip( void )
{
	this->m_Type = Entity_PlayerShip;
}

void PlayerShip::Initialize( const char* _filepath, D3DXVECTOR2 _pos, int _weaponID, InputController* _input, Camera* _camera )
{
	Ship::Initialize(_filepath,_pos,_weaponID);
	m_Input = _input;
	m_Camera = _camera;
}

void PlayerShip::Release( void )
{

}

void PlayerShip::Render( int _x, int _y )
{
	Ship::Render(_x,_y);
}

void PlayerShip::Update( float _dt )
{
	m_Input->CheckInput(this, nullptr, m_Camera);

	Ship::Update(_dt);
}

bool PlayerShip::CheckCollision( IEntity* _other )
{
	return true;
}

void PlayerShip::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{
	if(_other->GetType() == Entity_Powerup)
	{
		if( ((Powerup*)_other)->GetPowerType() == this->GetWeapon()->GetWeaponType() )
		{
			this->GetWeapon()->SetLevel(this->GetWeapon()->GetLevel()+1);
			if(this->GetWeapon()->GetLevel() > 3)
				this->GetWeapon()->SetLevel(3);
		}
		else 
		{
			this->SwitchWeapons(((Powerup*)_other)->GetPowerType());
		}
	}
	else if(_other->GetType() != Entity_Projectile)
		this->SetPos( this->GetPos() + D3DXVECTOR2(_dirX,_dirY) * _dist);
}