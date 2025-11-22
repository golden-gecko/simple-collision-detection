#include "StdAfx.h"

namespace Collision
{
	class Root : public Ogre::Root, Ogre::FrameListener, Ogre::WindowEventListener,
		OIS::KeyListener, OIS::MouseListener, OIS::JoyStickListener
	{
	public:
		Root() : render(true)
		{
			if (restoreConfig() || showConfigDialog())
			{
				renderWindow = initialise(true);
				sceneManager = createSceneManager(Ogre::ST_GENERIC);
				camera = sceneManager->createCamera("Camera");
				viewport = renderWindow->addViewport(camera);

				sceneManager->setWorldGeometry("Terrain.cfg");

				Root::addFrameListener(this);
				Ogre::WindowEventUtilities::addWindowEventListener(renderWindow, this);

				OIS::ParamList pl;
				size_t windowHnd = 0;
				std::ostringstream windowHndStr;
				renderWindow->getCustomAttribute("WINDOW", &windowHnd);
				windowHndStr << windowHnd;
				pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
				
				inputManager = OIS::InputManager::createInputSystem(pl);
				keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
				mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));

				keyboard->setEventCallback(this);
				mouse->setEventCallback(this);

				startRendering();
			}
		}

		virtual bool frameStarted(const Ogre::FrameEvent& evt)
		{
			keyboard->capture();
			mouse->capture();

			if (keyboard->isKeyDown(OIS::KC_ESCAPE))
			{
				render = false;
			}

			return render;
		}

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
		Ogre::RenderWindow* renderWindow;
		Ogre::SceneManager* sceneManager;
		Ogre::Camera* camera;
		Ogre::Viewport* viewport;

		OIS::InputManager* inputManager;
		OIS::Keyboard* keyboard;
		OIS::Mouse* mouse;

		bool render;
	};
}

int main()
{
	Collision::Root* root = new Collision::Root();

	delete root;

	return 0;
}
