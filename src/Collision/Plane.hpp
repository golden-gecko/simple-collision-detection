#pragma once

#include "Collision/Shape.hpp"

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

		virtual ~Plane();
	protected:
		Vector3 normal;
		float distance;
	};
}
