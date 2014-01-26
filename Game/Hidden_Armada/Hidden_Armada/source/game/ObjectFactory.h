#ifndef _OBJECT_FACTORY_H_
#define _OBJECT_FACTORY_H_

#include <vector>
using std::vector;

#include "objects\Asteroids.h"
#include "objects\Projectile.h"
#include "objects\EnemyShip.h"
#include "objects\Powerup.h"
#include "objects\Explosion.h"

#define MAX_ASTEROIDS	200
#define MAX_ENEMYSHIPS	2000
#define MAX_PROJECTILES	200
#define MAX_POWERUPS	100
#define MAX_EXPLOSIONS	200

class ObjectManager;
class ObjectFactory
{
	ObjectManager* m_OM;

	vector<unsigned int> m_OpenList[Entity_NumTypes];
	vector<IEntity*> m_Destroyed[Entity_NumTypes];

	Asteroids m_AsteroidArray[MAX_ASTEROIDS];
	Projectile m_ProjectileArray[MAX_PROJECTILES];
	EnemyShip m_EnemyShipArray[MAX_ENEMYSHIPS];
	Powerup m_PowerupArray[MAX_POWERUPS];
	Explosion m_ExplosionArray[MAX_EXPLOSIONS];

	static ObjectFactory m_Instance;

	ObjectFactory( void ) {}
	~ObjectFactory( void ) {}

	void MakeDefault( IEntity& _object );
	bool IsValid( int _id, int _index );
public:
	static ObjectFactory* GetInstance( void ) { return &m_Instance; }

	void Initialize( void );

	bool Create( IEntity** _object, Entity_Type _id );
	bool Destroy( IEntity* _object );
	void ProcessDestroy( void );

};

#endif