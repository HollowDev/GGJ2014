#ifndef _ASTEROID_MANAGER_H_
#define _ASTEROID_MANAGER_H_

#include "objects\PlayerShip.h"
#include "objects\Asteroids.h"
#include <vector>
using std::vector;

class AsteroidManager
{
	struct AsteroidChunk
	{
		int m_NumAsteroids;
		bool m_IsLoaded;
		vector<Asteroids*> m_Asteroids;
		vector<BaseEntity> m_Star;
		void Start( int _x, int _y );
		void Reload( int _x, int _y );
		void UpdateList( void );
	};

	PlayerShip* m_Player;

	AsteroidChunk*** m_Chunks;
	int m_NumRows;
	int m_NumColumns;

public:
	AsteroidManager( void );
	~AsteroidManager( void ) { Release(); }

	void Initialize( int _numColumns, int _numRows, int _numAsteroidsPer, PlayerShip* _player );
	void Release( void );

	void Update( float _dt );
	void Render( int _x, int _y );

	const int GetRows(void) { return m_NumRows; }
	const int GetCols(void) { return m_NumColumns; }
};

#endif