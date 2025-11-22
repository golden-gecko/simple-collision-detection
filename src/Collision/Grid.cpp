#include "StdAfx.h"

#include "Collision\AABB.h"
#include "Collision\Grid.h"

#include "Game\Root.h"

namespace Collision
{
	Grid::~Grid()
	{
	}

	void Grid::build()
	{
		std::cout << "Grid::build()" << std::endl;

		// Okreœl wymiary komórki siatki.
		numberCells = Vector3(size.x / cellSize.x, size.y / cellSize.y, size.z / cellSize.z);

		// Zbuduj siatkê.
		std::vector<std::vector<std::vector<Ogre::Entity*>>> entities;
		std::vector<std::vector<std::vector<Ogre::SceneNode*>>> sceneNodes;

		entities.resize((unsigned int)numberCells.x);
		sceneNodes.resize((unsigned int)numberCells.x);

		for (unsigned int x = 0; x < (unsigned int)numberCells.x; ++x)
		{
			entities[x].resize((unsigned int)numberCells.y);
			sceneNodes[x].resize((unsigned int)numberCells.y);

			for (unsigned int y = 0; y < (unsigned int)numberCells.y; ++y)
			{
				entities[x][y].resize((unsigned int)numberCells.z);
				sceneNodes[x][y].resize((unsigned int)numberCells.z);

				for (unsigned int z = 0; z < (unsigned int)numberCells.z; ++z)
				{
					std::stringstream ss;
					ss << "grid_" << x << "_" << y << "_" << z;

					entities[x][y][z] = Game::Root::getSingleton().createEntity(ss.str(), Ogre::SceneManager::PT_CUBE);
					entities[x][y][z]->setMaterialName("Tree");

					sceneNodes[x][y][z] = Game::Root::getSingleton().createSceneNode();
					sceneNodes[x][y][z]->attachObject(entities[x][y][z]);
					sceneNodes[x][y][z]->setScale(cellSize * 0.01f);
					sceneNodes[x][y][z]->setPosition(cellSize.x * x, cellSize.y * y, cellSize.z * z);
				}
			}
		}
	}
	
	bool Grid::collide(Shape* shape) const
	{
		return true;
	}
}
