#include "EnemyShip.h"

#include "../ObjectFactory.h"
#include "../../engine/renderer/TextureManager.h"
#include "../../engine/sound/SoundManager.h"
#include "../AssetManager.h"
#include "Powerup.h"
#include "Explosion.h"
#include "PlayerShip.h"

EnemyShip::EnemyShip( void )
{
	this->m_Type = Entity_EnemyShip;
	m_Target = nullptr;
}

void EnemyShip::Initialize( const char* _filepath, D3DXVECTOR2 _pos, int _weaponID )
{
	Ship::Initialize(_filepath,_pos,_weaponID);
	this->GetWeapon()->SetROF(1.5f);
}

void EnemyShip::Release( void )
{

}

void EnemyShip::Render( int _x, int _y )
{
	Ship::Render(_x,_y);
}

void EnemyShip::Update( float _dt )
{
	Ship::Update(_dt);

	if(m_Target != nullptr)
	{
		TurnToTarget(_dt);
		this->SetVel( this->GetDir() * this->GetMaxSpeed() );

		D3DXVECTOR2 pos = m_Target->GetPos() + m_Target->GetImgCenter();
		RotateWeaponToMouse(this->GetWeapon(),(int)pos.x,(int)pos.y);

		this->GetWeapon()->Fire(this);
	}

	if(this->GetHP() <= 0)
	{
		this->SetIsAlive(false);

		((PlayerShip*)m_Target)->AddToScore( 100 );

		IEntity* powerup;
		ObjectFactory::GetInstance()->Create(&powerup,Entity_Powerup);
		((BaseEntity*)powerup)->SetImgID(TextureManager::GetInstance()->LoadTexture(L"assets/textures/powerups/powerups1.png"));
		((BaseEntity*)powerup)->SetPos(this->GetPos()+this->GetImgCenter());
		((Powerup*)powerup)->SetLife(10.0f);

		IEntity* explosion;
		ObjectFactory::GetInstance()->Create(&explosion,Entity_Explosion);
		((Explosion*)explosion)->Initialize(true);
		((BaseEntity*)explosion)->SetPos( this->GetPos() );
		
		SoundManager::GetInstance()->Play(AssetManager::GetInstance()->GetAsset(Asset_S_Explosion03),false,false);
	}
}

void EnemyShip::TurnToTarget( float _dt )
{
	// Calculate the vector from this token to the Target's position
	D3DXVECTOR2 vToTarget(0,0);
	D3DXVECTOR2 tDefault(0,-1);

	D3DXVECTOR2 pos = m_Target->GetPos() + m_Target->GetImgCenter();
	vToTarget.x = pos.x - (this->GetPos().x + this->GetImgCenter().x);
	vToTarget.y = pos.y - (this->GetPos().y + this->GetImgCenter().y);

	// Calculate forward vector
	D3DXVECTOR2 forward = Rotate2D( tDefault, this->GetRot() );
	// calculate the angle between the vectors
	float angle = AngleBetweenVectors( vToTarget, forward );

	if(Steering(forward, vToTarget) < 0.0f)
		this->SetRot(this->GetRot() - 2.0f*_dt);
	else
		this->SetRot(this->GetRot() + 2.0f*_dt);

	forward = Rotate2D( tDefault, this->GetRot() );
	D3DXVec2Normalize(&forward,&forward);
	this->SetDir(forward);
}

bool EnemyShip::CheckCollision( IEntity* _other )
{
	if(_other->GetType() == Entity_Powerup)
		return false;

	return true;
}

void EnemyShip::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{
	if(!_other->GetIsAlive())
		return;

	if(_other->GetType() != Entity_Projectile && _other->GetType() != Entity_LaserBeam)
		this->SetPos( this->GetPos() + D3DXVECTOR2(_dirX,_dirY) * _dist);
	else if(_other->GetType() == Entity_Projectile || _other->GetType() == Entity_LaserBeam )
		this->SetHP(this->GetHP()-1);
}
