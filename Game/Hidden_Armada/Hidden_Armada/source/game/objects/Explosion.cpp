#include "Explosion.h"
#include "../AssetManager.h"

Explosion::Explosion( void )
{
	this->m_Type = Entity_Explosion;

	m_FrameDur = 0.05f;
	m_FrameTimer = m_FrameDur;
	m_CurrFrame = 0;
}

void Explosion::Initialize( bool _isBig, bool _isSingularity  )
{
	m_IsBig = _isBig;
	m_IsSingularity = _isSingularity;

	if(!m_IsBig)
	{
		this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_Explosion01));
		this->SetImgCenter(D3DXVECTOR2(32,32));
		this->SetSize(32);
	}
	else
	{
		this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_Explosion02));
		this->SetImgCenter(D3DXVECTOR2(64,64));
		this->SetSize(64);
	}
	this->SetDir(D3DXVECTOR2(0,-1));

	if(m_IsSingularity)
		this->SetImgID(AssetManager::GetInstance()->GetAsset(Asset_Explosion03));
}

void Explosion::Release( void )
{

}

void Explosion::Render( int _x, int _y )
{
	int xoff = m_CurrFrame%5;
	int yoff = m_CurrFrame/5;
	if(m_IsSingularity)
	{
		xoff = m_CurrFrame%4;
		yoff = m_CurrFrame/4;
	}

	if(!m_IsBig)
	{
		RECT source = {64*xoff,64*yoff,64 + 64*xoff, 64 + 64*yoff};
		this->SetImgSource(source);
	}
	else
	{
		RECT source = {128*xoff,128*yoff,128 + 128*xoff, 128 + 128*yoff};
		this->SetImgSource(source);
	}

	BaseEntity::Render(_x,_y);
}

void Explosion::Update( float _dt )
{
	BaseEntity::Update(_dt);

	m_FrameTimer -= _dt;
	if(m_FrameTimer <= 0.0f)
	{
		m_CurrFrame++;
		if(!m_IsSingularity)
		{
			if(m_CurrFrame >= 10)
			{
				m_CurrFrame = 0;
				this->SetIsAlive(false);
			}
		}
		else
		{
			if(m_CurrFrame >= 18)
			{
				m_CurrFrame = 0;
				this->SetIsAlive(false);
			}
		}

		m_FrameTimer = m_FrameDur;
	}
}

bool Explosion::CheckCollision( IEntity* _other ) 
{ 
	return false; 
}

void Explosion::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{

}