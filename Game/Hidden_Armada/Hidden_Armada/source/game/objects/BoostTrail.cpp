#include "BoostTrail.h"
#include "../AssetManager.h"
#include "../../engine/renderer/TextureManager.h"

BoostTrail::BoostTrail( void )
{
	this->m_Type = Entity_BoostTrail;
}

void BoostTrail::Initialize( void )
{
	this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_BoostTrail));
	RECT source = {0,0,32,32};
	this->SetImgSource(source);
	this->SetImgCenter(D3DXVECTOR2(16,16));
	this->SetSize(12);
	m_Life = 1.0f;
}

void BoostTrail::Release( void )
{

}

void BoostTrail::Render( int _x, int _y )
{
	DWORD color = D3DCOLOR_ARGB(int(255.0f*(m_Life/1.0f)), 255, 255, 255);
	TextureManager::GetInstance()->Draw(GetImgID(),int(GetPos().x)+_x,int(GetPos().y)+_y,1.0f,1.0f,&GetImgSource(),GetImgCenter().x,GetImgCenter().x,GetRot(),color);
}

void BoostTrail::Update( float _dt )
{
	BaseEntity::Update(_dt);

	this->SetVel(-this->GetDir() * 50);

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
