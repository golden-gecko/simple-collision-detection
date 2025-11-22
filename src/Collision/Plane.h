#pragma once

#include "Collision\Shape.h"

namespace Collision
{
	class Plane : public Shape
	{
	public:
		Plane(const Vector3& normal, float distance);
	protected:
		Vector3 normal;
		float distance;
	};
}
