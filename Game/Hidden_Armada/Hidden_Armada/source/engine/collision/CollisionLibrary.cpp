#include "CollisionLibrary.h"

bool SphereToSphere( Sphere& _rhs, Sphere& _lhs, ColInfo& _rhsResult, ColInfo& _lhsResult )
{
	D3DXVECTOR2 toOther = _rhs.center - _lhs.center;
	float dist = D3DXVec2Length(&toOther);
	if( dist < _rhs.radius + _lhs.radius )
	{
		float offset = dist - (_rhs.radius + _lhs.radius);
		// rhs first
		D3DXVECTOR2 toTarget = _lhs.center - _rhs.center;
		D3DXVec2Normalize(&toTarget,&toTarget);
		
		_rhsResult.dir = toTarget;
		_rhsResult.offset = offset;

		toTarget = _rhs.center - _lhs.center;
		D3DXVec2Normalize(&toTarget,&toTarget);
		
		_lhsResult.dir = toTarget;
		_lhsResult.offset = offset;

		return true;
	}
	return false;
}