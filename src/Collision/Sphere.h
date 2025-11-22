#pragma once

#include "Collision\Shape.h"

namespace Collision
{
	class Sphere : public Shape
	{
	public:
		Sphere(const Vector3& position, float radius) : Shape(position), radius(radius)
		{
		}

		float getRadius() const
		{
			return radius;
		}

		void update()
		{
		}
	protected:
		float radius;
	};
}
