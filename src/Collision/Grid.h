#pragma once

#include "Collision\Tree.h"

namespace Collision
{
	class Grid : public Tree
	{
	public:
		virtual ~Grid();

		virtual void build();

		virtual bool collide(Shape* shape) const;

		void setCellSize(const Vector3& size)
		{
			cellSize = size;
		}
	protected:
		Vector3 cellSize;
		Vector3 numberCells;
	};
}
