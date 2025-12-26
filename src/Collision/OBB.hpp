#pragma once

#include "Collision/Shape.hpp"

namespace Collision
{
    class OBB : public Shape
    {
    public:
        Ogre::Vector3f u[3];
        float e[3];

        OBB() : Shape(Shape::ST_OBB, Ogre::Vector3f::ZERO)
        {
            setSize(Ogre::Vector3f::ZERO);
        }

        OBB(const Ogre::Vector3f& position, const Ogre::Vector3f& size) : Shape(Shape::ST_OBB, position)
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

            u[0] = axes[0];
            u[1] = axes[1];
            u[2] = axes[2];

            e[0] = size.x;
            e[1] = size.y;
            e[2] = size.z;
        }

    protected:
        Ogre::Vector3f axes[3] = { Ogre::Vector3f::ZERO, Ogre::Vector3f::ZERO, Ogre::Vector3f::ZERO };
        Ogre::Vector3f size = Ogre::Vector3f::ZERO;
    };
}
