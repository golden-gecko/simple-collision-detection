#pragma once

#include <Ogre.h>

namespace Collision
{
    class Shape
    {
    public:
        enum Type
        {
            ST_SPHERE = 0x01,
            ST_AABB = 0x02,
            ST_PLANE = 0x04,
            ST_OBB = 0x08
        };

    public:
        Shape(Type type, const Ogre::Vector3f& position) : type(type), position(position)
        {
        }

        virtual void setPosition(const Ogre::Vector3f& position)
        {
            this->position = position;
        }

        const Ogre::Vector3f& getPosition() const
        {
            return position;
        }

        Type getType() const
        {
            return type;
        }

        void translate(const Ogre::Vector3f& vector)
        {
            this->position += vector;
        }

    protected:
        Type type;
        Ogre::Vector3f position;
    };
}
