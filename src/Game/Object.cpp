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
		sceneNode->setPosition(Ogre::Math::RangeRandom(-300.0f, 300.0f), 0.0f, Ogre::Math::RangeRandom(-300.0f, 300.0f));

		//*
		shape = new Collision::Sphere(sceneNode->getPosition(), entity->getBoundingRadius() * 0.5f);

		shapeEntity = Root::getSingleton().createEntity(name + "_Shape", Ogre::SceneManager::PT_SPHERE);
		shapeEntity->setUserAny(Ogre::Any(this));
		shapeEntity->setMaterialName("Wireframe");

		shapeSceneNode = sceneNode->createChildSceneNode();
		shapeSceneNode->attachObject(shapeEntity);
		shapeSceneNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Y);
		shapeSceneNode->setScale(Ogre::Vector3::UNIT_SCALE * 0.01f * shape->getRadius() * 2.0f);
		shapeSceneNode->translate(entity->getBoundingBox().getCenter());

		manual = Root::getSingleton().getSceneManager()->createManualObject(name + "_m");
		Root::getSingleton().getSceneManager()->getRootSceneNode()->attachObject(manual);

		//*/

		/*
		shape = new Collision::AABB(sceneNode->getPosition(), entity->getMesh()->getBoundingSphereRadius() * Ogre::Vector3::UNIT_SCALE);

		shapeEntity = Root::getSingleton().createEntity(name + "_Shape", Ogre::SceneManager::PT_CUBE);
		shapeEntity->setUserAny(Ogre::Any(this));
		shapeEntity->setMaterialName("Wireframe");

		shapeSceneNode = sceneNode->createChildSceneNode();
		shapeSceneNode->attachObject(shapeEntity);
		shapeSceneNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Y);
		shapeSceneNode->setScale(Ogre::Vector3::UNIT_SCALE * 0.01f * shape->getSize());
		shapeSceneNode->translate(entity->getBoundingBox().getCenter());
		//*/

		Root::getSingleton().getTree()->add(shape);
	}

	void Object::update(float time)
	{
		const Ogre::Vector3& position = sceneNode->getPosition();

		if (position.distance(target) < 1.0f)
		{
			target.x += Ogre::Math::RangeRandom(-100.0f, 100.0f);
			target.z += Ogre::Math::RangeRandom(-100.0f, 100.0f);
		}
		else
		{
			Ogre::Vector3 velocity = (target - position).normalisedCopy() * 30.0f * time;

			sceneNode->lookAt(target, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_X);

			if (Root::getSingleton().getTree()->canMove(shape, velocity))
			{
				sceneNode->translate(velocity);

				shapeSceneNode->setDirection(Ogre::Vector3::UNIT_X, Ogre::Node::TS_WORLD);

				shape->translate(velocity);
			}
		}

		/*
		manual->clear();
		manual->begin("Manual", Ogre::RenderOperation::OT_LINE_LIST);

		manual->position(shape->getPosition());
		manual->position(shape->getPosition() + Ogre::Vector3::UNIT_X * shape->getRadius());

		manual->position(shape->getPosition());
		manual->position(shape->getPosition() + Ogre::Vector3::UNIT_Y * shape->getRadius());
		
		manual->position(shape->getPosition());
		manual->position(shape->getPosition() + Ogre::Vector3::UNIT_Z * shape->getRadius());

		manual->position(shape->getPosition());
		manual->position(shape->getPosition() + Ogre::Vector3::NEGATIVE_UNIT_X * shape->getRadius());

		manual->position(shape->getPosition());
		manual->position(shape->getPosition() + Ogre::Vector3::NEGATIVE_UNIT_Y * shape->getRadius());
		
		manual->position(shape->getPosition());
		manual->position(shape->getPosition() + Ogre::Vector3::NEGATIVE_UNIT_Z * shape->getRadius());

		manual->end();
		//*/
	}

	Object::~Object()
	{
		delete shape;
		Root::getSingleton().destroyEntity(entity);
		Root::getSingleton().destroySceneNode(sceneNode);
	}
}
