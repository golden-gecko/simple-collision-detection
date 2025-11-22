#pragma once

#include "Collision\AABB.h"
#include "Collision\Sphere.h"

namespace Collision
{
	class Tree
	{
	public:
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

	protected:
		std::vector<Shape*> shapes;

		virtual void createNode() = 0;
	};
}
