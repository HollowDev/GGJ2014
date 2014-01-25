#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

#include "objects\IEntity.h"

#include <vector>
using std::vector;

#define NUM_LAYERS 4

class ObjectManager
{
	struct ChangeObject
	{
		int layer;
		IEntity* object;

		ChangeObject(IEntity* _object = nullptr, int _layer = -1)
		{
			object = _object;
			layer = _layer;
		}
	};

	vector<IEntity*> m_Objects[NUM_LAYERS];

	vector<ChangeObject> m_ToRemove;
	vector<ChangeObject> m_ToAdd;

	static ObjectManager m_Instance;

	ObjectManager( void ) {}
	~ObjectManager( void ) {}

	void CheckChanges( void );
public:

	static ObjectManager* GetInstance( void ) { return &m_Instance; }

	void Render( int _x, int _y );
	void Update( float _dt );
	void CheckCollision( void );

	void AddObject( IEntity* _object, int _layer );
	void RemoveObject( IEntity* _object, int _layer );
	void Clear( void );
};

#endif