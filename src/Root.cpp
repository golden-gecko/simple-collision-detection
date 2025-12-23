#include "PCH.hpp"

#include "Collision/Grid.hpp"
#include "Collision/NoTree.hpp"
#include "Collision/Octree.hpp"

#include "Gecko/App.hpp"
#include "Gecko/Camera.hpp"
#include "Gecko/Light.hpp"
#include "Gecko/GameObject.hpp"
#include "Gecko/Scene.hpp"

#include "Map.hpp"
#include "Object.hpp"
#include "Root.hpp"

Root* Ogre::Singleton<Root>::msSingleton = nullptr;

bool Root::frameStarted(const Ogre::FrameEvent& evt)
{
	std::cout << app->getContext()->getRenderWindow()->getStatistics().avgFPS << " FPS" << std::endl;

	/*
	TODO: Show FPS on window title.

	std::stringstream ss;
	ss << renderWindow->getStatistics().avgFPS << " FPS";
	size_t windowHnd = 0;
	renderWindow->getCustomAttribute("WINDOW", &windowHnd);
	SetWindowTextA((HWND)windowHnd, ss.str().c_str());
	*/

	for (std::vector<Object*>::const_iterator i = objects.begin(); i != objects.end(); ++i)
	{
		(*i)->update(evt.timeSinceLastFrame);
	}

	tree->build();

	return render;
}

bool Root::keyPressed(const OIS::KeyEvent& arg)
{
	if (arg.key == OIS::KC_M)
	{
		moveObjects = !moveObjects;
	}

	return true;
}

bool Root::keyReleased(const OIS::KeyEvent& arg)
{
	return true;
}

void Root::run()
{
	app = std::make_shared<Gecko::App>();
	input = std::make_shared<Gecko::Input>(app->getRenderWindowHandle());

	Ogre::Root* root = app->getContext()->getRoot();
	root->addFrameListener(this);

	if (root->restoreConfig() || root->showConfigDialog(OgreBites::getNativeConfigDialog()))
	{
		std::shared_ptr<Gecko::Scene> scene = std::make_shared<Gecko::Scene>(app->getRoot());
		std::shared_ptr<Gecko::Light> light = std::make_shared<Gecko::Light>(scene, "Light");
		std::shared_ptr<Gecko::Camera> camera = std::make_shared<Gecko::Camera>(scene, "Camera");

		sceneManager = scene->getSceneManager();

		Ogre::Vector3 size(10000.0f, 2000.0f, 10000.0f);

		Map* map = new Map("Map", size);


		camera->setPosition(Ogre::Vector3f(size.x / 2.0f, size.y * 4.0f, size.z * 1.2f));
		camera->lookAt(Ogre::Vector3(size.x / 2.0f, 0.0f, size.z / 2.0f));
		camera->setSpeed(1000.0f);

		std::srand(static_cast<unsigned int>(time(nullptr)));

		Collision::Solver* solver = new Collision::Solver();


		// tree = new Collision::NoTree();
		// tree = new Collision::Grid();
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

			objects.push_back(new Object(ss.str(), meshes[rand() % meshCount], map));
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

		app->setCamera(camera);
		app->run();

		for (std::vector<Object*>::const_iterator i = objects.begin(); i != objects.end(); ++i)
		{
			delete (*i);
		}

		delete tree;
		delete solver;
	}

	// viewport = renderWindow->addViewport(camera);
	// viewport->setBackgroundColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f, 1.0f));

	// root->addFrameListener(this);

	// Gecko::App::getSingleton().setCamera(camera);
	// app->getContext()->addInputListener(keyHandler.get());

	/*
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
	*/

	/*
	Ogre::Vector3 size(10000.0f, 2000.0f, 10000.0f);

	Map* map = new Map("Map", size);

	cameraNode->setPosition(size.x / 2.0f, size.y * 4.0f, size.z * 1.2f);
	cameraNode->lookAt(Ogre::Vector3(size.x / 2.0f, 0.0f, size.z / 2.0f), Ogre::Node::TransformSpace::TS_WORLD);


	srand((unsigned int)time(nullptr));


	Collision::Solver* solver = new Collision::Solver();


	// tree = new Collision::NoTree();
	// tree = new Collision::Grid();
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
		// map->createGrid(grid);
	}
	else if (octree)
	{
		// map->createOctree(octree);
	}

	Gecko::App::getSingleton().run();
	// root->startRendering();

	for (std::vector<App::Object*>::const_iterator i = objects.begin(); i != objects.end(); ++i)
	{
		delete (*i);
	}

	delete tree;
	delete solver;
	*/
}
