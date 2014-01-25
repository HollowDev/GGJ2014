#ifndef _IENTITY_H_
#define _IENTITY_H_

enum Entity_Type
{
	Entity_None = 0, Entity_PlayerShip, Entity_EnemyShip, Entity_Projectile,
	Entity_NumTypes
};

class IEntity
{
protected:
	Entity_Type m_Type;
public:
	virtual ~IEntity( void ) = 0 {}

	// The Interface
	virtual void Release( void ) = 0;

	virtual void Render( int _x, int _y ) = 0;
	virtual void Update( float _dt ) = 0;
	virtual void HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY ) = 0;
};

#endif