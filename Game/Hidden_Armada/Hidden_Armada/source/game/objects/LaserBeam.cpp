#include "LaserBeam.h"

#include "../../engine/renderer/TextureManager.h"
#include "../AssetManager.h"
#include "../ObjectFactory.h"
#include "Explosion.h"

LaserBeam::LaserBeam( void )
{
	m_Type = Entity_LaserBeam;

}

void LaserBeam::Initialize( void )
{

}

void LaserBeam::Release( void )
{

}

void LaserBeam::Render( int _x, int _y )
{
	int laser_id = AssetManager::GetInstance()->GetAsset(Asset_LaserProjectile);
	RECT source = {48,0,64,32};
	for(unsigned int i = 0; i < m_Laser.size(); ++i)
	{
		TextureManager::GetInstance()->Draw(laser_id,int(m_Laser[i].x)+20+_x,int(m_Laser[i].y)+_y,1.0f,1.0f,&source,8,32,this->GetRot());
	}
	m_Laser.clear();
}

void LaserBeam::Update( float _dt )
{
	// project laser
	D3DXVECTOR2 toEnd = m_Segment.end - m_Segment.start;
	float dist = D3DXVec2Length(&toEnd);
	
	D3DXVECTOR2 endpos;
	int length = int(dist/32.0f);
	for(int i = 0; i < length; ++i)
	{
		D3DXVECTOR2 pos = this->GetPos();
		pos += GetDir() * 14.0f + GetDir() * ((float)i*32.0f);
		m_Laser.push_back(pos);
		endpos = pos;
	}

	m_Segment.start = GetPos() + GetDir()*14 + D3DXVECTOR2(28,32);
	m_Segment.end = m_Segment.start + GetDir()*1280;

	m_PrevDist = FLT_MAX;

	if(m_CanDamage <= 0.0f)
	{
		m_CanDamage = 0.25f;
	}

	m_CanDamage -= _dt;
}

bool LaserBeam::CheckCollision( IEntity* _other ) 
{ 
	if(_other->GetType() == Entity_Asteroid)
		return true;

	if(_other != m_Owner && _other->GetType() != m_Owner->GetType() && m_CanDamage <= 0.0f)
		return true;

	return false; 
}
void LaserBeam::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{
	if(_dist < m_PrevDist && _other->GetType() == Entity_Asteroid)
	{
		m_Segment.end = m_Segment.start + GetDir()*_dist;
		m_PrevDist = _dist;
	}
	else if(_other->GetType() == Entity_EnemyShip)
	{
		D3DXVECTOR2 offset(float(rand()%20-10),float(rand()%20-10));

		IEntity* explosion;
		ObjectFactory::GetInstance()->Create(&explosion,Entity_Explosion);
		((Explosion*)explosion)->Initialize(false);
		((BaseEntity*)explosion)->SetPos( ((BaseEntity*)_other)->GetPos()+((BaseEntity*)_other)->GetImgCenter()+offset - ((BaseEntity*)explosion)->GetImgCenter() );
	}
}
