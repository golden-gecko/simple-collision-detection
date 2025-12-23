#include "PCH.hpp"

#include "Collision/Plane.hpp"

namespace Collision
{
	Plane::Plane(const Vector3& normal, float distance) : Shape(Shape::ST_PLANE, normal * distance), normal(normal), distance(distance)
	{
	}

	Plane::~Plane()
	{
	}
}
