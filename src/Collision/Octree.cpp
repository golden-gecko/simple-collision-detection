#include "PCH.hpp"

#include "Octree.hpp"

namespace Collision
{
    Octree::Octree() : maxDepth(8), root(nullptr)
    {
    }
    
    Octree::~Octree()
    {
        if (root)
        {
            delete root;
        }
    }

    void Octree::build()
    {
        if (root)
        {
            delete root;
        }

        // Zbuduj pierwszy wêze³.
        root = new Cell(1);
        root->aabb.setPosition(size / 2.0f);
        root->aabb.setSize(size / 2.0f);

        // Utwórz kolejkê wez³ów do sprawdzenia.
        std::list<Cell*> cells;
        cells.push_back(root);

        // Dokonaj podzia³u ka¿dego wêz³a w kolejce.
        // Warunkiem koñca jest brak wêz³ów do podzia³u lub osi¹gniêcie maksymalnej g³êbokoœci.
        while (cells.size() > 0)
        {
            // Pobierz pierwszy wêze³ z kolejki.
            Cell* current = cells.front();

            if (current->depth >= maxDepth)
            {
                cells.pop_front();

                continue;
            }

            // Utwórz nowe wêz³y.
            Cell* newCells[8] =
            {
                new Cell(current->depth + 1),
                new Cell(current->depth + 1),
                new Cell(current->depth + 1),
                new Cell(current->depth + 1),
                new Cell(current->depth + 1),
                new Cell(current->depth + 1),
                new Cell(current->depth + 1),
                new Cell(current->depth + 1)
            };

            const Ogre::Vector3f& p = current->aabb.getPosition();
            const Ogre::Vector3f& s = current->aabb.getSize() * 0.5f;

            // Ustal pozycjê nowych wêz³ów.
            newCells[0]->aabb.setPosition(Ogre::Vector3f(p.x - s.x, p.y - s.y, p.z - s.z));
            newCells[1]->aabb.setPosition(Ogre::Vector3f(p.x + s.x, p.y - s.y, p.z - s.z));
            newCells[2]->aabb.setPosition(Ogre::Vector3f(p.x + s.x, p.y - s.y, p.z + s.z));
            newCells[3]->aabb.setPosition(Ogre::Vector3f(p.x - s.x, p.y - s.y, p.z + s.z));
            newCells[4]->aabb.setPosition(Ogre::Vector3f(p.x - s.x, p.y + s.y, p.z - s.z));
            newCells[5]->aabb.setPosition(Ogre::Vector3f(p.x + s.x, p.y + s.y, p.z - s.z));
            newCells[6]->aabb.setPosition(Ogre::Vector3f(p.x + s.x, p.y + s.y, p.z + s.z));
            newCells[7]->aabb.setPosition(Ogre::Vector3f(p.x - s.x, p.y + s.y, p.z + s.z));

            // Ustal rozmiary nowych wêz³ów.
            for (int i = 0; i < 8; ++i)
            {
                newCells[i]->aabb.setSize(s);
            }

            // SprawdŸ które obiekty mieszcz¹ siê w nowych wêz³ach.
            for (int i = 0; i < 8; ++i)
            {
                bool isCollision = false;

                // SprawdŸ czy dowolny z obiektów koliduje z wêz³em.
                // Je¿eli kolizja nie zachodzi, to usuñ wêze³.
                for (std::vector<Shape*>::const_iterator j =  shapes.begin(); j != shapes.end(); ++j)
                {
                    AABB* aabb = dynamic_cast<AABB*>(*j);

                    if (aabb && solver->collide(newCells[i]->aabb, *aabb))
                    {
                        isCollision = true;
                    }
                }

                if (isCollision == false)
                {
                    delete newCells[i];
                    newCells[i] = nullptr;
                }
            }

            // Przypisz nowe wêz³y do przetwarzanego.
            for (int i = 0; i < 8; ++i)
            {
                if (newCells[i])
                {
                    current->cells[i] = newCells[i];
                }
            }

            // Je¿eli wêz³y s¹ liœciami, to przypisz do nich obiekty.
            // Je¿eli nie, to dodaj nowe wêz³y na koniec kolejki.
            for (int i = 0; i < 8; ++i)
            {
                if (newCells[i])
                {
                    if (newCells[i]->depth >= maxDepth)
                    {
                        for (std::vector<Shape*>::const_iterator j =  shapes.begin(); j != shapes.end(); ++j)
                        {
                            AABB* aabb = dynamic_cast<AABB*>(*j);

                            if (aabb && solver->collide(newCells[i]->aabb, *aabb))
                            {
                                newCells[i]->attachShape(aabb);
                            }
                        }
                    }
                    else
                    {
                        cells.push_back(newCells[i]);
                    }
                }
            }

            // Usuñ przetworzony wêze³ z kolejki.
            cells.pop_front();
        }
    }

    bool Octree::collide(Shape* shape) const
    {
        std::list<Cell*> cells;

        for (int i = 0; i < 8; ++i)
        {
            if (root->cells[i])
            {
                cells.push_back(root->cells[i]);
            }
        }

        do
        {
            Cell* current = cells.front();

            AABB* aabb = dynamic_cast<AABB*>(shape);

            if (aabb && solver->collide(current->aabb, *aabb))
            {
                if (current->shapes.size() > 0)
                {
                    const std::vector<Shape*>& shapes = current->shapes;

                    for (std::vector<Shape*>::const_iterator j =  shapes.begin(); j != shapes.end(); ++j)
                    {
                        AABB* s1 = dynamic_cast<AABB*>(shape);
                        AABB* s2 = dynamic_cast<AABB*>(*j);

                        if (s1 != s2 && s1 && s2 && solver->collide(*s1, *s2))
                        {
                            return true;
                        }
                    }
                }
            }

            for (int i = 0; i < 8; ++i)
            {
                if (current->cells[i])
                {
                    cells.push_back(current->cells[i]);
                }
            }

            cells.pop_front();
        }
        while (cells.size() > 0);

        return false;
    }
}
