#include "StdAfx.h"

#include "Collision\Grid.h"
#include "Collision\NoTree.h"
#include "Collision\Octree.h"

#include "App\Map.h"
#include "App\Object.h"
#include "App\Root.h"

App::Root* Ogre::Singleton<App::Root>::msSingleton = NULL;

namespace App
{
	Root::Root() : render(true), moveObjects(true)
	{
		root = new Ogre::Root("Plugins.cfg", "Ogre.cfg", "Ogre.log");

		if (root->restoreConfig() || root->showConfigDialog(OgreBites::getNativeConfigDialog()))
		{
			renderWindow = root->initialise(true);
			renderWindow->setDeactivateOnFocusChange(false);

			sceneManager = root->createSceneManager();

			camera = sceneManager->createCamera("Camera");
			camera->setNearClipDistance(0.1f);

			cameraNode = createSceneNode();
			cameraNode->attachObject(camera);
			cameraNode->setPosition(0.0f, 300.0f, 300.0f);
			cameraNode->lookAt(Ogre::Vector3::ZERO, Ogre::Node::TransformSpace::TS_WORLD);

			if (root->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
			{
				camera->setFarClipDistance(0.0f);
			}
			else
			{
				camera->setFarClipDistance(20000.0f);
			}

			viewport = renderWindow->addViewport(camera);
			viewport->setBackgroundColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f, 1.0f));

			root->addFrameListener(this);
			Ogre::WindowEventUtilities::addWindowEventListener(renderWindow, this);

			OIS::ParamList pl;
			size_t windowHnd = 0;
			std::ostringstream windowHndStr;
			renderWindow->getCustomAttribute("WINDOW", &windowHnd);
			windowHndStr << windowHnd;
			pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
			pl.insert(std::make_pair("w32_mouse", "DISCL_FOREGROUND"));
			pl.insert(std::make_pair("w32_mouse", "DISCL_NONEXCLUSIVE"));

			inputManager = OIS::InputManager::createInputSystem(pl);
			keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
			mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));

			keyboard->setEventCallback(this);
			mouse->setEventCallback(this);

			Ogre::ConfigFile resources;
			resources.load("Resources.cfg");

			Ogre::ConfigFile::SectionIterator sections = resources.getSectionIterator();

			Ogre::String secName;
			Ogre::ConfigFile::SettingsMultiMap* settings;
			Ogre::ConfigFile::SettingsMultiMap::iterator i;

			while (sections.hasMoreElements())
			{
				secName = sections.peekNextKey();
				settings = sections.getNext();

				for (i = settings->begin(); i != settings->end(); i++)
				{
					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(i->second, i->first, secName);
				}
			}

			Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
			
			Ogre::Vector3 size(10000.0f, 2000.0f, 10000.0f);

			Map* map = new Map("Map", size);

			cameraNode->setPosition(size.x / 2.0f, size.y * 4.0f, size.z * 1.2f);
			cameraNode->lookAt(Ogre::Vector3(size.x / 2.0f, 0.0f, size.z / 2.0f), Ogre::Node::TransformSpace::TS_WORLD);


			srand((unsigned int)time(NULL));


			Collision::Solver* solver = new Collision::Solver();


//			tree = new Collision::NoTree();
//			tree = new Collision::Grid();
			tree = new Collision::Octree();

			tree->setSolver(solver);
			tree->setSize(size);


			tree->add(new Collision::Plane(Collision::Vector3(1.0f, 0.0f, 0.0f), 0.0f));
			tree->add(new Collision::Plane(Collision::Vector3(0.0f, 0.0f, 1.0f), 0.0f));

			tree->add(new Collision::Plane(Collision::Vector3(1.0f, 0.0f, 0.0f), size.x));
			tree->add(new Collision::Plane(Collision::Vector3(0.0f, 0.0f, 1.0f), size.z));

			
			grid = dynamic_cast<Collision::Grid*>(tree);
			octree = dynamic_cast<Collision::Octree*>(tree);

			if (grid)
			{
				grid->setCellSize(Ogre::Vector3(1000.0f, 500.0f, 1000.0f));
			}
			else if (octree)
			{
				octree->setMaxDepth(4);
			}


			const int meshCount = 3;
			const std::string meshes[meshCount] =
			{
				"robot.mesh",
				"RZR-002.mesh",
				"tudorhouse.mesh"
			};

			for (int i = 0; i < 50; ++i)
			{
				std::stringstream ss;
				ss << "#" << i;

				objects.push_back(new App::Object(ss.str(), meshes[rand() % meshCount], map));
			}
			
			tree->build();


			if (grid)
			{
				map->createGrid(grid);
			}
			else if (octree)
			{
				map->createOctree(octree);
			}

			root->startRendering();

			for (std::vector<App::Object*>::const_iterator i = objects.begin(); i != objects.end(); ++i)
			{
				delete (*i);
			}

			delete tree;
			delete solver;
		}
	}

	bool Root::frameStarted(const Ogre::FrameEvent& evt)
	{
		std::stringstream ss;
		ss << renderWindow->getStatistics().lastFPS << " FPS";

		size_t windowHnd = 0;
		renderWindow->getCustomAttribute("WINDOW", &windowHnd);

		SetWindowTextA((HWND)windowHnd, ss.str().c_str());


		keyboard->capture();
		mouse->capture();

		if (keyboard->isKeyDown(OIS::KC_ESCAPE))
		{
			render = false;
		}


		float cameraSpeed = 1000.0f * evt.timeSinceLastFrame;

		if (keyboard->isKeyDown(OIS::KC_W))
		{
			cameraNode->translate(Ogre::Vector3::NEGATIVE_UNIT_Z * cameraSpeed);
		}

		if (keyboard->isKeyDown(OIS::KC_S))
		{
			cameraNode->translate(Ogre::Vector3::UNIT_Z * cameraSpeed);
		}

		if (keyboard->isKeyDown(OIS::KC_D))
		{
			cameraNode->translate(Ogre::Vector3::UNIT_X * cameraSpeed);
		}

		if (keyboard->isKeyDown(OIS::KC_A))
		{
			cameraNode->translate(Ogre::Vector3::NEGATIVE_UNIT_X * cameraSpeed);
		}

		if (keyboard->isKeyDown(OIS::KC_Q))
		{
			cameraNode->translate(Ogre::Vector3::UNIT_Y * cameraSpeed);
		}

		if (keyboard->isKeyDown(OIS::KC_Z))
		{
			cameraNode->translate(Ogre::Vector3::NEGATIVE_UNIT_Y * cameraSpeed);
		}


		for (std::vector<App::Object*>::const_iterator i = objects.begin(); i != objects.end(); ++i)
		{
			(*i)->update(evt.timeSinceLastFrame);
		}

		return render;
	}

	bool Root::mouseMoved(const OIS::MouseEvent& arg)
	{
		cameraNode->yaw(Ogre::Degree(-arg.state.X.rel * 0.1f));
		cameraNode->pitch(Ogre::Degree(-arg.state.Y.rel * 0.1f));

		return true;
	}

	bool Root::keyPressed(const OIS::KeyEvent& arg)
	{
		if (arg.key == OIS::KC_M)
		{
			moveObjects = !moveObjects;
		}

		return true;
	}
}
