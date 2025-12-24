#include "PCH.hpp"

#include "Collision/Tree.hpp"

namespace Collision
{
    bool Tree::collideShapes(Shape* _s1, Shape* _s2) const
    {
        int type = _s1->getType() & _s2->getType();

        switch (type)
        {
            case Shape::ST_AABB:
            {
                AABB* s1 = dynamic_cast<AABB*>(_s1);
                AABB* s2 = dynamic_cast<AABB*>(_s2);

                if (s1 && s2 && s1 != s2 && solver->collide(*s1, *s2))
                {
                    return true;
                }

                break;
            }

            case Shape::ST_AABB | Shape::ST_PLANE:
            {
                AABB* s1 = dynamic_cast<AABB*>(_s1);
                Plane* s2;

                if (s1)
                {
                    s2 = dynamic_cast<Plane*>(_s2);
                }
                else
                {
                    s1 = dynamic_cast<AABB*>(_s2);
                    s2 = dynamic_cast<Plane*>(_s1);
                }

                if (s1 && s2 && solver->collide(*s1, *s2))
                {
                    return true;
                }

                break;
            }

            case Shape::ST_AABB | Shape::ST_SPHERE:
            {
                AABB* s1 = dynamic_cast<AABB*>(_s1);
                Sphere* s2;

                if (s1)
                {
                    s2 = dynamic_cast<Sphere*>(_s2);
                }
                else
                {
                    s1 = dynamic_cast<AABB*>(_s2);
                    s2 = dynamic_cast<Sphere*>(_s1);
                }

                if (s1 && s2 && solver->collide(*s1, *s2))
                {
                    return true;
                }

                break;
            }

            case Shape::ST_PLANE | Shape::ST_SPHERE:
            {
                Plane* s1 = dynamic_cast<Plane*>(_s1);
                Sphere* s2;

                if (s1)
                {
                    s2 = dynamic_cast<Sphere*>(_s2);
                }
                else
                {
                    s1 = dynamic_cast<Plane*>(_s2);
                    s2 = dynamic_cast<Sphere*>(_s1);
                }

                if (s1 && s2 && solver->collide(*s1, *s2))
                {
                    return true;
                }

                break;
            }

            case Shape::ST_SPHERE:
            {
                Sphere* s1 = dynamic_cast<Sphere*>(_s1);
                Sphere* s2 = dynamic_cast<Sphere*>(_s2);

                if (s1 && s2 && s1 != s2 && solver->collide(*s1, *s2))
                {
                    return true;
                }

                break;
            }
        }

        return false;
    }
}
