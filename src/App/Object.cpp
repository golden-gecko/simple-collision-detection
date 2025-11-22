#include "StdAfx.h"

#include "Collision\AABB.h"
#include "Collision\OBB.h"
#include "Collision\Sphere.h"

#include "App\Object.h"
#include "App\Root.h"

namespace App
{
	Object::Object(const std::string& name, const std::string& mesh, Map* map)
		: name(name), mesh(mesh), target(Ogre::Vector3::ZERO), map(map)
	{
		entity = Root::getSingleton().createEntity(name, mesh);
		entity->setUserAny(Ogre::Any(this));

		sceneNode = Root::getSingleton().createSceneNode();
		sceneNode->attachObject(entity);
		sceneNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Y);
		sceneNode->setPosition(
			Ogre::Math::RangeRandom(100.0f, map->getSize().x - 100.0f), 0.0f,
			Ogre::Math::RangeRandom(100.0f, map->getSize().z - 100.0f));

		/*
		shape = new Collision::AABB(sceneNode->getPosition(),
			entity->getMesh()->getBoundingSphereRadius() * 0.5f * Collision::Vector3::UNIT_SCALE);

		shapeEntity = Root::getSingleton().createEntity(name + "_Shape", Ogre::SceneManager::PT_CUBE);
		shapeEntity->setUserAny(Ogre::Any(this));
		shapeEntity->setMaterialName("Wireframe");

		shapeSceneNode = sceneNode->createChildSceneNode();
		shapeSceneNode->attachObject(shapeEntity);
		shapeSceneNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Y);
		shapeSceneNode->setScale(Ogre::Vector3::UNIT_SCALE / shapeEntity->getBoundingBox().getSize() * shape->getSize() * 2.0f);
		shapeSceneNode->translate(entity->getBoundingBox().getCenter());
		//*/

		//*
		shape = new Collision::OBB(sceneNode->getPosition(),
			entity->getMesh()->getBounds().getSize() * 0.5f * Collision::Vector3::UNIT_SCALE);

		shapeEntity = Root::getSingleton().createEntity(name + "_Shape", Ogre::SceneManager::PT_CUBE);
		shapeEntity->setUserAny(Ogre::Any(this));
		shapeEntity->setMaterialName("Wireframe");

		shapeSceneNode = sceneNode->createChildSceneNode();
		shapeSceneNode->attachObject(shapeEntity);
		shapeSceneNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Y);
		shapeSceneNode->setScale(Ogre::Vector3::UNIT_SCALE / shapeEntity->getBoundingBox().getSize() * shape->getSize() * 2.0f);
		shapeSceneNode->translate(entity->getBoundingBox().getCenter());
		//*/

		/*
		shape = new Collision::Sphere(sceneNode->getPosition(), entity->getBoundingRadius());

		shapeEntity = Root::getSingleton().createEntity(name + "_Shape", Ogre::SceneManager::PT_SPHERE);
		shapeEntity->setUserAny(Ogre::Any(this));
		shapeEntity->setMaterialName("Wireframe");

		shapeSceneNode = sceneNode->createChildSceneNode();
		shapeSceneNode->attachObject(shapeEntity);
		shapeSceneNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Y);
		shapeSceneNode->setScale(Ogre::Vector3::UNIT_SCALE / shapeEntity->getBoundingBox().getSize() * shape->getRadius() * 2.0f);
		shapeSceneNode->translate(entity->getBoundingBox().getCenter());

		path = Root::getSingleton().getSceneManager()->createManualObject(name + "_m");
		Root::getSingleton().getSceneManager()->getRootSceneNode()->attachObject(path);
		//*/

		Root::getSingleton().getTree()->add(shape);

		setRandomTarget();
		setRandomSpeed();

		// Reprezentacja prêdkoœci oraz trasy.
		path = Root::getSingleton().getSceneManager()->createManualObject(name + "_path");
		path->begin("Track", Ogre::RenderOperation::OT_LINE_LIST);
		path->position(Ogre::Vector3::ZERO);
		path->position(Ogre::Vector3::UNIT_X);
		path->end();

		pathSceneNode = sceneNode->createChildSceneNode();
		pathSceneNode->attachObject(path);
	}

	void Object::update(float time)
	{
		const Ogre::Vector3& position = sceneNode->getPosition();

		if (position.distance(target) < 1.0f)
		{
			setRandomTarget();
			setRandomSpeed();
		}
		else
		{
			if (Root::getSingleton().getMoveObjects())
			{
				Ogre::Vector3 velocity = (target - position).normalisedCopy() * speed * time;

				// Przesuñ bry³ê. Je¿eli po przesuniêciu bry³a koliduje z innym obiektem,
				// to cofnij przesuniêcie. W przeciwnym wypadku, przesuñ ca³y obiekt.
				shape->translate(velocity);

				if (Root::getSingleton().getTree()->collide(shape))
				{
					shapeEntity->setMaterialName("Collision");

					shape->translate(-velocity);

					target = position - velocity * 200.0f;
				}
				else
				{
					shapeEntity->setMaterialName("Wireframe");

					sceneNode->lookAt(target, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_X);
					sceneNode->translate(velocity);

					if (dynamic_cast<Collision::AABB*>(shape)) {
						shapeSceneNode->setDirection(Ogre::Vector3::UNIT_X, Ogre::Node::TS_WORLD);
					}

					pathSceneNode->setScale(Ogre::Vector3::UNIT_SCALE * (target - position).length());
				}
			}
		}
	}

	Object::~Object()
	{
		delete shape;
		Root::getSingleton().destroyEntity(entity);
		Root::getSingleton().destroySceneNode(sceneNode);
	}

	void Object::setRandomTarget()
	{
		target.x = Ogre::Math::RangeRandom(-1000.0f, map->getSize().x + 1000.0f);
		target.y = 0.0f;
		target.z = Ogre::Math::RangeRandom(-1000.0f, map->getSize().z + 1000.0f);
	}

	void Object::setRandomSpeed()
	{
		speed = Ogre::Math::RangeRandom(100.0f, 100.0f);
	}
}
