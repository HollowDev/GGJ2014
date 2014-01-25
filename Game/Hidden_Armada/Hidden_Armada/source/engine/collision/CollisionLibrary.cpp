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
		_rhsResult.offset = offset;

		_lhsResult.dir = -toTarget;
		_lhsResult.offset = offset;

		return true;
	}
	return false;
}