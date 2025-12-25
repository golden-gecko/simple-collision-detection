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
