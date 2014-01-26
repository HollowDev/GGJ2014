#include "PlayerShip.h"
#include <fstream>
using std::fstream;

#include "../ObjectFactory.h"
#include "Projectile.h"
#include "../camera/Camera.h"
#include "../../engine/sound/SoundManager.h"
#include "../AssetManager.h"

PlayerShip::PlayerShip( void )
{
	this->m_Type = Entity_PlayerShip;

	m_Reveal = nullptr;
}

void PlayerShip::Initialize( const char* _filepath, D3DXVECTOR2 _pos, int _weaponID, InputController* _input, Camera* _camera )
{
	Ship::Initialize(_filepath,_pos,_weaponID);
	m_Input = _input;
	m_Camera = _camera;
	m_Score = 0;
	m_RespawnTimer = 3.0f;
}

void PlayerShip::Release( void )
{

}

void PlayerShip::Render( int _x, int _y )
{
	if(this->GetHP() > 0)
		Ship::Render(_x,_y);
}

void PlayerShip::Update( float _dt )
{
	Ship::Update(_dt);

	if(GetPos().x - GetSize() < 0)
	{
		SetPos(D3DXVECTOR2(0 + GetSize(), GetPos().y));
		//SetVel(D3DXVECTOR2(-GetVel().x, GetVel().y));
	}
	
	if(GetPos().x + GetSize() * 4 > 1024 * 4)
	{
		SetPos(D3DXVECTOR2(1024*4 - GetSize() * 4, GetPos().y));
		//SetVel(D3DXVECTOR2(-GetVel().x, GetVel().y));
	}

	if(GetPos().y - GetSize() < 0)
	{
		SetPos(D3DXVECTOR2(GetPos().x, 0 + GetSize()));
		//SetVel(D3DXVECTOR2(GetVel().x, -GetVel().y));
	}
	
	if(GetPos().y + GetSize() * 4 > 768 * 4)
	{
		SetPos(D3DXVECTOR2(GetPos().x, 768*4 - GetSize() * 4));
		//SetVel(D3DXVECTOR2(GetVel().x, -GetVel().y));
	}

	if(GetHP() > 0)
	{
		m_Input->CheckInput(this, nullptr, m_Camera);
	}
	else
	{
		m_RespawnTimer -= _dt;
		if(m_RespawnTimer <= 0.0f)
		{
			m_RespawnTimer = 3.0f;
			m_Shield->SetCurrShield(m_Shield->GetMaxShield());
			SetHP(GetMaxHP());
		}
	}
	
}

bool PlayerShip::CheckCollision( IEntity* _other )
{
	if(GetHP() <= 0)
		return false;

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
	else if(_other->GetType() == Entity_Projectile)
	{
		if(m_Shield->GetCurrShield() > 0)
			m_Shield->SetCurrShield(m_Shield->GetCurrShield() - 1);
		else
		{
			SetHP(GetHP() - 1);
			if(this->GetHP() <= 0 && m_RespawnTimer == 3.0f)
			{
				IEntity* explosion;
				ObjectFactory::GetInstance()->Create(&explosion,Entity_Explosion);
				((Explosion*)explosion)->Initialize(true,true);
				((BaseEntity*)explosion)->SetPos( this->GetPos() );
				this->SetVel(D3DXVECTOR2(0,0));
				
				SoundManager::GetInstance()->Play(AssetManager::GetInstance()->GetAsset(Asset_S_ExplosionS),false,false);
			}
		}
	}
}

void PlayerShip::UseReveal( void )
{
	if(!m_Reveal || !m_Reveal->GetIsAlive())
	{
		ObjectFactory::GetInstance()->Create(&m_Reveal,Entity_Reveal);
		((BaseEntity*)m_Reveal)->SetDir(this->GetWeapon()->GetDir());
		((BaseEntity*)m_Reveal)->SetRot(this->GetWeapon()->GetRot());
		((BaseEntity*)m_Reveal)->SetPos(this->GetPos()+this->GetImgCenter());
	}

}