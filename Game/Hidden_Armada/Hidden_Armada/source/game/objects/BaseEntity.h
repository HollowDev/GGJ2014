#ifndef _BASE_ENTITY_H_
#define _BASE_ENTITY_H_

#include "IEntity.h"
#include "../../engine/directx9.h"
#include "../../engine/windows.h"

class BaseEntity : public IEntity
{
	int			m_ImgID;		// img reference int
	RECT		m_ImgSource;	// area to render on the img
	int			m_ImgCenter;	// distance to center
	
	D3DXVECTOR2 m_Pos;			// position of the entity
	D3DXVECTOR2 m_Vel;			// current velocity
	D3DXVECTOR2 m_Dir;			// current heading/direction
	D3DXVECTOR2 m_PrevDir;		// previous heading
	float		m_CurrSpeed;	// current speed
	float		m_MaxSpeed;		// maximum speed

	int			m_Size;			// size of the object (radius for collision)
	float		m_Rot;			// rotation of the object, based on the direction

public:
	BaseEntity( void );
	~BaseEntity( void ) { Release(); }

	void Initialize( int _imgID, RECT _imgSource, int _imgCenter, D3DXVECTOR2 _pos, float _maxSpeed, int _size );
	virtual void Release( void );

	virtual void Render( int _x, int _y );
	virtual void Update( float _dt );
	virtual void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );

	void RotateToMouse( int _mouseX, int _mouseY );
	float AngleBetweenVectors( D3DXVECTOR2 _v1, D3DXVECTOR2 _v2 );
	D3DXVECTOR2 Rotate2D( D3DXVECTOR2 _vec, float _radians );
	float Steering( D3DXVECTOR2 _orientation, D3DXVECTOR2 _toTarget );

	// Accessors
	inline int GetImgID( void ) { return m_ImgID; }
	inline RECT GetImgSource( void ) { return m_ImgSource; }
	inline int GetImgCenter( void ) { return m_ImgCenter; }
	inline D3DXVECTOR2 GetPos( void ) { return m_Pos; }
	inline D3DXVECTOR2 GetVel( void ) { return m_Vel; }
	inline D3DXVECTOR2 GetDir( void ) { return m_Dir; }
	inline float GetMaxSpeed( void ) { return m_MaxSpeed; }
	inline float GetCurrSpeed( void ) { return m_CurrSpeed; }
	inline int GetSize( void ) { return m_Size; }
	inline float GetRot( void ) { return m_Rot; }

	// Mutators
	inline void SetImgID( int _imgID ) { m_ImgID = _imgID; }
	inline void SetImgSource( RECT _imgSource ) { m_ImgSource = _imgSource; }
	inline void SetImgCenter( int _imgCenter ) { m_ImgCenter = _imgCenter; }
	inline void SetPos( D3DXVECTOR2 _pos ) { m_Pos = _pos; }
	inline void SetVel( D3DXVECTOR2 _vel ) { m_Vel = _vel; }
	inline void SetDir( D3DXVECTOR2 _dir ) { m_Dir = _dir; }
	inline void SetMaxSpeed( float _maxSpeed ) { m_MaxSpeed = _maxSpeed; }
	inline void SetCurrSpeed( float _currSpeed ) { m_CurrSpeed = _currSpeed; }
	inline void SetSize( int _size ) { m_Size = _size; }
	inline void SetRot( float _rot ) { m_Rot = _rot; }
};

#endif