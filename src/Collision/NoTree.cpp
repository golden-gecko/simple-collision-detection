#include "StdAfx.h"

#include "Collision\NoTree.h"

namespace Collision
{
	void NoTree::build()
	{
		std::cout << "NoTree::build()" << std::endl;
	}

	bool NoTree::canMove(Shape* shape, const Vector3& v) const
	{
		for (std::vector<Shape*>::const_iterator i = shapes.begin(); i != shapes.end(); ++i)
		{
			Sphere* s1 = dynamic_cast<Sphere*>(shape);
			Sphere* s2 = dynamic_cast<Sphere*>(*i);

			if (s1 && s2 && s1 != s2 && solver->collide(*s1, *s2))
			{
				return false;
			}
		}

		return true;
	}

	void NoTree::createNode()
	{
	}
}
