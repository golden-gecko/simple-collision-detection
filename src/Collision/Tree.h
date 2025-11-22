#pragma once

#include "Collision\AABB.h"
#include "Collision\Solver.h"
#include "Collision\Sphere.h"
#include "Collision\Vector3.h"

namespace Collision
{
	class Tree
	{
	public:
		virtual ~Tree()
		{
		}

		virtual void add(Shape* shape)
		{
			shapes.push_back(shape);
		}

		void setSolver(Solver* solver)
		{
			this->solver = solver;
		}

		void setSize(const Vector3& min, const Vector3& max)
		{
			this->min = min;
			this->max = max;

			size = max - min;
		}

		virtual void build() = 0;

		virtual bool collide(Shape* shape) const = 0;
	protected:
		Solver* solver;

		std::vector<Shape*> shapes;

		Vector3 min;
		Vector3 max;

		Vector3 size;
	};
}
