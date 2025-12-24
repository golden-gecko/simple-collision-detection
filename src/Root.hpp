#pragma once

#include "PCH.hpp"

#include "Collision/Grid.hpp"
#include "Collision/Octree.hpp"

#include "Gecko/App.hpp"
#include "Gecko/Input.hpp"

#include "Object.hpp"

class Root : public Ogre::FrameListener
{
public:
    // Ogre::FrameListener
    bool frameStarted(const Ogre::FrameEvent& evt) override;

public:
    void run(const std::vector<std::string>& meshes, int numObjects);

    Collision::Tree* getTree() const
    {
        return tree;
    }

protected:
    std::shared_ptr<Gecko::App> app;
    std::shared_ptr<Gecko::Input> input;

    std::vector<Object*> objects;

    Collision::Tree* tree = nullptr;
    Collision::Grid* grid = nullptr;
    Collision::Octree* octree = nullptr;
};
