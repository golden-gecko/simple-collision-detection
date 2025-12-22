#include "StdAfx.h"

#include "App\Root.h"

int main()
{
	/*
	std::unique_ptr<Gecko::App> app = std::make_unique<Gecko::App>();

	Ogre::Root* root = app->getContext()->getRoot();
	Ogre::SceneManager* sceneManager = root->createSceneManager();

	Ogre::RTShader::ShaderGenerator::getSingletonPtr()->addSceneManager(sceneManager);

	std::shared_ptr light = std::make_shared<Gecko::Light>(sceneManager, "MainLight");
	std::shared_ptr camera = std::make_shared<Gecko::Camera>(sceneManager, "Camera");
	std::shared_ptr gameObject = std::make_shared<Gecko::GameObject>(sceneManager, "robot.mesh");
	std::shared_ptr keyHandler = std::make_shared<Gecko::KeyHandler>();

	app->setCamera(camera->getCamera());
	app->getContext()->addInputListener(keyHandler.get());
	app->run();
	//*/

	std::unique_ptr<App::Root> appRoot = std::make_unique<App::Root>();

	appRoot->run();

	return 0;
}

/*

	class AABB : public Object
	{
	};

	class OBB : public Object
	{
	};

	class Tree
	{
	};

	class SphereTree : public Tree
	{
	};

	class Octree : public Tree
	{
	};

*/
