#include "StdAfx.h"

#include "Collision\Math.h"
#include "Collision\Solver.h"

namespace Collision
{
	bool Solver::collide(const AABB& s1, const AABB& s2)
	{
		return Math::Abs(s1.getPosition().x - s2.getPosition().x) < s1.getSize().x + s2.getSize().x
			&& Math::Abs(s1.getPosition().y - s2.getPosition().y) < s1.getSize().y + s2.getSize().y
			&& Math::Abs(s1.getPosition().z - s2.getPosition().z) < s1.getSize().z + s2.getSize().z;
	}

	bool Solver::collide(const AABB& s1, const Plane& s2)
	{
		return false;
	}

	bool Solver::collide(const AABB& s1, const Sphere& s2)
	{
		return Math::Abs(s1.getPosition().x - s2.getRadius()) < s1.getSize().x + s2.getRadius()
			&& Math::Abs(s1.getPosition().y - s2.getRadius()) < s1.getSize().y + s2.getRadius()
			&& Math::Abs(s1.getPosition().z - s2.getRadius()) < s1.getSize().z + s2.getRadius();
	}


	bool Solver::collide(const Sphere& s1, const AABB& s2)
	{
		return collide(s2, s1);
	}

	bool Solver::collide(const Sphere& s1, const Plane& s2)
	{
		return false;
	}

	bool Solver::collide(const Sphere& s1, const Sphere& s2)
	{
		Vector3 p1 = s1.getPosition();
		Vector3 p2 = s2.getPosition();

		float d1 = s1.getPosition().distance(s2.getPosition());
		float d2 = s1.getRadius() + s2.getRadius();

		bool r = s1.getPosition().distance(s2.getPosition()) <= s1.getRadius() + s2.getRadius();

		return s1.getPosition().distance(s2.getPosition()) <= s1.getRadius() + s2.getRadius();
	}


	bool Solver::collide(const Plane& s1, const AABB& s2)
	{
		return collide(s2, s1);
	}

	bool Solver::collide(const Plane& s1, const Plane& s2)
	{
		return false;
	}

	bool Solver::collide(const Plane& s1, const Sphere& s2)
	{
		return collide(s2, s1);
	}
}
