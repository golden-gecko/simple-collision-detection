#pragma once

#include "Collision\Tree.h"

namespace Collision
{
	class NoTree : public Tree
	{
	public:
		virtual void build();

	protected:
		virtual void createNode();
	};
}
