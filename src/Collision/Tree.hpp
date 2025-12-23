#pragma once

#include "Collision/AABB.hpp"
#include "Collision/Solver.hpp"
#include "Collision/Sphere.hpp"
#include "Collision/Vector3.hpp"

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

		void setSize(const Vector3& size)
		{
			this->size = size;
		}

		virtual void build() = 0;

		virtual bool collide(Shape* shape) const = 0;

		virtual bool collideShapes(Shape* _s1, Shape* _s2) const;
	protected:
		Solver* solver;

		std::vector<Shape*> shapes;

		Vector3 size;
	};
}
