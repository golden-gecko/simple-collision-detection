#pragma once

#include "Collision\Vector3.h"

namespace Collision
{
	class Shape
	{
	public:
		Shape(const Vector3& position) : position(position)
		{
		}

		virtual void setPosition(const Vector3& position)
		{
			this->position = position;
		}

		const Vector3& getPosition() const
		{
			return position;
		}

		virtual void translate(const Vector3& vector)
		{
			this->position += vector;
		}

		virtual void update() = 0;

	protected:
		Vector3 position;
	};
}
