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
		sceneNode->setPosition(Ogre::Math::RangeRandom(100.0f, 900.0f), 0.0f, Ogre::Math::RangeRandom(100.0f, 900.0f));

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
		shape = new Collision::AABB(sceneNode->getPosition(), entity->getMesh()->getBoundingSphereRadius() * 0.5f);

		shapeEntity = Root::getSingleton().createEntity(name + "_Shape", Ogre::SceneManager::PT_CUBE);
		shapeEntity->setUserAny(Ogre::Any(this));
		shapeEntity->setMaterialName("Wireframe");

		shapeSceneNode = sceneNode->createChildSceneNode();
		shapeSceneNode->attachObject(shapeEntity);
		shapeSceneNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Y);
		shapeSceneNode->setScale(Ogre::Vector3::UNIT_SCALE * 0.02f * shape->getSize());
		shapeSceneNode->translate(entity->getBoundingBox().getCenter());
		//*/

		Root::getSingleton().getTree()->add(shape);

		target.x = Ogre::Math::RangeRandom(-100.0f, 1100.0f);
		target.y = 0.0f;
		target.z = Ogre::Math::RangeRandom(-100.0f, 1100.0f);

		speed = Ogre::Math::RangeRandom(10.0f, 50.0f);

		// Reprezentacja prêdkoœci oraz trasy.
		manual = Root::getSingleton().getSceneManager()->createManualObject(name + "_manual");

		Root::getSingleton().getSceneManager()->getRootSceneNode()->attachObject(manual);
	}

	void Object::update(float time)
	{
		const Ogre::Vector3& position = sceneNode->getPosition();

		if (position.distance(target) < 1.0f)
		{
			target.x = Ogre::Math::RangeRandom(-100.0f, 1100.0f);
			target.z = Ogre::Math::RangeRandom(-100.0f, 1100.0f);

			speed = Ogre::Math::RangeRandom(10.0f, 50.0f);
		}
		else
		{
			Ogre::Vector3 velocity = (target - position).normalisedCopy() * speed * time;

			// Przesuñ bry³ê. Je¿eli po przesuniêciu bry³a koliduje z innym obiektem,
			// to cofnij przesuniêcie. W przeciwnym wypadku, przesuñ ca³y obiekt.
			shape->translate(velocity);

			if (Root::getSingleton().getTree()->collide(shape))
			{
				shapeEntity->setMaterialName("Collision");

				shape->translate(-velocity);

				target = position - velocity * 100.0f;
			}
			else
			{
				shapeEntity->setMaterialName("Wireframe");

				sceneNode->lookAt(target, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_X);
				sceneNode->translate(velocity);

				shapeSceneNode->setDirection(Ogre::Vector3::UNIT_X, Ogre::Node::TS_WORLD);

				manual->clear();
				manual->begin("Track", Ogre::RenderOperation::OT_LINE_LIST);
				manual->position(position);
				manual->position(target);
				manual->end();
			}
		}
	}

	Object::~Object()
	{
		delete shape;
		Root::getSingleton().destroyEntity(entity);
		Root::getSingleton().destroySceneNode(sceneNode);
	}
}
