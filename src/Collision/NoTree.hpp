#pragma once

#include "Collision/Tree.hpp"

namespace Collision
{
    class NoTree : public Tree
    {
    public:
        bool collide(Shape* shape) const override;
    };
}
