#include "StdAfx.h"

#include "Octree.h"

namespace Collision
{
	Octree::Octree() : maxDepth(8), root(NULL)
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
		std::cout << "Octre::build()" << std::endl;

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

			const Vector3& p = current->aabb.getPosition();
			const Vector3& s = current->aabb.getSize() * 0.5f;

			// Ustal pozycjê nowych wêz³ów.
			newCells[0]->aabb.setPosition(Vector3(p.x - s.x, p.y - s.y, p.z - s.z));
			newCells[1]->aabb.setPosition(Vector3(p.x + s.x, p.y - s.y, p.z - s.z));
			newCells[2]->aabb.setPosition(Vector3(p.x + s.x, p.y - s.y, p.z + s.z));
			newCells[3]->aabb.setPosition(Vector3(p.x - s.x, p.y - s.y, p.z + s.z));
			newCells[4]->aabb.setPosition(Vector3(p.x - s.x, p.y + s.y, p.z - s.z));
			newCells[5]->aabb.setPosition(Vector3(p.x + s.x, p.y + s.y, p.z - s.z));
			newCells[6]->aabb.setPosition(Vector3(p.x + s.x, p.y + s.y, p.z + s.z));
			newCells[7]->aabb.setPosition(Vector3(p.x - s.x, p.y + s.y, p.z + s.z));

			// Ustal rozmiary nowych wêz³ów.
			for (int i = 0; i < 8; ++i)
			{
				newCells[i]->aabb.setSize(s);
			}

			// SprawdŸ które obiekty mieszcz¹ siê w nowych wêz³ach.
			for (std::vector<Shape*>::const_iterator i =  shapes.begin(); i != shapes.end(); ++i)
			{

			}

			// Przypisz nowe wêz³y do przetwarzanego.
			for (int i = 0; i < 8; ++i)
			{
				current->cells[i] = newCells[i];
			}

			// Dodaj nowe wêz³y na koniec kolejki.
			for (int i = 0; i < 8; ++i)
			{
				cells.push_back(newCells[i]);
			}

			// Usuñ przetworzony wêze³ z kolejki.
			cells.pop_front();
		}
	}

	bool Octree::collide(Shape* shape) const
	{
		return true;
	}
}
