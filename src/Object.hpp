#pragma once

#include "PCH.hpp"

#include "Gecko/GameObject.hpp"

#include "Collision/AABB.hpp"
#include "Collision/OBB.hpp"
#include "Collision/Sphere.hpp"

namespace Collision
{
    class Tree;
}

class Map;

class Object : public Gecko::GameObject
{
public:
    Object(Map* map, const std::string& name, const std::string& mesh, std::shared_ptr<Collision::Tree> tree);
    
    ~Object() override;

    void update(float time) override;

    Collision::Shape* getShape() const
    {
        return shape;
    }

protected:
    Collision::AABB* shape = nullptr;
    // Collision::OBB* shape = nullptr;
    // Collision::Sphere* shape = nullptr;

    Ogre::Entity* shapeEntity = nullptr;
    Ogre::SceneNode* shapeSceneNode = nullptr;

    Ogre::ManualObject* path = nullptr;
    Ogre::SceneNode* pathSceneNode = nullptr;

    Ogre::Vector3f target = Ogre::Vector3f::ZERO;
    float speed;

    Map* map = nullptr;
    std::shared_ptr<Collision::Tree> tree;

    void setRandomTarget();
    void setRandomSpeed();
};
