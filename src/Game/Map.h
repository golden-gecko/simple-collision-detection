#pragma once

#include "StdAfx.h"

#include "Collision\Grid.h"
#include "Collision\Octree.h"

namespace Game
{
	class Map
	{
	public:
		Map(const std::string& name, const Ogre::Vector3& size);

		virtual ~Map();

		const Ogre::Vector3& getSize() const
		{
			return size;
		}

		void createGrid(Collision::Grid* grid);
		void createOctree(Collision::Octree* octree);
	protected:
		std::string name;
		Ogre::Vector3 size;

		Ogre::ManualObject* manual;
		Ogre::SceneNode* sceneNode;
	};
}
