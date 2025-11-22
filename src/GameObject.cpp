#include "StdAfx.h"

#include "GameObject.h"
#include "Root.h"

namespace Collision
{
	GameObject::GameObject(const std::string& name, const std::string& mesh) : name(name), mesh(mesh), target(Ogre::Vector3::ZERO)
	{
		entity = Root::getSingleton().createEntity(name, mesh);
		entity->setUserAny(Ogre::Any(this));

		sceneNode = Root::getSingleton().createSceneNode();
		sceneNode->attachObject(entity);
		sceneNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Y);
	}

	void GameObject::update(float time)
	{
		const Ogre::Vector3 position = sceneNode->getPosition();

		if (position.distance(target) < 1.0f)
		{
			target.x += Ogre::Math::RangeRandom(-100.0f, 100.0f);
			target.z += Ogre::Math::RangeRandom(-100.0f, 100.0f);
		}
		else
		{
			sceneNode->lookAt(target, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_X);
			sceneNode->translate((target - position).normalisedCopy() * 30.0f * time);
		}
	}

	GameObject::~GameObject()
	{
	}
}
