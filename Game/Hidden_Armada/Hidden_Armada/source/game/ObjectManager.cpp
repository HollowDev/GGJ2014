#include "ObjectManager.h"
#include "../engine/collision/CollisionLibrary.h"
#include "ObjectFactory.h"

ObjectManager ObjectManager::m_Instance;

void ObjectManager::CheckChanges( void )
{
	for(unsigned int i = 0; i < m_ToRemove.size(); ++i)
	{
		int layer = m_ToRemove[i].layer;
		for(unsigned int j = 0; j < m_Objects[layer].size(); ++j)
		{
			if(m_Objects[layer][j] == m_ToRemove[i].object)
				m_Objects[layer].erase(m_Objects[layer].begin()+j);
		}
	}
	m_ToRemove.clear();

	for(unsigned int i = 0; i < m_ToAdd.size(); ++i)
		m_Objects[m_ToAdd[i].layer].push_back(m_ToAdd[i].object);
	m_ToAdd.clear();
}

void ObjectManager::Render( int _x, int _y )
{
	for(unsigned int x = 0; x < NUM_LAYERS; ++x)
		for(unsigned int i = 0; i < m_Objects[x].size(); ++i)
			m_Objects[x][i]->Render(_x,_y);
}

void ObjectManager::Update( float _dt )
{
	for(unsigned int x = 0; x < NUM_LAYERS; ++x)
	{
		for(unsigned int i = 0; i < m_Objects[x].size(); ++i)
		{
			if(m_Objects[x][i]->GetIsAlive())
				m_Objects[x][i]->Update(_dt);
			else
				ObjectFactory::GetInstance()->Destroy(m_Objects[x][i]);
		}
	}

	CheckChanges();
}

void ObjectManager::CheckCollision( void )
{
	for(unsigned int x = 0; x < NUM_LAYERS; ++x)
	{
		for(unsigned int i = 0; i < m_Objects[x].size(); ++i)
		{
			for(unsigned int y = 0; y < NUM_LAYERS; ++y)
			{
				for(unsigned int j = 0; j < m_Objects[y].size(); ++j)
				{
					if( m_Objects[x][i] != m_Objects[y][j] )
					{
						ColInfo rhs, lhs;
						if(SphereToSphere(m_Objects[x][i]->GetSphere(), m_Objects[y][j]->GetSphere(), rhs, lhs))
						{
							m_Objects[x][i]->HandleCollision(m_Objects[y][j], rhs.offset, rhs.dir.x, rhs.dir.y);
							m_Objects[y][j]->HandleCollision(m_Objects[x][i], lhs.offset, lhs.dir.x, lhs.dir.y);
						}
					}
				}
			}
		}
	}
}

void ObjectManager::AddObject( IEntity* _object, int _layer )
{
	m_ToAdd.push_back(ChangeObject(_object,_layer));
}

void ObjectManager::RemoveObject( IEntity* _object, int _layer )
{
	m_ToRemove.push_back(ChangeObject(_object,_layer));
}

void ObjectManager::Clear( void )
{
	for(int i = 0; i < NUM_LAYERS; ++i)
		m_Objects[i].clear();
}
