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
			if(m_Objects[x][i]->GetIsAlive())
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
			IEntity* object1 = m_Objects[x][i];
			for(unsigned int y = 0; y < NUM_LAYERS; ++y)
			{
				for(unsigned int j = 0; j < m_Objects[y].size(); ++j)
				{
					IEntity* object2 = m_Objects[y][j];
					if( object1 != object2 && object1->GetIsAlive() && object2->GetIsAlive() )
					{
						if(!m_Objects[x][i]->CheckCollision(m_Objects[y][j]) ||
						   !m_Objects[y][j]->CheckCollision(m_Objects[x][i]) )
						   continue;

						if(object1->GetType() != Entity_LaserBeam && object2->GetType() != Entity_LaserBeam)
						{
							ColInfo rhs, lhs;
							if(SphereToSphere(object1->GetSphere(), object2->GetSphere(), rhs, lhs))
							{
								object1->HandleCollision(object2, rhs.offset, rhs.dir.x, rhs.dir.y);
								object2->HandleCollision(object1, lhs.offset, lhs.dir.x, lhs.dir.y);
							}
						}
						else
						{
							if(object1->GetType() == Entity_LaserBeam)
							{
								ColInfo rhs, lhs;
								if(SegmentToSphere(((LaserBeam*)object1)->GetSegment(),object2->GetSphere(),rhs,lhs))
								{
									object1->HandleCollision(object2, rhs.offset, rhs.dir.x, rhs.dir.y);
									object2->HandleCollision(object1, lhs.offset, lhs.dir.x, lhs.dir.y);
								}
							}
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
	{
		for(int x = 0; x < m_Objects[i].size(); ++x)
			m_Objects[i][x]->SetIsAlive(false);
		m_Objects[i].clear();
	}
}
