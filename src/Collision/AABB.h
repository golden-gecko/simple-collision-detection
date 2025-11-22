#pragma once

#include "Collision\Shape.h"

namespace Collision
{
	class AABB : public Shape
	{
	public:
		AABB() : Shape(Vector3::ZERO)
		{
			setSize(Vector3::ZERO);
		}

		AABB(const Vector3& position, const Vector3& size) : Shape(position)
		{
			setSize(size);
		}

		const Vector3* getAxes() const
		{
			return axes;
		}
		
		const Vector3& getSize() const
		{
			return size;
		}

		virtual void setSize(const Vector3& size)
		{
			this->size = size;

			axes[0] = Vector3(size.x, 0.0f, 0.0f);
			axes[1] = Vector3(0.0f, size.y, 0.0f);
			axes[2] = Vector3(0.0f, 0.0f, size.z);

			axes[0].normalise();
			axes[1].normalise();
			axes[2].normalise();
		}

		virtual void update()
		{
		}
	protected:
		Vector3 axes[3];
		Vector3 size;
	};
}
