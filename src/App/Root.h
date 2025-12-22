#pragma once

#include "StdAfx.h"

#include "Collision\Grid.h"
#include "Collision\Octree.h"

#include "App\Object.h"

namespace Gecko
{
    class Camera
    {
    public:
        Camera(Ogre::SceneManager* sceneManager, const std::string& name) : sceneManager(sceneManager)
        {
            camera = sceneManager->createCamera(name);
            camera->setNearClipDistance(5.0f);
            camera->setAutoAspectRatio(true);

            sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
            sceneNode->setPosition(0.0f, 0.0f, 15.0f);
            sceneNode->lookAt(Ogre::Vector3(0.0f, 0.0f, -1.0f), Ogre::Node::TS_PARENT);
            sceneNode->attachObject(camera);
        }

        ~Camera()
        {
            sceneManager->destroySceneNode(sceneNode);
            sceneManager->destroyCamera(camera);
        }

        Ogre::Camera* getCamera() const
        {
            return camera;
        }

    protected:
        Ogre::SceneManager* sceneManager;
        Ogre::Camera* camera;
        Ogre::SceneNode* sceneNode;
    };

    class GameObject
    {
    public:
        GameObject(Ogre::SceneManager* sceneManager, const std::string& name) : sceneManager(sceneManager)
        {
            entity = sceneManager->createEntity(name);

            sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
            sceneNode->attachObject(entity);
        }

        ~GameObject()
        {
            sceneManager->destroySceneNode(sceneNode);
            sceneManager->destroyEntity(entity);
        }

    protected:
        Ogre::SceneManager* sceneManager;
        Ogre::Entity* entity;
        Ogre::SceneNode* sceneNode;
    };

    class KeyHandler : public OgreBites::InputListener
    {
    private:
        bool keyPressed(const OgreBites::KeyboardEvent& evt) override
        {
            if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
            {
                Ogre::Root::getSingleton().queueEndRendering();
            }

            return true;
        }
    };

    class Light
    {
    public:
        Light(Ogre::SceneManager* sceneManager, const std::string& name) : sceneManager(sceneManager)
        {
            light = sceneManager->createLight(name);
            light->setCastShadows(false);
            light->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);

            sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
            sceneNode->attachObject(light);
            sceneNode->lookAt(Ogre::Vector3f(-1.0f, -1.0f, -1.0f), Ogre::Node::TransformSpace::TS_PARENT);
        }

        ~Light()
        {
            sceneManager->destroySceneNode(sceneNode);
            sceneManager->destroyLight(light);
        }

    protected:
        Ogre::SceneManager* sceneManager;
        Ogre::Light* light;
        Ogre::SceneNode* sceneNode;
    };

    class App : public Ogre::Singleton<App>
    {
    public:
        App()
        {
            ctx = std::make_shared<OgreBites::ApplicationContext>("OgreTutorialApp");
            ctx->initApp();
        }

        ~App()
        {
            ctx->closeApp();
        }

        void run()
        {
            ctx->getRoot()->startRendering();
        }

        std::shared_ptr<OgreBites::ApplicationContext> getContext() const
        {
            return ctx;
        }

        void setCamera(Ogre::Camera* camera)
        {
            ctx->getRenderWindow()->addViewport(camera)->setBackgroundColour(Ogre::ColourValue::White);
        }

    protected:
        std::shared_ptr<OgreBites::ApplicationContext> ctx;
    };
}

namespace App
{
	class Root : public Ogre::Singleton<Root>, Ogre::FrameListener, OgreBites::InputListener
	{
	public:
		Root();

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

		virtual bool frameStarted(const Ogre::FrameEvent& evt);

		virtual void windowClosed(Ogre::RenderWindow* rw)
		{
			render = false;
		}

		bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

		bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override;

		Ogre::SceneManager* getSceneManager() const
		{
			return sceneManager;
		}

		Collision::Tree* getTree() const {
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
		std::shared_ptr<Gecko::App> gecko;

		Ogre::Root* root;
		Ogre::RenderWindow* renderWindow;
		Ogre::SceneManager* sceneManager;
		Ogre::Camera* camera;
		Ogre::SceneNode* cameraNode;
		Ogre::Viewport* viewport;

		bool render;
		bool moveObjects;

		std::vector<Object*> objects;

		Collision::Tree* tree;
        Collision::Grid* grid;
        Collision::Octree* octree;
	};
}
