#pragma once

#include "Collision\Tree.h"

namespace Collision
{
	class Octree : public Tree
	{
	public:
		struct Cell
		{
			AABB aabb;
			std::vector<Shape*> shapes;
			int cellNumber;
			Cell* cells[8];
			int depth;

			Cell(int depth) : cellNumber(0), depth(depth)
			{
				for (int i = 0; i < 8; ++i)
				{
					cells[i] = NULL;
				}
			}

			void attachShape(Shape* shape)
			{
				shapes.push_back(shape);
			}

			void detachShape(Shape* shape)
			{
			}
		};

		Octree();

		virtual ~Octree();

		virtual void build();

		virtual bool collide(Shape* shape) const;

		void setMaxDepth(int maxDepth)
		{
			this->maxDepth = maxDepth;
		}

		Cell* getRoot() const
		{
			return root;
		}
	protected:
		int maxDepth;
		Cell* root;
	};
}
