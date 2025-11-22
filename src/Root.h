#pragma once

#include "StdAfx.h"

#include "GameObject.h"

namespace Collision
{
	class Root : public Ogre::Singleton<Root>, Ogre::FrameListener, Ogre::WindowEventListener,
		OIS::KeyListener, OIS::MouseListener, OIS::JoyStickListener
	{
	public:
		Root();

		Ogre::Entity* createEntity(const std::string& name, const std::string& mesh) const
		{
			return sceneManager->createEntity(name, mesh);
		}

		Ogre::SceneNode* createSceneNode() const
		{
			return sceneManager->getRootSceneNode()->createChildSceneNode();
		}

		virtual bool frameStarted(const Ogre::FrameEvent& evt);

		virtual void windowClosed(Ogre::RenderWindow* rw)
		{
			render = false;
		}

		virtual bool keyPressed(const OIS::KeyEvent& arg)
		{
			return true;
		}

		virtual bool keyReleased(const OIS::KeyEvent& arg)
		{
			return true;
		}

		virtual bool mouseMoved(const OIS::MouseEvent& arg)
		{
			return true;
		}

		virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
		{
			return true;
		}

		virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
		{
			return true;
		}

		virtual bool buttonPressed(const OIS::JoyStickEvent& arg, int button)
		{
			return true;
		}

		virtual bool buttonReleased(const OIS::JoyStickEvent& arg, int button) 
		{
			return true;
		}

		virtual bool axisMoved(const OIS::JoyStickEvent& arg, int axis)
		{
			return true;
		}

	private:
		Ogre::Root* root;
		Ogre::RenderWindow* renderWindow;
		Ogre::SceneManager* sceneManager;
		Ogre::Camera* camera;
		Ogre::Viewport* viewport;

		OIS::InputManager* inputManager;
		OIS::Keyboard* keyboard;
		OIS::Mouse* mouse;

		bool render;

		std::vector<GameObject*> objects;
	};
}
