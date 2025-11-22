#include "StdAfx.h"

#include "Game\Map.h"
#include "Game\Root.h"

namespace Game
{
	Map::Map(const std::string& name, const Ogre::Vector3& size) : name(name), size(size)
	{
		manual = Root::getSingleton().createManual(name);
		manual->setUserAny(Ogre::Any(this));

		manual->begin("Map", Ogre::RenderOperation::OT_LINE_LIST);

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

	void Map::createGrid(Collision::Grid* grid)
	{
		const int* numberCells = grid->getNumberCells();
		const Collision::Cell* cells = grid->getCells();

		// Wygeneruj siatkê.
		manual->begin("Map", Ogre::RenderOperation::OT_LINE_LIST);

		for (int z = 0; z < numberCells[2]; ++z)
		{
			for (int y = 0; y < numberCells[1]; ++y)
			{
				for (int x = 0; x < numberCells[0]; ++x)
				{
					int offset = (z * numberCells[1] * numberCells[0]) + (y * numberCells[0]) + x;

					const Collision::Vector3& position = cells[offset].aabb.getPosition();
					const Collision::Vector3& size = cells[offset].aabb.getSize();

					Collision::Vector3 min = position - size;
					Collision::Vector3 max = position + size;
					
					manual->position(min.x, min.y, min.z);
					manual->position(max.x, min.y, min.z);
					manual->position(max.x, min.y, max.z);
					manual->position(min.x, min.y, max.z);

					manual->position(min.x, max.y, min.z);
					manual->position(max.x, max.y, min.z);
					manual->position(max.x, max.y, max.z);
					manual->position(min.x, max.y, max.z);

					offset *= 8;

					manual->index(offset + 0);
					manual->index(offset + 1);
					manual->index(offset + 1);
					manual->index(offset + 2);
					manual->index(offset + 2);
					manual->index(offset + 3);
					manual->index(offset + 3);
					manual->index(offset + 0);

					manual->index(offset + 4);
					manual->index(offset + 5);
					manual->index(offset + 5);
					manual->index(offset + 6);
					manual->index(offset + 6);
					manual->index(offset + 7);
					manual->index(offset + 7);
					manual->index(offset + 4);

					manual->index(offset + 0);
					manual->index(offset + 4);
					manual->index(offset + 1);
					manual->index(offset + 5);
					manual->index(offset + 2);
					manual->index(offset + 6);
					manual->index(offset + 3);
					manual->index(offset + 7);
				}
			}
		}

		manual->end();
	}

	void Map::createOctree(Collision::Octree* octree)
	{

	}
}
