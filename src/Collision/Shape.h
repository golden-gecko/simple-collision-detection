#pragma once

#include "Collision\Vector3.h"

namespace Collision
{
	class Shape
	{
	public:
		enum Type
		{
			ST_SPHERE = 0x01,
			ST_AABB = 0x02,
			ST_PLANE = 0x04,
			ST_OBB = 0x08
		};
	public:
		Shape(Type type, const Vector3& position) : type(type), position(position)
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

		Type getType() const
		{
			return type;
		}

		virtual void translate(const Vector3& vector)
		{
			this->position += vector;
		}
	protected:
		Type type;
		Vector3 position;
	};
}
