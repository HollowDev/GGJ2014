#include "Reveal.h"
#include "../../engine/renderer/TextureManager.h"
#include "../AssetManager.h"
#include "../../engine/renderer/D3D9Handler.h"

Reveal::Reveal( void )
{
	m_Type = Entity_Reveal;

	m_Timer = 0.5f;
	m_Scale = 0.0f;
}

void Reveal::Initialize( void )
{
	this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_Reveal));
	RECT source = {0,0,256,256};
	this->SetImgSource(source);
	this->SetImgCenter(D3DXVECTOR2(128,128));
	this->SetSize(64);
}

void Reveal::Release( void )
{

}

void Reveal::Render( int _x, int _y )
{
	int posX = (int)((GetPos().x)+_x + (1.0f-m_Scale)*GetImgCenter().x - GetImgCenter().x);
	int posY = (int)((GetPos().y)+_y + (1.0f-m_Scale)*GetImgCenter().y - GetImgCenter().y);
	TextureManager::GetInstance()->Draw(GetImgID(),posX,posY,m_Scale,m_Scale,&GetImgSource(),GetImgCenter().x,GetImgCenter().x,GetRot());

	RECT area = {(LONG)GetPos().x+_x-GetSize(),(LONG)GetPos().y+_y-GetSize(),(LONG)GetPos().x+_x+GetSize(),(LONG)GetPos().y+_y+GetSize()};
}

void Reveal::Update( float _dt )
{
	BaseEntity::Update(_dt);

	if(m_Scale < 1.0f)
		m_Scale = Lerp(1.0f,0.0f,m_Timer/0.5f);
	else
		m_Scale = 1.0f;

	this->SetVel(this->GetDir()*200);

	m_Timer -= _dt;
	if(m_Timer < -0.5f)
	{
		m_Timer = 0.5f;
		m_Scale = 0.0f;
		this->SetIsAlive(false);
	}
}

bool Reveal::CheckCollision( IEntity* _other ) 
{
	if(_other->GetType() == Entity_Asteroid)
		return true; 

	return false; 
}
void Reveal::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{
}
