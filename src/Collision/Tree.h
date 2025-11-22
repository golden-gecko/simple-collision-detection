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
		Tree(Solver* solver = NULL) : solver(solver)
		{
		}

		Collision::Shape* createSphere(const std::string& type) const
		{
			if ("Sphere" == type)
			{
			}
			
			throw "Unkown shape type";
		}

		void destroyShape(Collision::Shape* shape) const
		{
		}

		virtual void add(Shape* shape)
		{
			shapes.push_back(shape);
		}

		virtual void build() = 0;

		virtual bool canMove(Shape* shape, const Vector3& v) const = 0;
	protected:
		Solver* solver;

		std::vector<Shape*> shapes;

		virtual void createNode() = 0;
	};
}
