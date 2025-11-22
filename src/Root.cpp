#include "StdAfx.h"

#include "GameObject.h"
#include "Root.h"

Collision::Root* Ogre::Singleton<Collision::Root>::ms_Singleton = NULL;

namespace Collision
{
	Root::Root() : render(true)
	{
		root = new Ogre::Root();

		if (root->restoreConfig() || root->showConfigDialog())
		{
			renderWindow = root->initialise(true);
			sceneManager = root->createSceneManager(Ogre::ST_GENERIC);
			camera = sceneManager->createCamera("Camera");
			camera->setPosition(300.0f, 300.0f, 300.0f);
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


			objects.push_back(new GameObject("#1", "robot.mesh"));
			objects.push_back(new GameObject("#2", "robot.mesh"));
			objects.push_back(new GameObject("#3", "robot.mesh"));
			objects.push_back(new GameObject("#4", "robot.mesh"));


			root->startRendering();
		}
	}

	bool Root::frameStarted(const Ogre::FrameEvent& evt)
	{
		keyboard->capture();
		mouse->capture();

		if (keyboard->isKeyDown(OIS::KC_ESCAPE))
		{
			render = false;
		}

		for (std::vector<GameObject*>::const_iterator i = objects.begin(); i != objects.end(); ++i)
		{
			(*i)->update(evt.timeSinceLastFrame);
		}

		return render;
	}
}
