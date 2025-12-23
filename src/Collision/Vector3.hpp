#pragma once

#include "PCH.hpp"

namespace Collision
{
	class Vector3 : public Ogre::Vector3
	{
	public:
		Vector3() : Ogre::Vector3(Ogre::Vector3::ZERO)
		{
		}

		Vector3(float x, float y, float z) : Ogre::Vector3(x, y, z)
		{
		}

		Vector3(const Ogre::Vector3& v) : Ogre::Vector3(v)
		{
		}
	};
}
