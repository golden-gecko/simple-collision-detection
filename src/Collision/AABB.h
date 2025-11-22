#pragma once

#include "Collision\Shape.h"

namespace Collision
{
	class AABB : public Shape
	{
	public:
		AABB(const Vector3& position, const Vector3& size) : Shape(position), size(size)
		{
		}

		virtual void setSize(const Vector3& size)
		{
			this->size = size;
		}

		virtual void update()
		{
		}
	protected:
		Vector3 size;
	};
}
