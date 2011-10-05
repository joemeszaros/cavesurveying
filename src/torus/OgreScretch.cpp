#include "OgreScretch.h"
#include "util/util.h"
#include "util/meshutil.h"
#include "importers.h"
#include "exporters.h"
#include "graph.h"

#include <OgreException.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h> 
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <OgreVector3.h>
#include <OgreSubMesh.h>
#include "hull.cpp"

//-------------------------------------------------------------------------------------
OgreScretch::OgreScretch(void) : mRoot(0),    mPluginsCfg(Ogre::StringUtil::BLANK),mResourcesCfg(Ogre::StringUtil::BLANK),mCamera(0)
{
}
//-------------------------------------------------------------------------------------
OgreScretch::~OgreScretch(void)
{
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
	delete mRoot;
	Ogre::String;
}

bool OgreScretch::go(void)
{

#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif

	mRoot = new Ogre::Root(mPluginsCfg);
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);
	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}

	if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	{
		return false;
	}

	mWindow = mRoot->initialise(true, "3D Speleo View");

	// Set default mipmap level (NB some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	// initialise all resource groups
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager");

	// Create the camera
	mCamera = mSceneMgr->createCamera("PlayerCam");

	// Position it at 500 in Z direction
	mCamera->setPosition(Ogre::Vector3(0,0,80));
	// Look back along -Z
	mCamera->lookAt(Ogre::Vector3(0,0,-300));
	mCamera->setNearClipDistance(1);
	// Create one viewport, entire window
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));


    createScene();

    createFrameListener();

	//mRoot->startRendering();

	DWORD elapsedTicks = GetTickCount() - tickAtStart;
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Elapsed time in ms:  ***");
	Ogre::LogManager::getSingletonPtr()->logMessage(myutil::StringUtil::ToString(elapsedTicks));
	
while(true)
{
    // Pump window messages for nice behaviour
    Ogre::WindowEventUtilities::messagePump();
 
    if(mWindow->isClosed())
    {
        return false;
    }
 
    // Render a frame
    if(!mRoot->renderOneFrame()) return false;
	Sleep(10);
}

	return true;
}


void OgreScretch::createScene() {

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));

		
/*    headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("ogrehead", "ogrehead.mesh");
    headNode->attachObject(ogreHead); */

	Passage p;
	p.load("d:\\tmp\\cave.xml");


		MaterialPtr material = MaterialManager::getSingleton().create(
      "Test2/ColourTest", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::Pass* pass =  material->getTechnique(0)->getPass(0);
	pass->setAmbient( 1,0.3, 0.588235);
	pass->setDiffuse(1, 1, 0.588235,1);
	pass->setCullingMode(Ogre::CullingMode::CULL_ANTICLOCKWISE);
	pass->setLightingEnabled(true);
	pass->setManualCullingMode(Ogre::ManualCullingMode::MANUAL_CULL_BACK);
	pass->setPointSize(4.5);
	

	parentnode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	parentnode->setPosition(0,0,-30);
	ManualObject* manual = MeshUtil::createManual(mSceneMgr,"mykocka","BaseWhiteNoLighting",p,Ogre::ColourValue(1,0,0,1),Ogre::RenderOperation::OT_LINE_LIST);
	passagenode = parentnode->createChildSceneNode();
	passagenode->attachObject(manual);

	Hull hull;
	ManualObject* manualhelper = hull.createHull(p, mSceneMgr);
	helpernode = parentnode->createChildSceneNode();
	MeshPtr generatedmesh =  manualhelper->convertToMesh("convertedmesh");
	//helpernode->attachObject(manualhelper);
	Entity* ent =  mSceneMgr->createEntity("cmesh","convertedmesh");
	

	helpernode->attachObject(ent);

	
	parentnode->scale(10,10,10);
	//helpernode->scale(10,10,10);
	

	Ogre::Light *light = mSceneMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_POINT);
	light->setPosition(Ogre::Vector3(250, 150, 250));
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue::White);

}


