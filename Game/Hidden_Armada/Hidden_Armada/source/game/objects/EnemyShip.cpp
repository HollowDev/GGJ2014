#include "EnemyShip.h"

EnemyShip::EnemyShip( void )
{
	m_Target = nullptr;
}

void EnemyShip::Initialize( void )
{

}

void EnemyShip::Release( void )
{

}

void EnemyShip::Render( int _x, int _y )
{
	Ship::Render(_x,_y);


}

void EnemyShip::Update( float _dt )
{
	Ship::Update(_dt);
}

bool EnemyShip::CheckCollision( IEntity* _other )
{

}

void EnemyShip::HandleCollision( IEntity* _other, float _dist, float _dirX, float _dirY )
{

}
