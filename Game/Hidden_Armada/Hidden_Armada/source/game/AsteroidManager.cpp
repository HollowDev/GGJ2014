#include "AsteroidManager.h"
#include "ObjectFactory.h"
#include "AssetManager.h"

#include "../engine/memory_macros.h"

void AsteroidManager::AsteroidChunk::Start( int _x, int _y )
{
	for(int i = 0; i < 100; ++i)
	{
		int randX = rand()%1024;
		int randY = rand()%768;

		BaseEntity star;
		RECT source = {0,0,8,8};
		star.Initialize(AssetManager::GetInstance()->GetAsset(Asset_Star01),source,D3DXVECTOR2(4,4),D3DXVECTOR2(randX+_x,randY+_y),0,0);
		m_Star.push_back(star);
	}

	Reload(_x,_y);
}

void AsteroidManager::AsteroidChunk::Reload( int _x, int _y )
{
	if(m_Asteroids.size() == m_NumAsteroids)
	{
		m_IsLoaded = true;
		return;
	}

	for(unsigned int i = 0; i < m_Asteroids.size(); ++i)
		m_Asteroids[i]->SetIsAlive(false);

	int asteroidImgID[4] =
	{
		AssetManager::GetInstance()->GetAsset(Asset_Asteroid01),
		AssetManager::GetInstance()->GetAsset(Asset_Asteroid02),
		AssetManager::GetInstance()->GetAsset(Asset_Asteroid03),
		AssetManager::GetInstance()->GetAsset(Asset_Asteroid04)		
	};

	for(int i = 0; i < m_NumAsteroids; ++i)
	{
		int randX = rand()%1024;
		int randY = rand()%768;

		IEntity* newAsteroid;
		ObjectFactory::GetInstance()->Create(&newAsteroid, Entity_Asteroid);
		((Asteroids*)newAsteroid)->SetImgID(asteroidImgID[rand()%4]);
		((Asteroids*)newAsteroid)->SetPos(D3DXVECTOR2(randX+_x,randY+_y));
		m_Asteroids.push_back((Asteroids*)newAsteroid);
	}

	m_IsLoaded = true;
}

void AsteroidManager::AsteroidChunk::UpdateList( void )
{
	vector<Asteroids*> newList;
	for(unsigned int i = 0; i < m_Asteroids.size(); ++i)
		if(m_Asteroids[i]->GetIsAlive())
			newList.push_back(m_Asteroids[i]);

	m_Asteroids = newList;
}

AsteroidManager::AsteroidManager( void )
{
	m_Chunks = nullptr;
}

void AsteroidManager::Initialize( int _numColumns, int _numRows, int _numAsteroidsPer, PlayerShip* _player )
{
	m_Player = _player; 

	m_NumColumns = _numColumns;
	m_NumRows = _numRows;

	m_Chunks = new AsteroidChunk**[m_NumColumns];
	for(int x = 0; x < m_NumColumns; ++x)
	{
		m_Chunks[x] = new AsteroidChunk*[m_NumRows];
		for(int y = 0; y < m_NumRows; ++y)
		{
			m_Chunks[x][y] = new AsteroidChunk();
			m_Chunks[x][y]->m_NumAsteroids = _numAsteroidsPer;
			m_Chunks[x][y]->m_IsLoaded = false;
			m_Chunks[x][y]->Start(x*1024,y*768);
		}
	}
}

void AsteroidManager::Release( void )
{
	for(int x = 0; x < m_NumColumns; ++x)
	{
		for(int y = 0; y < m_NumRows; ++y)
		{
			SAFE_DELETE(m_Chunks[x][y]);
		}
		SAFE_DELETE(m_Chunks[x]);
	}
	SAFE_DELETE(m_Chunks);
}

void AsteroidManager::Update( float _dt )
{
	if(!m_Player || !m_Chunks)
		return;

	for(int x = 0; x < m_NumColumns; ++x)
		for(int y = 0; y < m_NumRows; ++y)
			m_Chunks[x][y]->UpdateList();

	// Check to see what area the player occupies.
	int amCoordsX = m_Player->GetPos().x / 1024;
	int amCoordsY = m_Player->GetPos().y / 768;

	// currently visiting
	if( amCoordsX >= 0 && amCoordsX < m_NumColumns &&
		amCoordsY >= 0 && amCoordsY < m_NumRows )
	{
		vector<int> m_LocX;
		vector<int> m_LocY;
		for(int x = -1; x <= 1; ++x)
		{
			for(int y = -1; y <= 1; ++y)
			{
				if( amCoordsX+x >= 0 && amCoordsX < m_NumColumns &&
					amCoordsY+y >= 0 && amCoordsY < m_NumRows )
				{
					m_LocX.push_back(amCoordsX+x);
					m_LocY.push_back(amCoordsY+y);
				}
			}
		}

		for(int x = 0; x < m_NumColumns; ++x)
		{
			for(int y = 0; y < m_NumRows; ++y)		
			{
				bool update = true;
				for(unsigned int i = 0; i < m_LocX.size(); ++i)
				{
					if(m_LocX[i] == x && m_LocY[i] == y)
					{
						update = false;
						break;
					}
				}
				if(update)
				{
					m_Chunks[x][y]->Reload(x*1024,y*768);
				}
			}
		}
	}
}

void AsteroidManager::Render( int _x, int _y )
{
	for(int x = 0; x < m_NumColumns; ++x)
	{
		for(int y = 0; y < m_NumRows; ++y)
		{
			for(unsigned int i = 0; i < m_Chunks[x][y]->m_Star.size(); ++i)
			{
				m_Chunks[x][y]->m_Star[i].Render(_x,_y);
			}
		}
	}
}
