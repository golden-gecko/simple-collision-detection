#include "StdAfx.h"

#include "Collision\Grid.h"
#include "Collision\NoTree.h"
#include "Collision\Octree.h"

#include "Game\Object.h"
#include "Game\Root.h"

Game::Root* Ogre::Singleton<Game::Root>::ms_Singleton = NULL;

namespace Game
{
	Root::Root() : render(true)
	{
		root = new Ogre::Root();

		if (root->restoreConfig() || root->showConfigDialog())
		{
			renderWindow = root->initialise(true);
			renderWindow->setDeactivateOnFocusChange(false);

			sceneManager = root->createSceneManager(Ogre::ST_GENERIC);

			camera = sceneManager->createCamera("Camera");
			camera->setPosition(0.0f, 300.0f, 300.0f);
			camera->lookAt(0.0f, 0.0f, 0.0f);
			camera->setNearClipDistance(0.1f);
			
			if (root->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE)) {
				camera->setFarClipDistance(0.0f);
			}
			else
			{
				camera->setFarClipDistance(50000.0f);
			}

			viewport = renderWindow->addViewport(camera);

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



			Collision::Vector3 min = Collision::Vector3(0.0f, 0.0f, 0.0f);
			Collision::Vector3 max = Collision::Vector3(1000.0f, 300.0f, 1000.0f);

			Ogre::ManualObject* m = sceneManager->createManualObject("map");
			
			m->begin("Map", Ogre::RenderOperation::OT_LINE_LIST);

			m->position(min.x, min.y, min.z);
			m->position(max.x, min.y, min.z);
			m->position(max.x, min.y, max.z);
			m->position(min.x, min.y, max.z);

			m->position(min.x, max.y, min.z);
			m->position(max.x, max.y, min.z);
			m->position(max.x, max.y, max.z);
			m->position(min.x, max.y, max.z);

			m->index(0);
			m->index(1);
			m->index(1);
			m->index(2);
			m->index(2);
			m->index(3);
			m->index(3);
			m->index(0);

			m->index(4);
			m->index(5);
			m->index(5);
			m->index(6);
			m->index(6);
			m->index(7);
			m->index(7);
			m->index(4);

			m->index(0);
			m->index(4);
			m->index(1);
			m->index(5);
			m->index(2);
			m->index(6);
			m->index(3);
			m->index(7);

			m->end();

			sceneManager->getRootSceneNode()->attachObject(m);

			camera->setPosition(max.x / 2.0f, max.y * 4.0f, max.z * 1.2f);
			camera->lookAt(max.x / 2.0f, min.y, max.z / 2.0f);


			srand((unsigned int)time(NULL));

			Collision::Solver* solver = new Collision::Solver();

			tree = new Collision::NoTree();
			tree->setSolver(solver);
			tree->setSize(min, max);


			tree->add(new Collision::Plane(Collision::Vector3(1.0f, 0.0f, 0.0f), min.x));
		//	tree->add(new Collision::Plane(Collision::Vector3(0.0f, 1.0f, 0.0f), min.y));
			tree->add(new Collision::Plane(Collision::Vector3(0.0f, 0.0f, 1.0f), min.z));

			tree->add(new Collision::Plane(Collision::Vector3(-1.0f, 0.0f, 0.0f), max.x));
		//	tree->add(new Collision::Plane(Collision::Vector3(0.0f, -1.0f, 0.0f), max.y));
			tree->add(new Collision::Plane(Collision::Vector3(0.0f, 0.0f, -1.0f), max.z));



			Collision::Grid* grid = dynamic_cast<Collision::Grid*>(tree);

			if (grid)
			{
				grid->setCellSize(Ogre::Vector3(100.0f, 100.0f, 100.0f));
			}

			for (int i = 0; i < 20; ++i)
			{
				std::stringstream ss;
				ss << "#" << i;

				objects.push_back(new Game::Object(ss.str(), "robot.mesh"));
			}

			tree->build();
			root->startRendering();


			for (std::vector<Game::Object*>::const_iterator i = objects.begin(); i != objects.end(); ++i)
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
		ss << renderWindow->getAverageFPS() << " FPS";

		size_t windowHnd = 0;
		renderWindow->getCustomAttribute("WINDOW", &windowHnd);

		SetWindowTextA((HWND)windowHnd, ss.str().c_str());


		keyboard->capture();
		mouse->capture();

		if (keyboard->isKeyDown(OIS::KC_ESCAPE))
		{
			render = false;
		}


		float cameraSpeed = 300.0f * evt.timeSinceLastFrame;

		if (keyboard->isKeyDown(OIS::KC_W))
		{
			camera->moveRelative(Ogre::Vector3::NEGATIVE_UNIT_Z * cameraSpeed);
		}

		if (keyboard->isKeyDown(OIS::KC_S))
		{
			camera->moveRelative(Ogre::Vector3::UNIT_Z * cameraSpeed);
		}

		if (keyboard->isKeyDown(OIS::KC_D))
		{
			camera->moveRelative(Ogre::Vector3::UNIT_X * cameraSpeed);
		}

		if (keyboard->isKeyDown(OIS::KC_A))
		{
			camera->moveRelative(Ogre::Vector3::NEGATIVE_UNIT_X * cameraSpeed);
		}

		if (keyboard->isKeyDown(OIS::KC_Q))
		{
			camera->moveRelative(Ogre::Vector3::UNIT_Y * cameraSpeed);
		}

		if (keyboard->isKeyDown(OIS::KC_Z))
		{
			camera->moveRelative(Ogre::Vector3::NEGATIVE_UNIT_Y * cameraSpeed);
		}


		for (std::vector<Game::Object*>::const_iterator i = objects.begin(); i != objects.end(); ++i)
		{
			(*i)->update(evt.timeSinceLastFrame);
		}

		return render;
	}
}
