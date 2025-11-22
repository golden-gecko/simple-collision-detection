#pragma once

#include "Sphere.h"

namespace Collision
{
	class Solver
	{
	public:
		static bool collide(const Sphere& s1, const Sphere& s2);
	};
}

