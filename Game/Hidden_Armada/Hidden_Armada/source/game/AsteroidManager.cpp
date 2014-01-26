#include "AsteroidManager.h"
#include "ObjectFactory.h"
#include "AssetManager.h"

#include "../engine/memory_macros.h"

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

	for(int i = 0; i < 100; ++i)
	{
		int randX = rand()%1024;
		int randY = rand()%768;

		BaseEntity star;
		RECT source = {0,0,8,8};
		star.Initialize(AssetManager::GetInstance()->GetAsset(Asset_Star01),source,D3DXVECTOR2(4,4),D3DXVECTOR2(randX+_x,randY+_y),0,0);
		m_Star.push_back(star);
	}

	m_IsLoaded = true;
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
			m_Chunks[x][y]->Reload(x*1024,y*768);
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

	// Check to see what area the player occupies.
	int amCoordsX = m_Player->GetPos().x / 1024;
	int amCoordsY = m_Player->GetPos().y / 768;

	// currently visiting
	if( amCoordsX > 0 && amCoordsX < m_NumColumns &&
		amCoordsY > 0 && amCoordsY < m_NumRows )
	{
		m_Chunks[amCoordsX][amCoordsY]->m_IsLoaded = false;
		for(int x = -1; x < 1; ++x)
		{
			for(int y = -1; y < 1; ++y)
			{
				if(x == 0 && y == 0)
					continue;
				if(m_Chunks[amCoordsX+x][amCoordsY+y] && !m_Chunks[amCoordsX+x][amCoordsY+y]->m_IsLoaded)
				{
					m_Chunks[amCoordsX+x][amCoordsY+y]->Reload( (amCoordsX+x)*1024, (amCoordsY+y)*768 );
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
