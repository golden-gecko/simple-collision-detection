#include "Collision/AABB.hpp"
#include "Collision/OBB.hpp"
#include "Collision/Sphere.hpp"

#include "Object.hpp"
#include "Map.hpp"
#include "Root.hpp"

Object::Object(Map* map, const std::string& name, const std::string& mesh, std::shared_ptr<Collision::Tree> tree) : Gecko::GameObject(map, name, mesh), map(map), tree(tree)
{
    //*
    entity->getUserObjectBindings().setUserAny(Ogre::Any(this));

    sceneNode->setFixedYawAxis(true, Ogre::Vector3f::UNIT_Y);
    sceneNode->setPosition(Ogre::Math::RangeRandom(100.0f, map->getSize().x - 100.0f), 0.0f, Ogre::Math::RangeRandom(100.0f, map->getSize().z - 100.0f));
    //*/

    //*
    shape = new Collision::AABB(sceneNode->getPosition(), entity->getMesh()->getBoundingSphereRadius() * 0.5f * Ogre::Vector3f::UNIT_SCALE);

    shapeEntity = sceneManager->createEntity(name + "_Shape", Ogre::SceneManager::PT_CUBE);
    shapeEntity->getUserObjectBindings().setUserAny(Ogre::Any(this));
    shapeEntity->setMaterialName("Wireframe");

    shapeSceneNode = sceneNode->createChildSceneNode();
    shapeSceneNode->attachObject(shapeEntity);
    shapeSceneNode->setScale(Ogre::Vector3f::UNIT_SCALE / shapeEntity->getBoundingBox().getSize() * shape->getSize() * 2.0f);
    shapeSceneNode->setFixedYawAxis(true, Ogre::Vector3f::UNIT_Y);
    shapeSceneNode->translate(entity->getBoundingBox().getCenter());
    //*/

    /*
    shape = new Collision::OBB(sceneNode->getPosition(), entity->getMesh()->getBounds().getSize() * 0.5f * Ogre::Vector3f::UNIT_SCALE);

    shapeEntity = sceneManager->createEntity(name + "_Shape", Ogre::SceneManager::PT_CUBE);
    shapeEntity->getUserObjectBindings().setUserAny(Ogre::Any(this));
    shapeEntity->setMaterialName("Wireframe");

    shapeSceneNode = sceneNode->createChildSceneNode();
    shapeSceneNode->attachObject(shapeEntity);
    shapeSceneNode->setScale(Ogre::Vector3f::UNIT_SCALE / shapeEntity->getBoundingBox().getSize() * shape->getSize() * 2.0f);
    shapeSceneNode->setFixedYawAxis(true, Ogre::Vector3f::UNIT_Y);
    shapeSceneNode->translate(entity->getBoundingBox().getCenter());
    //*/

    /*
    shape = new Collision::Sphere(sceneNode->getPosition(), entity->getBoundingRadius());

    shapeEntity = sceneManager->createEntity(name + "_Shape", Ogre::SceneManager::PT_SPHERE);
    shapeEntity->getUserObjectBindings().setUserAny(Ogre::Any(this));
    shapeEntity->setMaterialName("Wireframe");

    shapeSceneNode = sceneNode->createChildSceneNode();
    shapeSceneNode->attachObject(shapeEntity);
    shapeSceneNode->setScale(Ogre::Vector3f::UNIT_SCALE / shapeEntity->getBoundingBox().getSize() * shape->getRadius() * 2.0f);
    shapeSceneNode->setFixedYawAxis(true, Ogre::Vector3f::UNIT_Y);
    shapeSceneNode->translate(entity->getBoundingBox().getCenter());
    //*/

    // Reprezentacja prêdkoœci oraz trasy.
    path = sceneManager->createManualObject(name + "_path");
    path->begin("Path", Ogre::RenderOperation::OT_LINE_LIST);

    path->position(Ogre::Vector3f::ZERO);
    path->position(Ogre::Vector3f::UNIT_X);

    path->index(0);
    path->index(1);

    path->end();

    pathSceneNode = sceneNode->createChildSceneNode();
    pathSceneNode->attachObject(path);

    setRandomTarget();
    setRandomSpeed();
}

void Object::update(float time)
{
    const Ogre::Vector3f& position = sceneNode->getPosition();

    if (position.distance(target) < 1.0f)
    {
        setRandomTarget();
        setRandomSpeed();
    }
    else
    {
        Ogre::Vector3f velocity = (target - position).normalisedCopy() * speed * time;

        // Przesuñ bry³ê. Je¿eli po przesuniêciu bry³a koliduje z innym obiektem,
        // to cofnij przesuniêcie. W przeciwnym wypadku, przesuñ ca³y obiekt.
        shape->translate(velocity);

        if (tree->collide(shape))
        {
            shapeEntity->setMaterialName("Collision");

            shape->translate(-velocity);

            target = position - velocity * 200.0f;
        }
        else
        {
            shapeEntity->setMaterialName("Wireframe");

            sceneNode->lookAt(target, Ogre::Node::TS_PARENT, Ogre::Vector3f::UNIT_X);
            sceneNode->translate(velocity);

            if (dynamic_cast<Collision::AABB*>(shape))
            {
                shapeSceneNode->setDirection(Ogre::Vector3f::UNIT_X, Ogre::Node::TS_WORLD);
            }

            pathSceneNode->setScale(Ogre::Vector3f::UNIT_SCALE * (target - position).length());
        }
    }
}

Object::~Object()
{
    delete shape;
}

void Object::setRandomTarget()
{
    target.x = Ogre::Math::RangeRandom(-1000.0f, map->getSize().x + 1000.0f);
    target.y = 0.0f;
    target.z = Ogre::Math::RangeRandom(-1000.0f, map->getSize().z + 1000.0f);
}

void Object::setRandomSpeed()
{
    speed = Ogre::Math::RangeRandom(100.0f, 100.0f);
}
