#pragma once

#include "Tree.h"

namespace Collision
{
	class Octree : public Tree
	{
	public:
		virtual void build();
	protected:
		virtual void createNode();
	};
}
