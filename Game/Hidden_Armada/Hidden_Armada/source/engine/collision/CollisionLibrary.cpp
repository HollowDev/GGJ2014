#include "CollisionLibrary.h"

bool SphereToSphere( Sphere& _rhs, Sphere& _lhs, ColInfo& _rhsResult, ColInfo& _lhsResult )
{
	D3DXVECTOR2 toTarget = _rhs.center - _lhs.center;
	float dist = D3DXVec2Length(&toTarget);

	float r2 = _rhs.radius + _lhs.radius;
	if( dist < r2 )
	{
		float offset = dist - (r2);
		// rhs first
		D3DXVec2Normalize(&toTarget,&toTarget);
		
		_rhsResult.dir = toTarget;
		_rhsResult.offset = -offset;

		_lhsResult.dir = toTarget;
		_lhsResult.offset = offset;

		return true;
	}
	return false;
}


bool SegmentToSphere( Segment& _rhs, Sphere& _lhs, ColInfo& _rhsResult, ColInfo& _lhsResult )
{
	D3DXVECTOR2 closest;
	// First find the closest
	D3DXVECTOR2 L = _rhs.end - _rhs.start;
	D3DXVECTOR2 N;
	D3DXVec2Normalize(&N,&L);

	D3DXVECTOR2 V = _lhs.center - _rhs.start;
	float D = D3DXVec2Dot(&N,&V);
	if(D < 0.0f)
		closest = _rhs.start;
	else if(D > D3DXVec2Length(&L))
		closest = _rhs.end;
	else
	{
		N = N * D;
		closest = _rhs.start + N;
	}

	// Now get the distance between the closest point and center of the sphere.
	D3DXVECTOR2 toTarget = _lhs.center - closest;
	float dist = D3DXVec2Length(&toTarget);
	if(dist < _lhs.radius)
	{
		_rhsResult.dir = L;
		_rhsResult.offset = D;
		D3DXVec2Normalize(&_lhsResult.dir,&toTarget);
		_lhsResult.offset = dist - _lhs.radius;
		return true;
	}
	return false;
}