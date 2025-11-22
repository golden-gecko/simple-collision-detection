#pragma once

#include "Collision\Tree.h"

namespace Collision
{
	class Grid : public Tree
	{
	public:
		virtual void build();
	protected:
		virtual void createNode();
	};
}
