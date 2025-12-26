#pragma once

#include "Collision/Shape.hpp"

namespace Collision
{
    class Sphere : public Shape
    {
    public:
        Sphere(const Ogre::Vector3f& position, float radius) : Shape(Shape::ST_SPHERE, position), radius(radius)
        {
        }

        float getRadius() const
        {
            return radius;
        }

    protected:
        float radius = 0.0f;
    };
}
