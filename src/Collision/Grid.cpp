#include "StdAfx.h"

#include "Collision\AABB.h"
#include "Collision\Grid.h"

#include "Game\Root.h"

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
		cells = new Collision::AABB[numberCells[0] * numberCells[1] * numberCells[2]];
		
		for (int z = 0; z < numberCells[2]; ++z)
		{
			for (int y = 0; y < numberCells[1]; ++y)
			{
				for (int x = 0; x < numberCells[0]; ++x)
				{
					int offset = (z * numberCells[1] * numberCells[0]) + (y * numberCells[0]) + x;

					cells[offset].setPosition(Vector3(
						x * cellSize.x + halfSize.x,
						y * cellSize.y + halfSize.y,
						z * cellSize.z + halfSize.z));

					cells[offset].setSize(halfSize);
				}
			}
		}
	}
	
	bool Grid::collide(Shape* shape) const
	{
		return true;
	}
}
