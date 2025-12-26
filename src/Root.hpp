#pragma once

#include "Collision/Tree.hpp"

#include "Object.hpp"

namespace Gecko
{
    class App;
    class Input;
}

class Root : public Ogre::FrameListener
{
public:
    // Ogre::FrameListener
    bool frameStarted(const Ogre::FrameEvent& evt) override;

public:
    void run(const Ogre::Vector3f& size, const std::vector<std::string>& meshes, int numObjects, std::shared_ptr<Collision::Tree> tree);

    std::shared_ptr<Collision::Tree> getTree() const
    {
        return tree;
    }

protected:
    std::shared_ptr<Gecko::App> app;
    std::shared_ptr<Gecko::Input> input;
    std::shared_ptr<Map> map;
    std::shared_ptr<Collision::Tree> tree;
    std::vector<Object*> objects;
};
