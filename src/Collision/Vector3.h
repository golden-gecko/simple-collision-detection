#pragma once

#include "StdAfx.h"

namespace Collision
{
	class Vector3 : public Ogre::Vector3
	{
	public:
		Vector3(const Ogre::Vector3& v) : Ogre::Vector3(v)
		{
		}
	};
}
