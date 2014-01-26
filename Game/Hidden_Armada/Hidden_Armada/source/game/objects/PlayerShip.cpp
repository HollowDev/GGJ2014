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

	m_RechargeTimer = 2.0f;
	m_LastHit = 2.0f;
	m_InvulnTimer = 0.0f;
	m_Boosting = false;
	m_BoostSpeed = GetMaxSpeed() + 100;
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

	m_Shield->SetPos(GetPos() + D3DXVECTOR2(10,14));

	if(m_InvulnTimer != 0.0f)
		m_InvulnTimer -= _dt;

	if(m_InvulnTimer <= 0.0f)
		m_InvulnTimer = 0.0f;

	if(GetPos().x - GetSize() < 0)
	{
		SetPos(D3DXVECTOR2((float)(0 + GetSize()), GetPos().y));
		//SetVel(D3DXVECTOR2(-GetVel().x, GetVel().y));
	}
	
	if(GetPos().x + GetSize() * 4 > 1024 * 4)
	{
		SetPos(D3DXVECTOR2((float)(1024*4 - GetSize() * 4), GetPos().y));
		//SetVel(D3DXVECTOR2(-GetVel().x, GetVel().y));
	}

	if(GetPos().y - GetSize() < 0)
	{
		SetPos(D3DXVECTOR2(GetPos().x, (float)(0 + GetSize())));
		//SetVel(D3DXVECTOR2(GetVel().x, -GetVel().y));
	}
	
	if(GetPos().y + GetSize() * 4 > 768 * 4)
	{
		SetPos(D3DXVECTOR2(GetPos().x, (float)(768*4 - GetSize() * 4)));
		//SetVel(D3DXVECTOR2(GetVel().x, -GetVel().y));
	}

	if(GetHP() > 0)
	{
		m_Input->CheckInput(this, nullptr, m_Camera);

		m_LastHit += _dt;
		if(m_LastHit >= 2.0f)
		{
			m_LastHit = 2.0f;
			m_RechargeTimer += _dt;
			if(m_RechargeTimer >= 0.75f)
			{
				m_RechargeTimer = 0.0f;
				m_Shield->SetCurrShield(m_Shield->GetCurrShield() + 1);
				if(m_Shield->GetCurrShield() > m_Shield->GetMaxShield())
					m_Shield->SetCurrShield(m_Shield->GetMaxShield());
			}
		}
	}
	else
	{
		m_RespawnTimer -= _dt;
		if(m_RespawnTimer <= 0.0f)
		{
			m_InvulnTimer = 4.0f;
			m_RespawnTimer = 3.0f;
			m_Shield->SetCurrShield(m_Shield->GetMaxShield());
			SetHP(GetMaxHP());
		}
	}

	if(m_Boosting)
	{
		m_BoostTrailSpawn -= _dt;
		
		if(m_BoostTrailSpawn <= 0.0f)
		{
			IEntity* trail;
			for(float deg = -90.0f; deg <= 90.0f; deg+=45.0f)
			{
				ObjectFactory::GetInstance()->Create(&trail,Entity_BoostTrail);
				((BaseEntity*)trail)->SetPos(this->GetPos() + this->GetImgCenter() - ((BaseEntity*)trail)->GetImgCenter() + GetDir()*-16.0f);
				D3DXVECTOR2 forward = Rotate2D( GetDir(), D3DXToRadian(deg) );
				((BaseEntity*)trail)->SetDir(forward);
			}
			m_BoostTrailSpawn = 0.1f;
		}
		this->SetMaxSpeed(m_BoostSpeed);
	}
	else
		this->SetMaxSpeed(m_BoostSpeed-100);
	
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
	else if(_other->GetType() == Entity_Projectile && m_InvulnTimer == 0.0f)
	{
		if(m_Shield->GetCurrShield() > 0)
		{
			m_Shield->SetRender(true);
			m_Shield->SetRenderTimer(0.0f);
			m_Shield->SetCurrShield(m_Shield->GetCurrShield() - 1);
		}
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

				m_Score -= 1000;
				if(m_Score < 0)
					m_Score = 0;
			}
		}
		m_LastHit = 0.0f;
	}
}

void PlayerShip::FireWeapon( void )
{
	if(!m_Boosting)
	{
		this->GetWeapon()->Fire(this);
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

void PlayerShip::UseBoost( void )
{
	m_Boosting = true;
}