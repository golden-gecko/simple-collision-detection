#pragma once

#include "Collision\Shape.h"

namespace Collision
{
	class Tree
	{
	public:
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
