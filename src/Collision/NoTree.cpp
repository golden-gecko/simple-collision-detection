#include "StdAfx.h"

#include "Collision\NoTree.h"

namespace Collision
{
	void NoTree::build()
	{
		std::cout << "NoTree::build()" << std::endl;

		// Klasa NoTree wykonuje testy ka¿ej pary obiektów.
		// S³u¿y tylko do testów i (w odró¿nieniu od np. Octree)
		// nie wymaga dodatkowej organizacji obiektów.
	}

	bool NoTree::collide(Shape* shape) const
	{
		for (std::vector<Shape*>::const_iterator i = shapes.begin(); i != shapes.end(); ++i)
		{
			{
				AABB* s1 = dynamic_cast<AABB*>(shape);
				AABB* s2 = dynamic_cast<AABB*>(*i);

				if (s1 && s2 && s1 != s2 && solver->collide(*s1, *s2))
				{
					return true;
				}
			}

			{
				AABB* s1 = dynamic_cast<AABB*>(shape);
				Plane* s2 = dynamic_cast<Plane*>(*i);

				if (s1 && s2 && solver->collide(*s1, *s2))
				{
					return true;
				}
			}

			{
				AABB* s1 = dynamic_cast<AABB*>(shape);
				Sphere* s2 = dynamic_cast<Sphere*>(*i);

				if (s1 && s2 && solver->collide(*s1, *s2))
				{
					return true;
				}
			}

			{
				Plane* s1 = dynamic_cast<Plane*>(shape);
				Plane* s2 = dynamic_cast<Plane*>(*i);

				if (s1 && s2 && s1 != s2 && solver->collide(*s1, *s2))
				{
					return true;
				}
			}

			{
				Plane* s1 = dynamic_cast<Plane*>(shape);
				AABB* s2 = dynamic_cast<AABB*>(*i);

				if (s1 && s2 && solver->collide(*s1, *s2))
				{
					return true;
				}
			}

			{
				Plane* s1 = dynamic_cast<Plane*>(shape);
				Sphere* s2 = dynamic_cast<Sphere*>(*i);

				if (s1 && s2 && solver->collide(*s1, *s2))
				{
					return true;
				}
			}

			{
				Sphere* s1 = dynamic_cast<Sphere*>(shape);
				Sphere* s2 = dynamic_cast<Sphere*>(*i);

				if (s1 && s2 && s1 != s2 && solver->collide(*s1, *s2))
				{
					return true;
				}
			}

			{
				Sphere* s1 = dynamic_cast<Sphere*>(shape);
				AABB* s2 = dynamic_cast<AABB*>(*i);

				if (s1 && s2 && solver->collide(*s1, *s2))
				{
					return true;
				}
			}

			{
				Sphere* s1 = dynamic_cast<Sphere*>(shape);
				Plane* s2 = dynamic_cast<Plane*>(*i);

				if (s1 && s2 && solver->collide(*s1, *s2))
				{
					return true;
				}
			}
		}

		return false;
	}
}
