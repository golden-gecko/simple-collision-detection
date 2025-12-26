#pragma once

#include "Gecko/Scene.hpp"

class Map : public Gecko::Scene
{
public:
    Map(Ogre::Root* root, const std::string& name, const Ogre::Vector3f& size);

    ~Map() override;

    const Ogre::Vector3f& getSize() const
    {
        return size;
    }

protected:
    std::string name;
    Ogre::Vector3f size;

    Ogre::ManualObject* manual;
    Ogre::SceneNode* sceneNode;
};
