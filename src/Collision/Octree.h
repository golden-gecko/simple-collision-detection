#pragma once

#include "Collision\Tree.h"

namespace Collision
{
	class Octree : public Tree
	{
	public:
		virtual void build();

		virtual bool collide(Shape* shape) const;
	};
}
