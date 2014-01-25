#ifndef _SHIP_H_
#define _SHIP_H_

#include "BaseEntity.h"
#include "Weapon.h"

class Ship : public BaseEntity
{
	Weapon* m_Weapon;

	int m_HP;
	int m_MaxHP;

public:
	Ship( void );
	~Ship( void ) { Release(); }

	virtual void Initialize( const char* _filepath, D3DXVECTOR2 _pos, int _weaponID );
	virtual void Release( void );

	virtual void Render( int _x, int _y );
	virtual void Update( float _dt );
	virtual bool CheckCollision( IEntity* _other );
	virtual void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY );

	virtual Sphere GetSphere( void ) { return Sphere(GetPos()+this->GetImgCenter(), float(this->GetSize())); }

	void RotateWeaponToMouse( int _mouseX, int _mouseY );

	// accessors
	inline int GetHP( void ) { return m_HP; }
	inline int GetMaxHP( void ) { return m_MaxHP; }
	inline Weapon* GetWeapon( void ) { return m_Weapon; }

	// mutators
	inline void SetHP( int _hp ) { m_HP = _hp; }
	inline void SetMaxHP( int _maxHP ) { m_MaxHP = _maxHP; }
	inline void SetWeapon( Weapon* _weapon ) { m_Weapon = _weapon; }
};

#endif