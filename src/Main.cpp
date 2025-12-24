#include "PCH.hpp"

#include "Root.hpp"

int main()
{
    std::vector<std::string> meshes = 
    {
        "ogrehead.mesh",
        "robot.mesh",
        "tudorhouse.mesh"
    };

    std::make_unique<Root>()->run(meshes, 40);

    return 0;
}
