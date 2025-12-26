#include <iostream>

#include "Gecko/App.hpp"
#include "Gecko/Camera.hpp"
#include "Gecko/Input.hpp"
#include "Gecko/Light.hpp"
#include "Gecko/GameObject.hpp"
#include "Gecko/Scene.hpp"

#include "Map.hpp"
#include "Object.hpp"
#include "Root.hpp"

bool Root::frameStarted(const Ogre::FrameEvent& evt)
{
    std::cout << app->getContext()->getRenderWindow()->getStatistics().avgFPS << " FPS" << std::endl;

    for (Object* object : objects)
    {
        object->update(evt.timeSinceLastFrame);
    }

    tree->build();
    tree->debug(map.get());

    return true;
}

void Root::run(const Ogre::Vector3f& size, const std::vector<std::string>& meshes, int numObjects, std::shared_ptr<Collision::Tree> _tree)
{
    // Create app.
    app = std::make_shared<Gecko::App>();
    app->getRoot()->addFrameListener(this);

    input = std::make_shared<Gecko::Input>(app->getRenderWindowHandle());

    // Create scene.
    map = std::make_shared<Map>(app->getRoot(), "Map", size);

    std::shared_ptr<Gecko::Light> light = std::make_shared<Gecko::Light>(map.get(), "Light");
    std::shared_ptr<Gecko::Camera> camera = std::make_shared<Gecko::Camera>(map.get(), "Camera");

    camera->setPosition(Ogre::Vector3f(size.x / 2.0f, size.y * 4.0f, size.z * 1.2f));
    camera->lookAt(Ogre::Vector3f(size.x / 2.0f, 0.0f, size.z / 2.0f));
    camera->setSpeed(1000.0f);

    // Create solver and setup tree.
    std::shared_ptr<Collision::Solver> solver = std::make_shared<Collision::Solver>();

    tree = _tree;
    tree->setSolver(solver);
    tree->setSize(size);

    tree->add(new Collision::Plane(Ogre::Vector3f(1.0f, 0.0f, 0.0f), 0.0f));
    tree->add(new Collision::Plane(Ogre::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    tree->add(new Collision::Plane(Ogre::Vector3f(1.0f, 0.0f, 0.0f), size.x));
    tree->add(new Collision::Plane(Ogre::Vector3f(0.0f, 0.0f, 1.0f), size.z));

    // Create objects.
    std::srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < numObjects; i++)
    {
        Object* object = new Object(map.get(), std::format("Object #{}", i), meshes[rand() % meshes.size()], tree);

        objects.push_back(object);

        tree->add(object->getShape());
    }

    // Build tree.
    tree->build();
    tree->debug(map.get());

    // Run app.
    app->setCamera(camera);
    app->run();

    // Free memory.
    for (Object* object : objects)
    {
        delete object;
    }
}
