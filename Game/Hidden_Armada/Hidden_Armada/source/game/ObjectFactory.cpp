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
	}

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

