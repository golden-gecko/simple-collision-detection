#pragma once

#include "Collision/Tree.hpp"

namespace Collision
{
    class NoTree : public Tree
    {
    public:
        void build() override;

        bool collide(Shape* shape) const override;
    };
}
