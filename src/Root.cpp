#include "PCH.hpp"

#include "Collision/Grid.hpp"
#include "Collision/NoTree.hpp"
#include "Collision/Octree.hpp"

#include "Gecko/App.hpp"
#include "Gecko/Camera.hpp"
#include "Gecko/Light.hpp"
#include "Gecko/GameObject.hpp"
#include "Gecko/Scene.hpp"

#include "Map.hpp"
#include "Object.hpp"
#include "Root.hpp"

bool Root::frameStarted(const Ogre::FrameEvent& evt)
{
    std::cout << app->getContext()->getRenderWindow()->getStatistics().avgFPS << " FPS" << std::endl;

    /*
    TODO: Show FPS on window title.

    SetWindowTextA((HWND)app->getRenderWindowHandle(), std::format("{} FPS", renderWindow->getStatistics().avgFPS).c_str());
    */

    for (Object* object : objects)
    {
        object->update(evt.timeSinceLastFrame);
    }

    // tree->build();

    return true;
}

void Root::run(const std::vector<std::string>& meshes, int numObjects)
{
    app = std::make_shared<Gecko::App>();
    app->getRoot()->addFrameListener(this);

    input = std::make_shared<Gecko::Input>(app->getRenderWindowHandle());

    if (app->getRoot()->restoreConfig() || app->getRoot()->showConfigDialog(OgreBites::getNativeConfigDialog()))
    {
        Ogre::Vector3f size(10000.0f, 2000.0f, 10000.0f);

        std::shared_ptr<Map> map = std::make_shared<Map>(app->getRoot(), "Map", size);
        std::shared_ptr<Gecko::Light> light = std::make_shared<Gecko::Light>(map.get(), "Light");
        std::shared_ptr<Gecko::Camera> camera = std::make_shared<Gecko::Camera>(map.get(), "Camera");

        camera->setPosition(Ogre::Vector3f(size.x / 2.0f, size.y * 4.0f, size.z * 1.2f));
        camera->lookAt(Ogre::Vector3f(size.x / 2.0f, 0.0f, size.z / 2.0f));
        camera->setSpeed(1000.0f);

        // Create tree.
        Collision::Solver* solver = new Collision::Solver();

        // tree = new Collision::NoTree();
        // tree = new Collision::Grid();
        tree = new Collision::Octree();

        tree->setSolver(solver);
        tree->setSize(size);

        tree->add(new Collision::Plane(Ogre::Vector3f(1.0f, 0.0f, 0.0f), 0.0f));
        tree->add(new Collision::Plane(Ogre::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));

        tree->add(new Collision::Plane(Ogre::Vector3f(1.0f, 0.0f, 0.0f), size.x));
        tree->add(new Collision::Plane(Ogre::Vector3f(0.0f, 0.0f, 1.0f), size.z));

        grid = dynamic_cast<Collision::Grid*>(tree);
        octree = dynamic_cast<Collision::Octree*>(tree);

        if (grid)
        {
            grid->setCellSize(Ogre::Vector3f(1000.0f, 500.0f, 1000.0f));
        }
        else if (octree)
        {
            octree->setMaxDepth(4);
        }

        // Create objects.
        std::srand(static_cast<unsigned int>(time(nullptr)));

        for (int i = 0; i < numObjects; ++i)
        {
            Object* object = new Object(map.get(), std::format("Object #{}", i), meshes[rand() % meshes.size()], tree);

            objects.push_back(object);

            tree->add(object->getShape());
        }

        // Build tree.
        tree->build();

        if (grid)
        {
            map->createGrid(grid);
        }
        else if (octree)
        {
            map->createOctree(octree);
        }

        // Run app.
        app->setCamera(camera);
        app->run();

        // Free memory.
        for (Object* object : objects)
        {
            delete object;
        }

        delete tree;
        delete solver;
    }
}
