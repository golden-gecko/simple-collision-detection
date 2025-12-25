#pragma once

#include "Collision/Tree.hpp"

#include "Map.hpp"

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
                    cells[i] = nullptr;
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

        ~Octree() override;

        void build() override;

        bool collide(Shape* shape) const override;

        void debug(Map* map) override;

        void setMaxDepth(int maxDepth)
        {
            this->maxDepth = maxDepth;
        }

        Cell* getRoot() const
        {
            return root;
        }

    protected:
        int maxDepth = 0;
        Cell* root = nullptr;

        Ogre::ManualObject* manual = nullptr;
        Ogre::SceneNode* sceneNode = nullptr;
    };
}
