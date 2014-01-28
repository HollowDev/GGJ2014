#include "Quadtree.h"
#include "../engine/renderer/D3D9Handler.h"

Quadtree::Quadtree( int _maxLevel, int _maxObjects, int _level )
{
	m_MaxLevels = _maxLevel;
	m_MaxObjects = _maxObjects;
	m_CurrLevel = _level;
	for(int i = 0; i < 4; ++i)
		m_Nodes[i] = nullptr;
}

Quadtree::~Quadtree( void )
{
}

void Quadtree::Init( RECT _bounds )
{
	m_Bounds = _bounds;
}

void Quadtree::Release( void )
{
}

void Quadtree::RenderDebug( int _x, int _y )
{
	RECT drawBounds = m_Bounds;
	drawBounds.left += _x;
	drawBounds.right += _x;
	drawBounds.top += _y;
	drawBounds.bottom += _y;
	D3D9Handler::DrawEmptyRect(drawBounds,255,255,255);
	if(m_Nodes[0] != nullptr)
		for(int i = 0; i < 4; ++i)
			m_Nodes[i]->RenderDebug(_x,_y);
}

void Quadtree::Clear( void )
{
	m_Objects.clear();
	if(m_Nodes[0])
	{
		for(int i = 0; i < 4; ++i)
		{
			m_Nodes[i]->Clear();
			delete m_Nodes[i];
			m_Nodes[i] = nullptr;
		}
	}
}

void Quadtree::Split( void )
{
	int width = int(m_Bounds.right-m_Bounds.left);
	int height = int(m_Bounds.bottom-m_Bounds.top);
	int halfWidth = width/2;
	int halfHeight = height/2;
	int x = int(m_Bounds.left);
	int y = int(m_Bounds.top);

	RECT topLeft		= { x, y, x + halfWidth, y + halfHeight };
	RECT topRight		= { x + halfWidth, y, x + width, y + halfHeight };
	RECT bottomLeft		= { x, y + halfHeight, x + halfWidth, y + height };
	RECT bottomRight	= { x + halfWidth, y + halfHeight, x + width, y + height };
	for(int i = 0; i < 4; ++i)
		m_Nodes[i] = new Quadtree(m_MaxLevels,m_MaxObjects,m_CurrLevel+1);
	m_Nodes[TLeft]->Init(topLeft);
	m_Nodes[TRight]->Init(topRight);
	m_Nodes[BLeft]->Init(bottomLeft);
	m_Nodes[BRight]->Init(bottomRight);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: The getIndex method is a helper function of the quadtree. It determines where an 
		 object belongs in the quadtree by determining which node the object can fit into.
[in] _rect: rect of the object to test for.
Return: the indexes the object is in.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
vector<int> Quadtree::GetIndex( RECT& _rect )
{
	vector<int> indexes;

	float vMidpoint = int(m_Bounds.left) + int((m_Bounds.right-m_Bounds.left)/2.0f);
	float hMidpoint = int(m_Bounds.top) + int((m_Bounds.bottom-m_Bounds.top)/2.0f);

	// Which quadrants have the object in it.
	bool topQuad = ((int)_rect.top < hMidpoint);
	bool bottomQuad = ((int)_rect.bottom > hMidpoint);
	bool leftQuad = ((int)_rect.left < vMidpoint);
	bool rightQuad = ((int)_rect.right > vMidpoint);

	// Left and right
	if(rightQuad)
	{
		if(topQuad)
			indexes.push_back(TRight);
		if(bottomQuad)
			indexes.push_back(BRight);
	}
	if(leftQuad)
	{
		if(topQuad)
			indexes.push_back(TLeft);
		if(bottomQuad)
			indexes.push_back(BLeft);
	}

	return indexes;

	/*
	// Object can completely fit within the left quadrants
	if((int)_rect.left < vMidpoint && (int)_rect.right < vMidpoint)
	{
		if(topQuad)
			index = TLeft;
		else if(bottomQuad)
			index = BLeft;
	}
	else if(_rect.left > vMidpoint)
	{
		if(topQuad)
			index = TRight;
		else if(bottomQuad)
			index = BRight;
	}

	return index;
	*/
}

void Quadtree::Insert( BaseEntity* _entity )
{
	Sphere s1 = _entity->GetSphere();
	RECT area = {s1.center.x - s1.radius, s1.center.y - s1.radius,
				 s1.center.x + s1.radius, s1.center.y + s1.radius};

	// If one of the nodes is not null
	if(m_Nodes[0] != nullptr)
	{
		vector<int> indexes = GetIndex(area);
		for(unsigned int i = 0; i < indexes.size(); ++i)
		{
			m_Nodes[indexes[i]]->Insert(_entity);
			return;
		}
	}

	m_Objects.push_back(_entity);

	// Check if we should split!
	if(m_Objects.size() > m_MaxObjects && m_CurrLevel < m_MaxLevels)
	{
		if(m_Nodes[0] == nullptr)
			Split();

		int i = 0;
		vector<BaseEntity*> toKeep = m_Objects;
		while(i < m_Objects.size())
		{
			Sphere s2 = m_Objects[i]->GetSphere();
			RECT area = {s2.center.x - s2.radius, s2.center.y - s2.radius,
						 s2.center.x + s2.radius, s2.center.y + s2.radius};
			vector<int> indexes = GetIndex(area);
			for(unsigned int x = 0; x < indexes.size(); ++x)
			{
				m_Nodes[indexes[x]]->Insert(m_Objects[i]);
			}
			if(indexes.size() > 0)
				m_Objects.erase(m_Objects.begin()+i);
			else
				i++;
		}
		m_Objects.clear();
	}
}

vector<BaseEntity*> Quadtree::Retrieve( vector<BaseEntity*>& _returnList, BaseEntity* _entity )
{
	Sphere s1 = _entity->GetSphere();
	RECT area = {s1.center.x - s1.radius, s1.center.y - s1.radius,
				 s1.center.x + s1.radius, s1.center.y + s1.radius};

	if(m_Nodes[0] != nullptr)
	{
		vector<int> indexes = GetIndex(area);
		for(unsigned int i = 0; i < indexes.size(); ++i)
		{
			m_Nodes[indexes[i]]->Retrieve(_returnList,_entity);
		}
	}

	for(unsigned int i = 0; i < m_Objects.size(); ++i)
		_returnList.push_back(m_Objects[i]);
	
	return _returnList;
}