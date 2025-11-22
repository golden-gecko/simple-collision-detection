#include "Solver.h"

namespace Collision
{
	bool Solver::collide(const Sphere& s1, const Sphere& s2)
	{
		return s1.getPosition().distance(s2.getPosition()) < s1.getRadius() + s2.getRadius();
	}
}
