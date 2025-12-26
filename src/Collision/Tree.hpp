#pragma once

#include "Collision/Solver.hpp"

class Map;
class Shape;

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

        virtual void build()
        {
        }

        virtual bool collide(Shape* shape) const = 0;

        virtual bool collideShapes(Shape* _s1, Shape* _s2) const;

        virtual void debug(Map* map)
        {
        }

        void setSolver(std::shared_ptr<Solver> _solver)
        {
            solver = _solver;
        }

        void setSize(const Ogre::Vector3f& _size)
        {
            size = _size;
        }

    protected:
        std::shared_ptr<Solver> solver;

        std::vector<Shape*> shapes;

        Ogre::Vector3f size = Ogre::Vector3f::ZERO;
    };
}
