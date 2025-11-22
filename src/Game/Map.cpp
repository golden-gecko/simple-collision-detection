#include "StdAfx.h"

#include "Game\Map.h"
#include "Game\Root.h"

namespace Game
{
	Map::Map(const std::string& name, const Ogre::Vector3& size) : name(name), size(size)
	{
		manual = Root::getSingleton().createManual(name);
		manual->setUserAny(Ogre::Any(this));

		manual->begin(name, Ogre::RenderOperation::OT_LINE_LIST);

		manual->position(0.0f, 0.0f, 0.0f);
		manual->position(size.x, 0.0f, 0.0f);
		manual->position(size.x, 0.0f, size.z);
		manual->position(0.0f, 0.0f, size.z);

		manual->position(0.0f, size.y, 0.0f);
		manual->position(size.x, size.y, 0.0f);
		manual->position(size.x, size.y, size.z);
		manual->position(0.0f, size.y, size.z);

		manual->index(0);
		manual->index(1);
		manual->index(1);
		manual->index(2);
		manual->index(2);
		manual->index(3);
		manual->index(3);
		manual->index(0);

		manual->index(4);
		manual->index(5);
		manual->index(5);
		manual->index(6);
		manual->index(6);
		manual->index(7);
		manual->index(7);
		manual->index(4);

		manual->index(0);
		manual->index(4);
		manual->index(1);
		manual->index(5);
		manual->index(2);
		manual->index(6);
		manual->index(3);
		manual->index(7);

		manual->end();

		sceneNode = Root::getSingleton().createSceneNode();
		sceneNode->attachObject(manual);
	}

	Map::~Map()
	{
		Root::getSingleton().destroyManual(manual);
		Root::getSingleton().destroySceneNode(sceneNode);
	}
}
