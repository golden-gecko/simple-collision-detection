#include "StdAfx.h"

#include "App\Root.h"

int main()
{
	delete new App::Root();

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
