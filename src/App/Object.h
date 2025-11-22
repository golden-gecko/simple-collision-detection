#pragma once

#include "StdAfx.h"

#include "Collision\AABB.h"
#include "Collision\Sphere.h"

#include "App\Map.h"

namespace App
{
	class Object
	{
	public:
		Object(const std::string& name, const std::string& mesh, Map* map);

		virtual void update(float time);

		virtual ~Object();

		Collision::Shape* getShape() const
		{
			return shape;
		}
	protected:
		std::string name;
		std::string mesh;

		Ogre::Entity* entity;
		Ogre::SceneNode* sceneNode;

		Collision::AABB* shape;
//		Collision::OBB* shape;
//		Collision::Sphere* shape;

		Ogre::Entity* shapeEntity;
		Ogre::SceneNode* shapeSceneNode;

		Ogre::ManualObject* path;
		Ogre::SceneNode* pathSceneNode;

		Ogre::Vector3 target;
		float speed;

		Map* map;

		void setRandomTarget();
		void setRandomSpeed();
	};
}
