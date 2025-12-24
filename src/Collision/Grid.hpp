#pragma once

#include "PCH.hpp"

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
                std::erase(shapes, shape);
            }
        };

        virtual ~Grid();

        virtual void build();

        virtual bool collide(Shape* shape) const;

        void setCellSize(const Ogre::Vector3f& size)
        {
            cellSize = size;
        }

        const Ogre::Vector3f& getCellSize() const 
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
        Ogre::Vector3f cellSize = Ogre::Vector3f::ZERO;
        int numberCells[3] = { 0, 0, 0 };
        Cell* cells = nullptr;
        std::map<Shape*, Cell*> shapesToCells;
    };
}
