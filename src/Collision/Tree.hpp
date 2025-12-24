#pragma once

#include "PCH.hpp"

#include "Collision/AABB.hpp"
#include "Collision/Solver.hpp"
#include "Collision/Sphere.hpp"

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

        void setSolver(Solver* solver)
        {
            this->solver = solver;
        }

        void setSize(const Ogre::Vector3f& size)
        {
            this->size = size;
        }

        virtual void build() = 0;

        virtual bool collide(Shape* shape) const = 0;

        virtual bool collideShapes(Shape* _s1, Shape* _s2) const;

    protected:
        Solver* solver = nullptr;

        std::vector<Shape*> shapes;

        Ogre::Vector3f size = Ogre::Vector3f::ZERO;
    };
}
