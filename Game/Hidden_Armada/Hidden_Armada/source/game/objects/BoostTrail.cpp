#include "BoostTrail.h"
#include "../AssetManager.h"

BoostTrail::BoostTrail( void )
{
	this->m_Type = Entity_BoostTrail;
}

void BoostTrail::Initialize( void )
{
	this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_ShipThrust));
	RECT source = {0,0,16,32};
	this->SetImgSource(source);
	this->SetImgCenter(D3DXVECTOR2(8,16));
	this->SetSize(8);
	m_Life = 1.0f;
}

void BoostTrail::Release( void )
{

}

void BoostTrail::Render( int _x, int _y )
{
	BaseEntity::Render(_x,_y);
}

void BoostTrail::Update( float _dt )
{
	BaseEntity::Update(_dt);

	m_Life -= _dt;
	if(m_Life <= 0.0f)
	{
		m_Life = 1.0f;
		this->SetIsAlive(false);
	}
}

bool BoostTrail::CheckCollision( IEntity* _other ) 
{ 
	if(_other->GetType() != Entity_Projectile)
		return false;
	return true; 
}
void BoostTrail::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{

}