void OgreScretch::createFrameListener(void){


	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem( pl );

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);


	// Populate the camera container
	mCamNode = mCamera->getParentSceneNode();

	// set the rotation and move speed
	mRotate = 0.13;
	mMove = 250;

	mDirection = Ogre::Vector3::ZERO;

}


void OgreScretch::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void OgreScretch::windowClosed(Ogre::RenderWindow* rw)
{
	//Only close for window that created OIS (the main window in these demos)
	if( rw == mWindow )
	{
		if( mInputManager )
		{
			mInputManager->destroyInputObject( mMouse );
			mInputManager->destroyInputObject( mKeyboard );

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}

bool OgreScretch::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(mWindow->isClosed())
		return false;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		return false;
	//mCamNode->translate(mDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	return true;
}


bool OgreScretch::keyPressed( const OIS::KeyEvent &arg ){
	switch (arg.key)
	{
	case OIS::KC_1:
		mCamera->getParentSceneNode()->detachObject(mCamera);
		mCamNode = mSceneMgr->getSceneNode("CamNode1");
		mCamNode->attachObject(mCamera);
		break;

	case OIS::KC_2:
		mCamera->getParentSceneNode()->detachObject(mCamera);
		mCamNode = mSceneMgr->getSceneNode("CamNode2");
		mCamNode->attachObject(mCamera);
		break;
	case OIS::KC_UP:
	case OIS::KC_W:
		parentnode->scale(1.2,1.2,1.2);
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		parentnode->scale(0.8,0.8,0.8);
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		mDirection.x = -mMove;
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		mDirection.x = mMove;
		break;

	case OIS::KC_PGDOWN:
	case OIS::KC_E:
		mDirection.y = -mMove;
		break;

	case OIS::KC_PGUP:
	case OIS::KC_Q:
		mDirection.y = mMove;
		break;

	case OIS::KC_ESCAPE: 
		mShutDown = true;
		break;
	case OIS::KC_R :
		
        Ogre::PolygonMode pm;

        switch (mCamera->getPolygonMode())
        {
		case Ogre::PM_SOLID:
			pm = Ogre::PM_WIREFRAME;
            break;
        case Ogre::PM_WIREFRAME:
            pm = Ogre::PM_POINTS;
            break;
        default:
            pm = Ogre::PM_SOLID;
			break;
        }

        mCamera->setPolygonMode(pm);
       
		
		break;
	default:
		break;
	}
	return true;
}

bool OgreScretch::keyReleased( const OIS::KeyEvent &arg ){

	switch (arg.key)
	{
	case OIS::KC_UP:
	case OIS::KC_W:
		mDirection.z = 0;
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		mDirection.z = 0;
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		mDirection.x = 0;
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		mDirection.x = 0;
		break;

	case OIS::KC_PGDOWN:
	case OIS::KC_E:
		mDirection.y = 0;
		break;

	case OIS::KC_PGUP:
	case OIS::KC_Q:
		mDirection.y = 0;
		break;

	default:
		break;
	}
	return true;
}

bool OgreScretch::mouseMoved( const OIS::MouseEvent &arg) {
	if (arg.state.buttonDown(OIS::MB_Right))
	{
		parentnode->rotate(Ogre::Vector3(arg.state.Y.rel,arg.state.X.rel,0),Ogre::Degree(5), Ogre::Node::TS_WORLD);
	}
	return true;
}
bool OgreScretch::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
	Ogre::Light *light = mSceneMgr->getLight("Light1");
	switch (id)
	{
	case OIS::MB_Left:
		light->setVisible(! light->isVisible());
		break;
	default:
		break;
	}
	return true;
}

bool OgreScretch::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){return true;}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
	int main2(int argc, char *argv[])
#endif
	{
		// Create application object
		OgreScretch app;


		try {
			app.tickAtStart = GetTickCount();
			app.go();
		} catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif