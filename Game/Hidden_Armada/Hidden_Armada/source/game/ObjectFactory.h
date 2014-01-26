#ifndef _OBJECT_FACTORY_H_
#define _OBJECT_FACTORY_H_

#include <vector>
using std::vector;

#include "objects\Asteroids.h"
#include "objects\Projectile.h"
#include "objects\EnemyShip.h"
#include "objects\Powerup.h"
#include "objects\Explosion.h"
#include "objects\LaserBeam.h"
#include "objects\Shield.h"
#include "objects\Reveal.h"
#include "objects\BoostTrail.h"
#include "objects\BossEnemy.h"

#define MAX_ASTEROIDS	1000
#define MAX_ENEMYSHIPS	1000
#define MAX_PROJECTILES	3000
#define MAX_POWERUPS	1000
#define MAX_EXPLOSIONS	3000
#define MAX_LASERBEAMS	50
#define MAX_SHIELDS		50
#define MAX_REVEAL		50
#define MAX_BOOST_TRAIL	100
#define MAX_BOSSES		10

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
	LaserBeam m_LaserBeamArray[MAX_LASERBEAMS];
	Shield m_ShieldArray[MAX_SHIELDS];
	Reveal m_RevealArray[MAX_REVEAL];
	BoostTrail m_BoostTrailArray[MAX_BOOST_TRAIL];
	BossEnemy m_BossArray[MAX_BOSSES];

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