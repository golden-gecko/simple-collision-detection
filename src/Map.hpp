#pragma once

#include "PCH.hpp"

#include "Collision/Grid.hpp"
#include "Collision/Octree.hpp"

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
