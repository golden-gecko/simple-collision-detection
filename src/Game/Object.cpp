#include "StdAfx.h"

#include "Collision\AABB.h"
#include "Collision\Sphere.h"

#include "Game\Object.h"
#include "Game\Root.h"

namespace Game
{
	Object::Object(const std::string& name, const std::string& mesh) : name(name), mesh(mesh), target(Ogre::Vector3::ZERO)
	{
		entity = Root::getSingleton().createEntity(name, mesh);
		entity->setUserAny(Ogre::Any(this));

		sceneNode = Root::getSingleton().createSceneNode();
		sceneNode->attachObject(entity);
		sceneNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Y);
		sceneNode->setPosition(Ogre::Math::RangeRandom(-100.0f, 100.0f), 0.0f, Ogre::Math::RangeRandom(-100.0f, 100.0f));

		shape = new Collision::Sphere(sceneNode->getPosition(), entity->getBoundingRadius());
//		shape = new Collision::AABB(sceneNode->getPosition(), entity->getMesh()->getBounds().getSize());

		shapeEntity = Root::getSingleton().createEntity(name + "_Shape", Ogre::SceneManager::PT_SPHERE);
		shapeEntity->setUserAny(Ogre::Any(this));
		shapeEntity->setMaterialName("Wireframe");

		shapeSceneNode = sceneNode->createChildSceneNode();
		shapeSceneNode->attachObject(shapeEntity);
		shapeSceneNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Y);
		shapeSceneNode->setScale(Ogre::Vector3::UNIT_SCALE * 0.01f * shape->getRadius());
		shapeSceneNode->translate(entity->getBoundingBox().getCenter());
	}

	void Object::update(float time)
	{
		const Ogre::Vector3 position = sceneNode->getPosition();

		if (position.distance(target) < 1.0f)
		{
			target.x += Ogre::Math::RangeRandom(-100.0f, 100.0f);
			target.z += Ogre::Math::RangeRandom(-100.0f, 100.0f);
		}
		else
		{
			Ogre::Vector3 velocity = (target - position).normalisedCopy() * 30.0f * time;

			sceneNode->lookAt(target, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_X);
			sceneNode->translate(velocity);

			shape->translate(velocity);
		}
	}

	Object::~Object()
	{
		delete shape;
		Root::getSingleton().destroyEntity(entity);
		Root::getSingleton().destroySceneNode(sceneNode);
	}
}
