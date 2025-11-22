#pragma once

#include "Collision\Shape.h"

namespace Collision
{
	class Plane : public Shape
	{
	public:
		Plane(const Vector3& normal, float distance);

		const Vector3& getNormal() const
		{
			return normal;
		}

		float getDistance() const
		{
			return distance;
		}
	protected:
		Vector3 normal;
		float distance;
	};
}
