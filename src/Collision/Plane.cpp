#include "StdAfx.h"

#include "Collision\Plane.h"

namespace Collision
{
	Plane::Plane(const Vector3& normal, float distance) : Shape(normal * distance), normal(normal), distance(distance)
	{
	}
}
