#include "LaserBeam.h"

#include "../../engine/renderer/TextureManager.h"
#include "../../engine/renderer/D3D9Handler.h"
#include "../AssetManager.h"

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
	
	int length = int(dist/32.0f);
	for(unsigned int i = 0; i < length; ++i)
	{
		D3DXVECTOR2 pos = this->GetPos();
		pos += GetDir() * 14 + GetDir() * (i*32);
		m_Laser.push_back(pos);
	}

	m_Segment.start = GetPos() + GetDir()*14 + D3DXVECTOR2(28,32);
	m_Segment.end = m_Segment.start + GetDir()*1280;

	m_PrevDist = FLT_MAX;
}

bool LaserBeam::CheckCollision( IEntity* _other ) 
{ 
	if(_other != m_Owner && _other->GetType() != m_Owner->GetType())
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
}
