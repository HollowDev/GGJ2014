#include "BaseEntity.h"
#include "../../engine/renderer/TextureManager.h"
#include "../../engine/renderer/D3D9Handler.h"

BaseEntity::BaseEntity( void )
{
	m_ImgID = -1;
	m_Pos = D3DXVECTOR2(0,0);
	m_Vel = D3DXVECTOR2(0,0);
	m_Dir = D3DXVECTOR2(0,0);
	m_MaxSpeed = 0.0f;
	m_CurrSpeed = 0.0f;
	m_Size = 0;
	m_Rot = 0.0f;
	m_ImgCenter = 0;
}

void BaseEntity::Initialize( int _imgID, RECT _imgSource, int _imgCenter, D3DXVECTOR2 _pos, float _maxSpeed, int _size )
{
	m_ImgID = _imgID;
	m_ImgSource = _imgSource;
	m_ImgCenter = _imgCenter;
	m_Pos = _pos;
	m_MaxSpeed = _maxSpeed;
	m_Size = _size;
}

void BaseEntity::Release( void )
{

}

void BaseEntity::Render( int _x, int _y )
{
	if( m_ImgID != -1 )
	{
		TextureManager::GetInstance()->Draw(m_ImgID,int(m_Pos.x)+_x,int(m_Pos.y)+_y,1.0f,1.0f,&m_ImgSource,float(m_ImgCenter),float(m_ImgCenter),m_Rot);
	}

#if _DEBUG
	// RENDER DEBUG LINES
	D3D9Handler::m_Sprite->Flush();
	D3DXVECTOR2 center = m_Pos + D3DXVECTOR2(float(m_ImgCenter),float(m_ImgCenter));
	RECT collisionRect = {center.x-m_Size/2,center.y-m_Size/2,center.x+m_Size/2,center.y+m_Size/2};
	D3D9Handler::DrawEmptyRect(collisionRect, 255, 0, 0);
#endif
}

void BaseEntity::Update( float _dt )
{
	// Add the current velocity to the position.
	m_Pos += m_Vel * _dt;
	
	// Add the current speed, in the direction we're heading, to the velocity.
	m_Vel += m_Dir * m_CurrSpeed;
	// Cap max speed
	if(D3DXVec2Length(&m_Vel) > m_MaxSpeed)
	{
		D3DXVec2Normalize(&m_Vel,&m_Vel);
		m_Vel *= m_MaxSpeed;
	}

	// calculate new rotation, if we need to
	if(m_PrevDir != m_Dir)
	{
		// calculate rotation
		D3DXVECTOR2 tDefault(0,-1);

		
	}

	m_PrevDir = m_Dir;
}

void BaseEntity::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{

}

void BaseEntity::RotateToMouse( int _mouseX, int _mouseY )
{
	D3DXVECTOR2 toTarget(0,0);
	D3DXVECTOR2 tDefault(0,-1);

	toTarget = D3DXVECTOR2(float(_mouseX),float(_mouseY)) - m_Pos;
	D3DXVec2Normalize(&toTarget,&toTarget);

	// Calculate forward vector
	D3DXVECTOR2 forward = Rotate2D( tDefault, this->GetRot() );

	// calculate the angle between the vectors
	float angle = AngleBetweenVectors( tDefault, forward );

	if(Steering(forward, toTarget) < 0.0f)
		this->SetRot(this->GetRot() - angle);
	else
		this->SetRot(this->GetRot() - angle);
}

float BaseEntity::Steering( D3DXVECTOR2 _orientation, D3DXVECTOR2 _toTarget )
{
	return (_orientation.x * _toTarget.y) - (_orientation.y * _toTarget.x);
}

D3DXVECTOR2 BaseEntity::Rotate2D( D3DXVECTOR2 _vec, float _radians )
{
	//	Convert into the Cartesian coordinate system
	_vec.y *= -1.0f;

	D3DXVECTOR2 vRotated;
	vRotated.x = (cos(_radians) * _vec.x) + (sin(_radians) * _vec.y);
	vRotated.y = (-sin(_radians) * _vec.x) + (cos(_radians) * _vec.y);

	//	Convert back to our windows coordinate system
	vRotated.y *= -1.0f;

	//	Return our rotated vector
	return vRotated;
}

float BaseEntity::AngleBetweenVectors( D3DXVECTOR2 _v1, D3DXVECTOR2 _v2 )
{
	//	Dot product
	float fDot = D3DXVec2Dot(&_v1, &_v2);

	//	Length of those vectors
	float fLength =  D3DXVec2Length(&_v1) * D3DXVec2Length(&_v2);

	//	Make sure we don't get a divide by zero error.
	if (fLength == 0.0f)	return 0.0f;

	//	Calculate the angle between the two vectors
	float fAngle = acos( fDot / fLength );

	//	Make sure the number is not indefinite.  Shows up as -1.#IND00000.  Not a number.
	if (_isnan(fAngle))
		return 0.0f;

	//	Return the angle.
	return fAngle;
}