#include "ObjectFactory.h"
#include "ObjectManager.h"

ObjectFactory ObjectFactory::m_Instance;

void ObjectFactory::Initialize( void )
{
	m_OM = ObjectManager::GetInstance();

	unsigned int i;
	for(i = 0; i < MAX_ASTEROIDS; ++i)
	{
		m_OpenList[Entity_Asteroid].push_back(i);
		m_AsteroidArray[i].Initialize();
	}

	for(i = 0; i < MAX_PROJECTILES; ++i)
	{
		m_OpenList[Entity_Projectile].push_back(i);
		m_ProjectileArray[i].Initialize();
	}

	for(i = 0; i < MAX_ENEMYSHIPS; ++i)
	{
		m_OpenList[Entity_EnemyShip].push_back(i);
	}

	for(i = 0; i < MAX_POWERUPS; ++i)
	{
		m_OpenList[Entity_Powerup].push_back(i);
	}

	for(i = 0; i < MAX_EXPLOSIONS; ++i)
	{
		m_OpenList[Entity_Explosion].push_back(i);
		m_ExplosionArray[i].Initialize();
	}

	for(i = 0; i < MAX_LASERBEAMS; ++i)
	{
		m_OpenList[Entity_LaserBeam].push_back(i);
		m_LaserBeamArray[i].Initialize();
	}

	for(i = 0; i < MAX_SHIELDS; ++i)
	{
		m_OpenList[Entity_Shield].push_back(i);
	}
}


bool ObjectFactory::Create( IEntity** _object, Entity_Type _id )
{
	if( !m_OpenList[_id].size() )
		return false;

	unsigned int index = m_OpenList[_id].back();
	m_OpenList[_id].pop_back();

	switch(_id)
	{
	case Entity_Asteroid:
		{
			MakeDefault(m_AsteroidArray[index]);
			*_object = &m_AsteroidArray[index];
			m_OM->AddObject(&m_AsteroidArray[index],NUM_LAYERS-1);
		}
		break;
	case Entity_Projectile:
		{
			MakeDefault(m_ProjectileArray[index]);
			*_object = &m_ProjectileArray[index];
			m_OM->AddObject(&m_ProjectileArray[index],NUM_LAYERS-1);
		}
		break;
	case Entity_EnemyShip:
		{
			MakeDefault(m_EnemyShipArray[index]);
			*_object = &m_EnemyShipArray[index];
			m_OM->AddObject(&m_EnemyShipArray[index],3);
		}
		break;
	case Entity_Powerup:
		{
			// make default here
			m_PowerupArray[index].SetPowerType(rand()%3);	// random between the three
			*_object = &m_PowerupArray[index];
			m_OM->AddObject(&m_PowerupArray[index],2);
		}
		break;
	case Entity_Explosion:
		{
			// make default here
			*_object = &m_ExplosionArray[index];
			m_OM->AddObject(&m_ExplosionArray[index],NUM_LAYERS-1);
		}
		break;
	case Entity_LaserBeam:
		{
			// make default here
			*_object = &m_LaserBeamArray[index];
			m_OM->AddObject(&m_LaserBeamArray[index],2);
		}
		break;
	case Entity_Shield:
		{
			// make default here
			*_object = &m_ShieldArray[index];
			m_OM->AddObject(&m_ShieldArray[index],3);
		}
		break;
	}
	(*_object)->SetIsAlive(true);

	return true;
}

bool ObjectFactory::Destroy( IEntity* _object )
{
	int test = -1;

	switch(_object->GetType())
	{
	case Entity_Asteroid:
		{
			test = ((int)_object-(int)&m_AsteroidArray[0]) / sizeof(Asteroids);
			if( test < 0 || test >= MAX_ASTEROIDS )
				return false;
			else if( !IsValid( Entity_Asteroid, test ) )
				return false;

			m_Destroyed[Entity_Asteroid].push_back(&m_AsteroidArray[test]);
		}
		break;
	case Entity_Projectile:
		{
			test = ((int)_object-(int)&m_ProjectileArray[0]) / sizeof(Projectile);
			if( test < 0 || test >= MAX_PROJECTILES )
				return false;
			else if( !IsValid( Entity_Projectile, test ) )
				return false;

			m_Destroyed[Entity_Projectile].push_back(&m_ProjectileArray[test]);
		}
		break;
	case Entity_EnemyShip:
		{
			test = ((int)_object-(int)&m_EnemyShipArray[0]) / sizeof(EnemyShip);
			if( test < 0 || test >= MAX_ENEMYSHIPS )
				return false;
			else if( !IsValid( Entity_EnemyShip, test ) )
				return false;

			m_Destroyed[Entity_EnemyShip].push_back(&m_EnemyShipArray[test]);
		}
	case Entity_Powerup:
		{
			test = ((int)_object-(int)&m_PowerupArray[0]) / sizeof(Powerup);
			if( test < 0 || test >= MAX_POWERUPS )
				return false;
			else if( !IsValid( Entity_Powerup, test ) )
				return false;

			m_Destroyed[Entity_Powerup].push_back(&m_PowerupArray[test]);
		}
		break;
	case Entity_Explosion:
		{
			test = ((int)_object-(int)&m_ExplosionArray[0]) / sizeof(Explosion);
			if( test < 0 || test >= MAX_EXPLOSIONS )
				return false;
			else if( !IsValid( Entity_Explosion, test ) )
				return false;

			m_Destroyed[Entity_Explosion].push_back(&m_ExplosionArray[test]);
		}
		break;
	case Entity_LaserBeam:
		{
			test = ((int)_object-(int)&m_LaserBeamArray[0]) / sizeof(LaserBeam);
			if( test < 0 || test >= MAX_LASERBEAMS )
				return false;
			else if( !IsValid( Entity_LaserBeam, test ) )
				return false;

			m_Destroyed[Entity_LaserBeam].push_back(&m_LaserBeamArray[test]);
		}
		break;
	case Entity_Shield:
		{
			test = ((int)_object-(int)&m_ShieldArray[0]) / sizeof(Shield);
			if( test < 0 || test >= MAX_SHIELDS )
				return false;
			else if( !IsValid( Entity_Shield, test ) )
				return false;

			m_Destroyed[Entity_Shield].push_back(&m_ShieldArray[test]);
		}
		break;
	}

	return true;
}

