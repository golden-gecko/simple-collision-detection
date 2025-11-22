#pragma once

#include "StdAfx.h"

namespace Game
{
	class Map
	{
	public:
		Map(const std::string& name, const Ogre::Vector3& size);

		virtual ~Map();
	protected:
		std::string name;
		Ogre::Vector3 size;

		Ogre::ManualObject* manual;
		Ogre::SceneNode* sceneNode;
	};
}
