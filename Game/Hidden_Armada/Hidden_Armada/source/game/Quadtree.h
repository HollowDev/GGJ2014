#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include "objects\BaseEntity.h"
#include <vector>
using std::vector;

enum Quadrants { TLeft = 0, TRight, BLeft, BRight };

class Quadtree
{
	int m_MaxObjects;
	int m_MaxLevels;
	int m_CurrLevel;

	vector<BaseEntity*> m_Objects;
	Quadtree* m_Nodes[4];

	RECT m_Bounds;

public:
	Quadtree( int _maxLevel = 0, int _maxObjects = 0, int _level = 0 );
	~Quadtree( void );

	void Init( RECT _bounds );
	void Release( void );
	void RenderDebug( int _x, int _y );

	void Clear( void );
	void Split( void );
	vector<int> GetIndex( RECT& _rect );
	void Insert( BaseEntity* _entity );

	vector<BaseEntity*> Retrieve( vector<BaseEntity*>& _returnList, BaseEntity* _entity );
};

#endif