void ObjectFactory::ProcessDestroy( void )
{
	unsigned int size = 0, index = 0, i = 0;

	size = m_Destroyed[Entity_Asteroid].size();
	for(i = 0; i < size; ++i)
	{
		index = ((int)m_Destroyed[Entity_Asteroid][i]-(int)&m_AsteroidArray[0])/sizeof(Asteroids);
		m_OpenList[Entity_Asteroid].push_back(index);
		m_OM->RemoveObject(m_Destroyed[Entity_Asteroid][i],NUM_LAYERS-1);
	}
	m_Destroyed[Entity_Asteroid].clear();

	size = m_Destroyed[Entity_Projectile].size();
	for(i = 0; i < size; ++i)
	{
		index = ((int)m_Destroyed[Entity_Projectile][i]-(int)&m_ProjectileArray[0])/sizeof(Projectile);
		m_OpenList[Entity_Projectile].push_back(index);
		m_OM->RemoveObject(m_Destroyed[Entity_Projectile][i],NUM_LAYERS-1);
	}
	m_Destroyed[Entity_Projectile].clear();

	size = m_Destroyed[Entity_EnemyShip].size();
	for(i = 0; i < size; ++i)
	{
		index = ((int)m_Destroyed[Entity_EnemyShip][i]-(int)&m_EnemyShipArray[0])/sizeof(EnemyShip);
		m_OpenList[Entity_EnemyShip].push_back(index);
		m_OM->RemoveObject(m_Destroyed[Entity_EnemyShip][i],3);
	}
	m_Destroyed[Entity_EnemyShip].clear();

	size = m_Destroyed[Entity_Powerup].size();
	for(i = 0; i < size; ++i)
	{
		index = ((int)m_Destroyed[Entity_Powerup][i]-(int)&m_PowerupArray[0])/sizeof(Powerup);
		m_OpenList[Entity_Powerup].push_back(index);
		m_OM->RemoveObject(m_Destroyed[Entity_Powerup][i],2);
	}
	m_Destroyed[Entity_Powerup].clear();

	size = m_Destroyed[Entity_Explosion].size();
	for(i = 0; i < size; ++i)
	{
		index = ((int)m_Destroyed[Entity_Explosion][i]-(int)&m_ExplosionArray[0])/sizeof(Explosion);
		m_OpenList[Entity_Explosion].push_back(index);
		m_OM->RemoveObject(m_Destroyed[Entity_Explosion][i],NUM_LAYERS-1);
	}
	m_Destroyed[Entity_Explosion].clear();

	size = m_Destroyed[Entity_LaserBeam].size();
	for(i = 0; i < size; ++i)
	{
		index = ((int)m_Destroyed[Entity_LaserBeam][i]-(int)&m_LaserBeamArray[0])/sizeof(LaserBeam);
		m_OpenList[Entity_LaserBeam].push_back(index);
		m_OM->RemoveObject(m_Destroyed[Entity_LaserBeam][i],2);
	}
	m_Destroyed[Entity_LaserBeam].clear();

	size = m_Destroyed[Entity_Shield].size();
	for(i = 0; i < size; ++i)
	{
		index = ((int)m_Destroyed[Entity_Shield][i]-(int)&m_ShieldArray[0])/sizeof(Shield);
		m_OpenList[Entity_Shield].push_back(index);
		m_OM->RemoveObject(m_Destroyed[Entity_Shield][i],3);
	}
	m_Destroyed[Entity_Shield].clear();
}


bool ObjectFactory::IsValid( int _id, int _index )
{
	unsigned int size = m_OpenList[_id].size();

	for(unsigned int i = 0; i < size; ++i)
	{
		if(m_OpenList[_id][i] == _index)
			return false;
	}

	return true;
}

void ObjectFactory::MakeDefault( IEntity& _object )
{

}

