#pragma once

#include "Collision\Shape.h"

namespace Collision
{
	class OBB : public Shape
	{
	public:
		Vector3 u[3];
		float e[3];

		OBB() : Shape(Vector3::ZERO)
		{
			setSize(Vector3::ZERO);
		}

		OBB(const Vector3& position, const Vector3& size) : Shape(position)
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

			u[0] = axes[0];
			u[1] = axes[1];
			u[2] = axes[2];

			e[0] = size.x;
			e[1] = size.y;
			e[2] = size.z;
		}

		virtual void update()
		{
		}
	protected:
		Vector3 axes[3];
		Vector3 size;
	};
}
