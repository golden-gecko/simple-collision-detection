#pragma once

#include "Collision\AABB.h"
#include "Collision\OBB.h"
#include "Collision\Plane.h"
#include "Collision\Sphere.h"

namespace Collision
{
	class Solver
	{
	public:
		virtual bool collide(const AABB& s1, const AABB& s2);
		virtual bool collide(const AABB& s1, const Plane& s2);
		virtual bool collide(const AABB& s1, const Sphere& s2);
		
		virtual bool collide(const Sphere& s1, const AABB& s2);
		virtual bool collide(const Sphere& s1, const Plane& s2);
		virtual bool collide(const Sphere& s1, const Sphere& s2);

		virtual bool collide(const Plane& s1, const AABB& s2);
		virtual bool collide(const Plane& s1, const Plane& s2);
		virtual bool collide(const Plane& s1, const Sphere& s2);

		virtual bool collide(const OBB& s1, const OBB& s2);
		virtual bool collide(const OBB& s1, const Plane& s2);
		virtual bool collide(const OBB& s1, const Sphere& s2);
	};
}
