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
		const Vector3& q = s1.getPosition();
		const Vector3& n = s2.getNormal();

		float dq = Math::Abs(n.dotProduct(q));
		float dn = n.dotProduct(n);

		return Math::Abs(dq - s2.getDistance()) < s1.getRadius();
	}

	bool Solver::collide(const Sphere& s1, const Sphere& s2)
	{
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
