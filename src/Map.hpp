#pragma once

#include "PCH.hpp"

#include "Gecko/Scene.hpp"

#include "Collision/Grid.hpp"
#include "Collision/Octree.hpp"

class Map : public Gecko::Scene
{
public:
    Map(Ogre::Root* root, const std::string& name, const Ogre::Vector3f& size);

    ~Map() override;

    const Ogre::Vector3f& getSize() const
    {
        return size;
    }

    void createGrid(Collision::Grid* grid);
    void createOctree(Collision::Octree* octree);

protected:
    std::string name;
    Ogre::Vector3f size;

    Ogre::ManualObject* manual;
    Ogre::SceneNode* sceneNode;
};
