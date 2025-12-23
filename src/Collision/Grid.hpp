#pragma once

#include "Collision/AABB.hpp"
#include "Collision/Tree.hpp"

namespace Collision
{
	class Grid : public Tree
	{
	public:
		struct Cell
		{
			AABB aabb;
			std::vector<Shape*> shapes;

			void attachShape(Shape* shape)
			{
				shapes.push_back(shape);
			}

			void detachShape(Shape* shape)
			{
				std::remove(shapes.begin(), shapes.end(), shape);
			}
		};

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

		Cell& getCell(int offset)
		{
			return cells[offset];
		}
		
		const Cell& getCell(int offset) const
		{
			return cells[offset];
		}

		Cell& getCell(int x, int y, int z)
		{
			return cells[(z * numberCells[1] * numberCells[0]) + (y * numberCells[0]) + x];
		}

		const Cell& getCell(int x, int y, int z) const
		{
			return cells[(z * numberCells[1] * numberCells[0]) + (y * numberCells[0]) + x];
		}

		const Cell* getCells() const
		{
			return cells;
		}

		void updateShape(Shape* shape);
	protected:
		Vector3 cellSize;
		int numberCells[3];
		Cell* cells;
		std::map<Shape*, Cell*> shapesToCells;
	};
}
