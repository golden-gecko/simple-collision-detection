#pragma once

#include "Collision/Shape.hpp"

namespace Collision
{
    class AABB : public Shape
    {
    public:
        AABB() : Shape(Shape::ST_AABB, Ogre::Vector3f::ZERO)
        {
            setSize(Ogre::Vector3f::ZERO);
        }

        AABB(const Ogre::Vector3f& position, const Ogre::Vector3f& size) : Shape(Shape::ST_AABB, position)
        {
            setSize(size);
        }

        const Ogre::Vector3f* getAxes() const
        {
            return axes;
        }
        
        const Ogre::Vector3f& getSize() const
        {
            return size;
        }

        void setSize(const Ogre::Vector3f& size)
        {
            this->size = size;

            axes[0] = Ogre::Vector3f(size.x, 0.0f, 0.0f);
            axes[1] = Ogre::Vector3f(0.0f, size.y, 0.0f);
            axes[2] = Ogre::Vector3f(0.0f, 0.0f, size.z);

            axes[0].normalise();
            axes[1].normalise();
            axes[2].normalise();
        }

    protected:
        Ogre::Vector3f axes[3] = { Ogre::Vector3f::ZERO, Ogre::Vector3f::ZERO, Ogre::Vector3f::ZERO };
        Ogre::Vector3f size = Ogre::Vector3f::ZERO;
    };
}
