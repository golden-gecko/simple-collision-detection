#include "StdAfx.h"

#include "Game\Root.h"

int main()
{
	delete new Game::Root();

	return 0;
}

/*

	class AABB : public Object
	{
	};

	class OBB : public Object
	{
	};

	class Tree
	{
	};

	class SphereTree : public Tree
	{
	};

	class Octree : public Tree
	{
	};

*/
