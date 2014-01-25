#ifndef _COLLISION_VOLUME_H_
#define _COLLISION_VOLUME_H_

#include "../directx9.h"

struct Segment
{
	D3DXVECTOR2 start;
	D3DXVECTOR2 end;
};

struct Sphere
{
	D3DXVECTOR2 center;
	float radius;
	Sphere( D3DXVECTOR2 _center = D3DXVECTOR2(0,0), float _radius = 0.0f )
	{
		center = _center;
		radius = _radius;
	}
};

struct ColInfo
{
	D3DXVECTOR2 dir;
	float offset;
};

#endif