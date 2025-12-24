#include "PCH.hpp"

#include "Map.hpp"
#include "Root.hpp"

Map::Map(Ogre::Root* root, const std::string& name, const Ogre::Vector3f& size) : Gecko::Scene(root), name(name), size(size)
{
    manual = sceneManager->createManualObject(name);
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

    sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    sceneNode->attachObject(manual);
}

Map::~Map()
{
    sceneManager->destroySceneNode(sceneNode);
    sceneManager->destroyManualObject(manual);
}

void Map::createGrid(Collision::Grid* grid)
{
    const int* numberCells = grid->getNumberCells();
    const Collision::Grid::Cell* cells = grid->getCells();

    // Wygeneruj siatkê.
    manual->begin("Map", Ogre::RenderOperation::OT_LINE_LIST);

    for (int z = 0; z < numberCells[2]; ++z)
    {
        for (int y = 0; y < numberCells[1]; ++y)
        {
            for (int x = 0; x < numberCells[0]; ++x)
            {
                int offset = (z * numberCells[1] * numberCells[0]) + (y * numberCells[0]) + x;

                const Ogre::Vector3f& position = cells[offset].aabb.getPosition();
                const Ogre::Vector3f& size = cells[offset].aabb.getSize();

                Ogre::Vector3f min = position - size;
                Ogre::Vector3f max = position + size;
                    
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
    // Wygeneruj siatkê.
    manual->begin("Map", Ogre::RenderOperation::OT_LINE_LIST);

    std::list<Collision::Octree::Cell*> cells;
    cells.push_back(octree->getRoot());

    int offset = 0;

    while (cells.size() > 0)
    {
        Collision::Octree::Cell* current = cells.front();

        const Ogre::Vector3f& position = current->aabb.getPosition();
        const Ogre::Vector3f& size = current->aabb.getSize();

        Ogre::Vector3f min = position - size;
        Ogre::Vector3f max = position + size;

        manual->position(min.x, min.y, min.z);
        manual->position(max.x, min.y, min.z);
        manual->position(max.x, min.y, max.z);
        manual->position(min.x, min.y, max.z);

        manual->position(min.x, max.y, min.z);
        manual->position(max.x, max.y, min.z);
        manual->position(max.x, max.y, max.z);
        manual->position(min.x, max.y, max.z);

        offset += 8;

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

        for (int i = 0; i < 8; ++i)
        {
            if (current->cells[i])
            {
                cells.push_back(current->cells[i]);
            }
        }

        cells.pop_front();
    }

    manual->end();
}
