#pragma once

#include "StdAfx.h"

#include "Collision\AABB.h"
#include "Collision\Sphere.h"

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

//		Collision::Sphere* shape;
		Collision::AABB* shape;

		Ogre::Entity* shapeEntity;
		Ogre::SceneNode* shapeSceneNode;

		Ogre::ManualObject* manual;

		Ogre::Vector3 target;
		float speed;
	};
}
