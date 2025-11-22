#pragma once

#include "StdAfx.h"

#include "Collision\Shape.h"

namespace Game
{
	class Object
	{
	public:
		Object(const std::string& name, const std::string& mesh);

		virtual void update(float time);

		virtual ~Object();
	protected:
		std::string name;
		std::string mesh;

		Ogre::Entity* entity;
		Ogre::SceneNode* sceneNode;

		Collision::Shape* shape;

		Ogre::Entity* shapeEntity;
		Ogre::SceneNode* shapeSceneNode;

		Ogre::Vector3 target;
	};
}
