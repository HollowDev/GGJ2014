#include "Projectile.h"
#include "../AssetManager.h"
#include "../AIManager.h"
#include "../ObjectFactory.h"
#include "Explosion.h"

Projectile::Projectile( void )
{
	this->m_Type = Entity_Projectile;
	this->m_IsAlive = true;

	m_Damage = 0;
	m_Life = 0.0f;
}

void Projectile::Initialize( void )
{
	this->SetMaxSpeed(500);
	RECT source = {0,0,16,32};
	this->SetImgSource(source);
	this->SetSize(8);
	m_Life = 5.0f;
	this->SetIsAlive(true);
	this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_MachineGunProjectile));
	this->SetImgCenter(D3DXVECTOR2(8,4));
	m_Target = nullptr;

	m_SmokeTrailEmitter = ParticleManager::GetInstance()->AddEmitter(100, 0, 0, GetPos().x, GetPos().y, 1.0f, 3.5f, AssetManager::GetInstance()->GetAsset(Asset_HexParticle));
}

void Projectile::Release( void )
{

}

void Projectile::Render( int _x, int _y )
{
	BaseEntity::Render(_x,_y);
	m_SmokeTrailEmitter->Render(_x, _y);
}

void Projectile::Update( float _dt )
{
	// Add the current velocity to the position.
	this->SetPos(this->GetPos() + this->GetVel() * _dt);
	this->SetVel(this->GetVel() * 0.99f);
	
	// Cap max speed
	if(D3DXVec2Length(&this->GetVel()) > this->GetMaxSpeed())
	{
		D3DXVECTOR2 cappedVel;
		D3DXVec2Normalize(&cappedVel,&this->GetVel());
		cappedVel *= this->GetMaxSpeed();
		this->SetVel(cappedVel);
	}

	D3DXVECTOR2 vel = this->GetDir() * this->GetMaxSpeed();
	this->SetVel(vel);

	if( m_IsHoming )
	{
		// TODO:: this is for player only, change for AI.
		if(m_Target != nullptr && m_Target->GetIsAlive())
		{
			TurnToTarget(_dt);
			// TODO:: also leave smoke trail
		}
		else
		{
			if(this->m_Owner->GetType() == Entity_PlayerShip)
				m_Target = AIManager::GetInstance()->GetClosestEnemy(this->GetPos());
			else
				m_Target = AIManager::GetInstance()->GetTarget();
		}

		m_SmokeTrailEmitter->Update(_dt*2.0f, GetPos().x, GetPos().y - GetDir().y*16);
	}

	

	m_Life -= _dt;
	if(m_Life <= 0.0f)
	{
		m_Life = 5.0f;
		this->SetIsAlive(false);
	}
}

bool Projectile::CheckCollision( IEntity* _other )
{
	if( _other->GetType() == Entity_EnemyShip && m_Owner->GetType() == Entity_EnemyShip )
		return false;

	//if( _other->GetType() == Entity_Asteroid && m_Owner->GetType() == Entity_EnemyShip )
	//	return false;

	if( _other != m_Owner && _other->GetType() != Entity_Projectile )
		return true;
	
	return false;
}
void Projectile::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{
	if( _other->GetType() == Entity_EnemyShip && m_Owner->GetType() == Entity_EnemyShip )
		return;
	if( _other->GetType() != Entity_Projectile && _other != m_Owner )
	{
		this->SetIsAlive(false);
		IEntity* explosion;
		ObjectFactory::GetInstance()->Create(&explosion,Entity_Explosion);
		((Explosion*)explosion)->Initialize(true,true);
		((BaseEntity*)explosion)->SetPos( this->GetPos() - ((BaseEntity*)explosion)->GetImgCenter() );
	}
}

void Projectile::TurnToTarget( float _dt )
{
	// Calculate the vector from this token to the Target's position
	D3DXVECTOR2 vToTarget(0,0);
	D3DXVECTOR2 tDefault(0,-1);

	D3DXVECTOR2 pos = ((BaseEntity*)m_Target)->GetPos() + ((BaseEntity*)m_Target)->GetImgCenter();
	vToTarget.x = pos.x - (this->GetPos().x + this->GetImgCenter().x);
	vToTarget.y = pos.y - (this->GetPos().y + this->GetImgCenter().y);

	// Calculate forward vector
	D3DXVECTOR2 forward = Rotate2D( tDefault, this->GetRot() );
	// calculate the angle between the vectors
	float angle = AngleBetweenVectors( vToTarget, forward );

	if(Steering(forward, vToTarget) < 0.0f)
		this->SetRot(this->GetRot() - 3.0f*_dt);
	else
		this->SetRot(this->GetRot() + 3.0f*_dt);

	forward = Rotate2D( tDefault, this->GetRot() );
	D3DXVec2Normalize(&forward,&forward);
	this->SetDir(forward);
}