#include "Collision/Grid.hpp"
#include "Collision/NoTree.hpp"
#include "Collision/Octree.hpp"

#include "Root.hpp"

namespace
{
    std::shared_ptr<Collision::Tree> createNoTree()
    {
        return std::make_shared<Collision::NoTree>();
    }

    std::shared_ptr<Collision::Tree> createGrid(const Ogre::Vector3f& size)
    {
        std::shared_ptr<Collision::Grid> tree = std::make_shared<Collision::Grid>();

        tree->setCellSize(size);

        return tree;
    }

    std::shared_ptr<Collision::Tree> createOctree(int maxDepth)
    {
        std::shared_ptr<Collision::Octree> tree = std::make_shared<Collision::Octree>();

        tree->setMaxDepth(maxDepth);

        return tree;
    }
}

int main()
{
    Ogre::Vector3f size(10000.0f, 2000.0f, 10000.0f);

    std::vector<std::string> meshes = 
    {
        "ogrehead.mesh",
        "robot.mesh",
        "tudorhouse.mesh"
    };

    // std::make_unique<Root>()->run(size, meshes, 40, createNoTree());
    // std::make_unique<Root>()->run(size, meshes, 40, createGrid(size));
    std::make_unique<Root>()->run(size, meshes, 40, createOctree(4));

    return 0;
}
