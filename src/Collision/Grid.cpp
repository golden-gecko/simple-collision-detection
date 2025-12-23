#include "PCH.hpp"

#include "Collision/AABB.hpp"
#include "Collision/Grid.hpp"

#include "Root.hpp"

namespace Collision
{
	Grid::~Grid()
	{
	}

	void Grid::build()
	{
		std::cout << "Grid::build()" << std::endl;

		// Dzielimy rozmiar siatki przez rozmiar komórki (rozmiarem komórki mo¿e byæ np. rozmiar najwiêkszego obiektu na mapie).
		// Rozmiar mapy dzielimy przez uzyskan¹ liczbê komórek i otrzymujemy optymalny rozmiar komórek.
		// Powy¿sza operacja powoduje, ¿e ¿adna z komórek nie bêdzie wychodzi³a poza obszar siatki (mapy).
		numberCells[0] = (int)Ogre::Math::Floor(size.x / cellSize.x);
		numberCells[1] = (int)Ogre::Math::Floor(size.y / cellSize.y);
		numberCells[2] = (int)Ogre::Math::Floor(size.z / cellSize.z);

		cellSize = Vector3(size.x / numberCells[0], size.y / numberCells[1], size.z / numberCells[2]);

		// Po³owa rozmiaru komórki potrzebna do okreœlenia AABB.
		Vector3 halfSize = cellSize / 2.0f;

		// Zbuduj komórki siatki.
		cells = new Cell[numberCells[0] * numberCells[1] * numberCells[2]];
		
		for (int z = 0; z < numberCells[2]; ++z)
		{
			for (int y = 0; y < numberCells[1]; ++y)
			{
				for (int x = 0; x < numberCells[0]; ++x)
				{
					int offset = (z * numberCells[1] * numberCells[0]) + (y * numberCells[0]) + x;

					cells[offset].aabb.setPosition(Vector3(
						x * cellSize.x + halfSize.x,
						y * cellSize.y + halfSize.y,
						z * cellSize.z + halfSize.z));

					cells[offset].aabb.setSize(halfSize);
				}
			}
		}

		// Przypisz obiekty (bry³y) do komórek siatki.
		for (std::vector<Shape*>::iterator i =  shapes.begin(); i != shapes.end(); ++i)
		{
			updateShape(*i);
		}
	}
	
	void Grid::updateShape(Shape* shape)
	{
		Plane* plane = dynamic_cast<Plane*>(shape);

		if (plane == nullptr)
		{
			// Oblicz wspó³rzêdne komórki.
			Vector3 cellCoordinates = shape->getPosition() / getCellSize();

			// Przypisz obiekt do komórki.
			/*
			std::cout
				<< numberCells[0] << " " << numberCells[1] << " " << numberCells[2] << "\n"
				<< shape->getPosition() << "\n"
				<< cellCoordinates << "\n"
				<< offset << std::endl;
			//*/

			Cell& cell = getCell((int)cellCoordinates.x, (int)cellCoordinates.y, (int)cellCoordinates.z);
			cell.attachShape(shape);

			/*
			if (shapesToCells[shape])
			{
				shapesToCells[shape]->detachShape(shape);
			}

			shapesToCells[shape] = &cell;
			*/
		}
	}

	bool Grid::collide(Shape* shape) const
	{
		// Indeksy s¹siednich komórek, które bêdziemy
		// przeszukiwali podczas testowania kolizji.
		static const int indexes[26][3] =
		{
			{ -1, -1, -1 },
			{ -1, -1,  0 },
			{ -1, -1,  1 },

			{ -1,  0, -1 },
			{ -1,  0,  0 },
			{ -1,  0,  1 },

			{ -1,  1, -1 },
			{ -1,  1,  0 },
			{ -1,  1,  1 },

			{  0, -1, -1 },
			{  0, -1,  0 },
			{  0, -1,  1 },

			{  0,  0, -1 },
			{  0,  0,  1 },

			{  0,  1, -1 },
			{  0,  1,  0 },
			{  0,  1,  1 },

			{  1, -1, -1 },
			{  1, -1,  0 },
			{  1, -1,  1 },

			{  1,  0, -1 },
			{  1,  0,  0 },
			{  1,  0,  1 },

			{  1,  1, -1 },
			{  1,  1,  0 },
			{  1,  1,  1 }
		};

		for (int z = 0; z < numberCells[2]; ++z)
		{
			for (int y = 0; y < numberCells[1]; ++y)
			{
				for (int x = 0; x < numberCells[0]; ++x)
				{
					const std::vector<Shape*>& shapes = getCell(x, y, z).shapes;

					for (std::vector<Shape*>::const_iterator i =  shapes.begin(); i != shapes.end(); ++i)
					{
						if (collideShapes(shape, *i))
						{
							return true;
						}
					}
				}
			}
		}

		return false;
	}
}
