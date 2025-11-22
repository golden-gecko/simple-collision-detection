#pragma once

#include "StdAfx.h"

namespace Collision
{
	class GameObject
	{
	public:
		GameObject(const std::string& name, const std::string& mesh);

		virtual void update(float time);

		virtual ~GameObject();
	protected:
		std::string name;
		std::string mesh;

		Ogre::Entity* entity;
		Ogre::SceneNode* sceneNode;

		Ogre::Vector3 target;
	};
}
