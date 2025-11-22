#pragma once

#include "Collision\AABB.h"
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

		const Vector3& getCellSize() const 
		{
			return cellSize;
		}

		const int* getNumberCells() const
		{
			return numberCells;
		}

		const AABB& getCell(int offset) const
		{
			return cells[offset];
		}

		const Collision::AABB* getCells() const
		{
			return cells;
		}
	protected:
		Vector3 cellSize;
		int numberCells[3];
		Collision::AABB* cells;
	};
}
