#include "Collision/NoTree.hpp"

namespace Collision
{
    bool NoTree::collide(Shape* shape) const
    {
        for (std::vector<Shape*>::const_iterator i = shapes.begin(); i != shapes.end(); ++i)
        {
            if (collideShapes(shape, *i))
            {
                return true;
            }

            {
                OBB* s1 = dynamic_cast<OBB*>(shape);
                OBB* s2 = dynamic_cast<OBB*>(*i);

                if (s1 && s2 && s1 != s2 && solver->collide(*s1, *s2))
                {
                    return true;
                }
            }

            {
                OBB* s1 = dynamic_cast<OBB*>(shape);
                Plane* s2 = dynamic_cast<Plane*>(*i);

                if (s1 && s2 && solver->collide(*s1, *s2))
                {
                    return true;
                }
            }

            {
                OBB* s1 = dynamic_cast<OBB*>(shape);
                Sphere* s2 = dynamic_cast<Sphere*>(*i);

                if (s1 && s2 && solver->collide(*s1, *s2))
                {
                    return true;
                }
            }
        }

        return false;
    }
}
