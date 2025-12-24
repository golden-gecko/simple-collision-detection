#pragma once

#include "Collision/Shape.hpp"

namespace Collision
{
    class Plane : public Shape
    {
    public:
        Plane(const Ogre::Vector3f& normal, float distance) : Shape(Shape::ST_PLANE, normal* distance), normal(normal), distance(distance)
        {
        }

        const Ogre::Vector3f& getNormal() const
        {
            return normal;
        }

        float getDistance() const
        {
            return distance;
        }

    protected:
        Ogre::Vector3f normal = Ogre::Vector3f::ZERO;
        float distance = 0.0f;
    };
}
