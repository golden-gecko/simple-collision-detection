#pragma once

#include "PCH.hpp"

#include "Collision/Grid.hpp"
#include "Collision/Octree.hpp"

#include "Gecko/App.hpp"
#include "Gecko/Input.hpp"

#include "Object.hpp"

class Root : public Ogre::Singleton<Root>, public Ogre::FrameListener, public OIS::KeyListener
{
public:
	// Ogre::FrameListener
	bool frameStarted(const Ogre::FrameEvent& evt) override;

	// OIS::KeyListener
	bool keyPressed(const OIS::KeyEvent& arg) override;
	bool keyReleased(const OIS::KeyEvent& arg) override;

public:
    void run();

	Ogre::Entity* createEntity(const std::string& name, const std::string& mesh) const
	{
		return sceneManager->createEntity(name, mesh);
	}

	void destroyEntity(Ogre::Entity* entity) const
	{
		sceneManager->destroyEntity(entity);
	}

	Ogre::ManualObject* createManual(const std::string& name) const
	{
		return sceneManager->createManualObject(name);
	}

	void destroyManual(Ogre::ManualObject* manual) const
	{
		sceneManager->destroyManualObject(manual);
	}

	Ogre::SceneNode* createSceneNode() const
	{
		return sceneManager->getRootSceneNode()->createChildSceneNode();
	}

	void destroySceneNode(Ogre::SceneNode* sceneNode) const
	{
		sceneManager->destroySceneNode(sceneNode);
	}

	Ogre::SceneManager* getSceneManager() const
	{
		return sceneManager;
	}

	Collision::Tree* getTree() const
	{
		return tree;
	}

	bool getMoveObjects() const
	{
		return moveObjects;
	}

	void setMoveObjects(bool moveObjects)
	{
		this->moveObjects = moveObjects;
	}
protected:
	std::shared_ptr<Gecko::App> app;
	std::shared_ptr<Gecko::Input> input;

	Ogre::SceneManager* sceneManager = nullptr;

	bool render = true;
	bool moveObjects = true;

	std::vector<Object*> objects;

	Collision::Tree* tree = nullptr;
    Collision::Grid* grid = nullptr;
    Collision::Octree* octree = nullptr;
};
