#include "OgreScretch.h"
#include "util/util.h"
#include "util/meshutil.h"
#include "importers.h"
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
#include "ogre/movabletext.h"

//-------------------------------------------------------------------------------------
OgreScretch::OgreScretch(void) : mRoot(0),    mPluginsCfg(Ogre::StringUtil::BLANK),mResourcesCfg(Ogre::StringUtil::BLANK),mCamera(0),alpha(1.0),alphadiff(0.1),passageVisible(false),polygonVisible(true), hullVisible(false),shotVisible(false),planeVisible(false),mCameraMan(0),hullLimit(300), headVisible(true)
{
	mRotate = 0.13;	
	mMove = 250;
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
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
	// Create one viewport, entire window
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0.4,0.4,0.4));

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));


    createScene();

    createFrameListener();

	//mRoot->startRendering();

	long elapsedTicks = GetTickCount() - tickAtStart;
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Elapsed time in ms:  ***");
	Ogre::LogManager::getSingletonPtr()->logMessage(util::String::ToString(elapsedTicks));
	
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
	
	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
	CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
	CEGUI::MouseCursor::getSingleton().setImage( CEGUI::System::getSingleton().getDefaultMouseCursor());

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));

		
/*    headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("ogrehead", "ogrehead.mesh");
    headNode->attachObject(ogreHead); */


	

	parentnode = mSceneMgr->getRootSceneNode()->createChildSceneNode("parentNode");

	
	MaterialPtr material = MaterialManager::getSingleton().create(
      "Test2/ColourTest", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::Pass* pass =  material->getTechnique(0)->getPass(0);
	pass->setAmbient( 139/255.0f,71/255.0f, 38/255.0f);
	pass->setDiffuse(139/255.0f, 71/255.0f, 38/255.0f,1);
	
	pass->setCullingMode(Ogre::CullingMode::CULL_NONE);
	pass->setLightingEnabled(true);
	pass->setManualCullingMode(Ogre::ManualCullingMode::MANUAL_CULL_NONE);
	pass->setPointSize(2.5);
	//pass->setShadingMode(Ogre::ShadeOptions::SO_GOURAUD);
	

	regenerate();

/*
	Passage p;
	p.load("d:\\tmp\\cave.xml");


	ManualObject* manual = util::Mesh::createManual(mSceneMgr,"mykocka","BaseWhiteNoLighting",p,Ogre::ColourValue(1,0,0,1),Ogre::RenderOperation::OT_LINE_LIST);
	passagenode = parentnode->createChildSceneNode();
	passagenode->attachObject(manual);
	passagenode->translate(-util::Mesh::getPivotPoint(p));

	Hull hull;
	ManualObject* manualhelper = hull.createHull(p, mSceneMgr);
	helpernode = parentnode->createChildSceneNode();
	MeshPtr generatedmesh =  manualhelper->convertToMesh("convertedmesh");
	//helpernode->attachObject(manualhelper);
	Entity* ent =  mSceneMgr->createEntity("cmesh","convertedmesh");
	

	helpernode->attachObject(ent);
	helpernode->translate(-util::Mesh::getPivotPoint(p));

	
	parentnode->scale(10,10,10);
	//helpernode->scale(10,10,10);
	
	SceneNode* sphereNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	 util::Mesh::createSphere("mySphereMesh2", 1.3, 20, 20);
	 Entity* sphereEntity2 = mSceneMgr->createEntity("mySphereEntity2", "mySphereMesh2");
	 sphereEntity2->setMaterialName("Test2/Cave");
	 sphereNode2->attachObject(sphereEntity2);
	 sphereNode2->setPosition(-util::Mesh::getPivotPoint(p));
	 
*/
	
	/*MovableText* msg = new MovableText("TXT_001", "this is the caption","StarWars",1.0,Ogre::ColourValue::Red);
	msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); // Center horizontally and display above the node
	captionNode =  parentnode->createChildSceneNode();
	captionNode->attachObject(msg);
	captionNode->scale(0.4,0.4,0.4);*/

	Ogre::Light *light = mSceneMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_POINT);
	light->setPosition(Ogre::Vector3(250, 150, 250));
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue::White);

	lightmove = mSceneMgr->createLight("LightMove");
	lightmove->setType(Ogre::Light::LT_SPOTLIGHT);
	lightmove->setDiffuseColour(Ogre::ColourValue::White);
	lightmove->setSpecularColour(Ogre::ColourValue::White);

	



}

void OgreScretch::regenerate(void) {

	
	
	stdext::hash_map<const Ogre::String, Ogre::Vector3> vertexliststr;
	std::vector<Index2Str> indicesstr;

	Ogre::ConfigFile mainconfig;
	mainconfig.load("global.conf");
	Ogre::String filename = mainconfig.getSetting("path");

	//formats::Polygon::import("G:\\cavesurveying\\data\\\Pocsakoi.cave",vertexliststr,indicesstr);
	formats::Therion::import(filename,vertexliststr,indicesstr);
	
	Passage p = formats::Therion::toPassage(vertexliststr, indicesstr);
	//orderSourcePoints(p);

	Vector pivotpoint = -util::Mesh::getPivotPoint(p);

	mSceneMgr->destroyManualObject("polygonmodel");
	ManualObject* manualShot = util::Mesh::createManual(mSceneMgr,"polygonmodel","BaseWhiteNoLighting",vertexliststr,indicesstr,Ogre::ColourValue(1,0,0,1),Ogre::RenderOperation::OT_LINE_LIST);
	shotNode = parentnode->createChildSceneNode();
	shotNode->attachObject(manualShot);
	shotNode->translate(-util::Mesh::getPivotPoint(vertexliststr)); 
	shotNode->setVisible(shotVisible);
	
	
	mSceneMgr->destroyManualObject("hull");
	Hull hull;
	hull.limit = hullLimit;
	ManualObject* manualHull = 0;
	manualHull = hull.createHull(p, mSceneMgr,"hull","Cave/Brown");
	hullNode = parentnode->createChildSceneNode();

	//MeshSerializer ser;
	//ser.exportMesh(generatedmesh.getPointer(), "nyomocso.mesh" );
	
	hullNode->attachObject(manualHull);
	hullNode->setVisible(hullVisible);
	hullNode->translate(pivotpoint.toOgreVector());
	
	
	///Vector pivotpoint = -util::Mesh::getPivotPoint(p);
	mSceneMgr->destroyManualObject("manualshot");
	ManualObject* manualPolygon= util::Mesh::createManual(mSceneMgr,"manualshot","BaseWhiteNoLighting",p,Ogre::ColourValue(1,0,0,1),Ogre::RenderOperation::OT_LINE_LIST, true, false);
	polygonNode = parentnode->createChildSceneNode();
	polygonNode->attachObject(manualPolygon);
	polygonNode->translate(pivotpoint.toOgreVector());
	polygonNode->setVisible(polygonVisible);

	mSceneMgr->destroyManualObject("manualslices");
	ManualObject* manualPassage = util::Mesh::createManual(mSceneMgr,"manualslices","BaseWhiteNoLighting",p,Ogre::ColourValue(1,0,0,1),Ogre::RenderOperation::OT_LINE_LIST, false, true);
	passageNode = parentnode->createChildSceneNode();
	passageNode->attachObject(manualPassage);
	passageNode->translate(pivotpoint.toOgreVector());
	passageNode->setVisible(passageVisible);

	/*
	int round = 0;
	headNodes = parentnode->createChildSceneNode();
	for(std::vector<SourcePoint>::iterator it = p.points.begin(); it != p.points.end(); ++it) {
		int cnt = 0;
		for (std::vector<EndPoint>::iterator it2 = it->points.begin(); it2 != it->points.end(); ++it2) {
			std::stringstream ss;
			ss << "head" << round << "_id" << cnt; 
			Ogre::Entity* ogreHead = mSceneMgr->createEntity(ss.str(), "ogrehead.mesh");
			Ogre::SceneNode* headNode = headNodes->createChildSceneNode();
			headNode->attachObject(ogreHead);
			double v = 0.0004*cnt/2;
			headNode->scale(v,v,v);
			headNode->translate(Ogre::Vector3(it2->x, it2->y, it2->z));
			cnt++;
		}
		round++;
	}
	headNodes->translate(pivotpoint.toOgreVector());
	*/
	
/*	planesNode = parentnode->createChildSceneNode();
		int id = 0;
	int cnt = 0;
	simplex::Plane myplane = hull.getPlane();
		double* params = myplane.getParameters();
		Ogre::Vector3 pn = myplane.normal.toOgreVector();
		double ddist = myplane.distanceFromOrigo();
		Ogre::Plane plane(pn , ddist);
		
//		Ogre::Plane plane(params[0],params[1], params[2], params[3]);
		std::stringstream ss;
		ss << "ground";
		ss << id++;
		std::stringstream ss2;
		ss2 <<  "groundentinty" << id;
		Ogre::String groundname;
		ss >> groundname;
		Ogre::String groundentname;
		ss2 >> groundentname;
		mSceneMgr->destroyEntity(groundentname);
		Ogre::MeshManager::getSingleton().createPlane(groundname , Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,    plane, 2, 2, 10, 10, true, 1, 5, 5, myplane.getUpVector().toOgreVector());
		Ogre::Entity* entGround = mSceneMgr->createEntity(groundentname , groundname);
		SceneNode * node = planesNode->createChildSceneNode();
		node->attachObject(entGround);
		//node->translate(it->toOgreVector());
		entGround->setMaterialName("Test2/ColourTest");
		entGround->setCastShadows(false);
		planesNode->translate(pivotpoint.toOgreVector());
		planesNode->setVisible(planeVisible);

*/		//parentnode->scale(13.0,13.0,13.0);
		parentnode->scale(10.0,10.0,10.0);

/*
	simplex::Plane* planes = util::Mesh::createBestFitPlanes(p);

	planesNode = parentnode->createChildSceneNode();
	int id = 0;
	int cnt = 0;
	int size = p.points.size();
	for(std::vector<SourcePoint>::iterator it = p.points.begin(); it != p.points.end(); ++it) {
		simplex::Plane p = planes[cnt++];
		double* params = p.getParameters();
		Ogre::Plane plane(p.normal.toOgreVector(),p.distanceFromOrigo());
//		Ogre::Plane plane(params[0],params[1], params[2], params[3]);
		std::stringstream ss;
		ss << "ground";
		ss << id++;
		std::stringstream ss2;
		ss2 <<  "groundentinty" << id;
		Ogre::String groundname;
		ss >> groundname;
		Ogre::String groundentname;
		ss2 >> groundentname;
		mSceneMgr->destroyEntity(groundentname);
		Ogre::MeshManager::getSingleton().createPlane(groundname , Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,    plane, 10, 10, 10, 10, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
		Ogre::Entity* entGround = mSceneMgr->createEntity(groundentname , groundname);
		SceneNode * node = planesNode->createChildSceneNode();
		node->attachObject(entGround);
		//node->translate(it->toOgreVector());
		entGround->setMaterialName("Test2/ColourTest");
		entGround->setCastShadows(false);
	}

	planesNode->translate(pivotpoint.toOgreVector());
	planesNode->setVisible(planeVisible);*/


}

void  OgreScretch::orderSourcePoints(Passage p) {
		std::vector<SourcePoint> copy;
		
		for (std::vector<SourcePoint>::iterator it = p.points.begin(); it != p.points.end();++it) {
			copy.push_back(*it);
		}

		p.points.clear();
		for (std::vector<SourcePoint>::iterator it =copy.begin(); it != copy.end();++it) {
			simplex::Plane plane = util::Math::getBestFittingPlane(*it);
			p.points.push_back(util::Math::orderEndPoints(*it, plane));
		}


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
	mCamNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

		//mCamNode = mSceneMgr->getSceneNode("CamNode1");
		mCamNode->attachObject(mCamera);
	// set the rotation and move speed
	mRotate = 0.13;
	mMove = 30;

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


	if (mCamNode && mDirection.length() > 0) {
		Ogre::Vector3 dir(0,0,0);
		if (mDirection.z < 0) {
			dir = mCamera->getDirection() * 15;
		} else {
			dir = -mCamera->getDirection() * 15;
		}

		if (mDirection.x > 0) {//left 
			dir = mCamera->getRight()*15;
		} else if (mDirection.x < 0) {
			dir = -mCamera->getRight()*15;
		}
		mCamNode->translate(dir * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
		lightmove->setDirection(mCamera->getDirection());
		lightmove->setPosition(mCamNode->getPosition());
		
		
	}
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		return false;
	//mCamNode->translate(mDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	return true;
}


bool OgreScretch::keyPressed( const OIS::KeyEvent &arg ){
	Ogre::Light *light = mSceneMgr->getLight("Light1");

	switch (arg.key)
	{
		case OIS::KC_UP:
		case OIS::KC_W:
			mDirection.z = -mMove;
			break;
		 
		case OIS::KC_DOWN:
		case OIS::KC_S:
			mDirection.z = mMove;
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

	case OIS::KC_1:
		mCamera->getParentSceneNode()->detachObject(mCamera);
		mCamNode = mSceneMgr->getSceneNode("CamNode1");
		mCamNode->attachObject(mCamera);
		break;
	case OIS::KC_ESCAPE: 
		mShutDown = true;
		break;

	case OIS::KC_B :
			if (alpha-alphadiff >= 0) {
				alpha -= alphadiff;
				MaterialPtr mod = MaterialManager::getSingleton().getByName("Test2/ColourTest");
				mod->setDiffuse(139/255.0f, 71/255.0f, 38/255.0f,alpha);
			}
			
		break;
	case OIS::KC_Z:
		headVisible = !headVisible;
		headNodes->setVisible(headVisible);
		break;
	case OIS::KC_U:
		planeVisible = ! planeVisible;
		planesNode->setVisible(planeVisible);
		break;
	case OIS::KC_H :
		hullVisible = !hullVisible;
		hullNode->setVisible(hullVisible);
		break;
	case OIS::KC_P :
		polygonVisible = !polygonVisible;
		polygonNode->setVisible(polygonVisible);
		break;
	case OIS::KC_I :
		passageVisible = !passageVisible;
		passageNode->setVisible(passageVisible);
		break;
	case OIS::KC_O:
		shotVisible = !shotVisible;
		shotNode->setVisible(shotVisible);
		break;
	case OIS::KC_R:
		hullLimit++;
		regenerate();
		break;
	case OIS::KC_T:
		hullLimit = 0;
		break;
	case OIS::KC_L :
		
		light->setVisible(! light->isVisible());
		break;
	case OIS::KC_K :
		lightmove->setVisible(! light->isVisible());
		break;
	case OIS::KC_M :
		
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
	}

	mCameraMan->injectKeyDown(arg);
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
		 
		}
	CEGUI::System::getSingleton().injectKeyUp(arg.key);
	mCameraMan->injectKeyUp(arg);
	return true;
}


CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
 
    default:
        return CEGUI::LeftButton;
    }
}

bool OgreScretch::mouseMoved( const OIS::MouseEvent &arg) {

	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
	// Scroll wheel.
	if (arg.state.Z.rel)
		sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);

	if (arg.state.buttonDown(OIS::MB_Right))
	{
		parentnode->rotate(Ogre::Vector3(arg.state.Y.rel,arg.state.X.rel,0),Ogre::Degree(5), Ogre::Node::TS_WORLD);
		//captionNode->rotate(Ogre::Vector3(arg.state.Y.rel,arg.state.X.rel,0),Ogre::Degree(5), Ogre::Node::TS_LOCAL);
	}
	 mCameraMan->injectMouseMove(arg);
	return true;
}
bool OgreScretch::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
	CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
	mCameraMan->injectMouseDown(arg, id);
	return true;

}

bool OgreScretch::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
	CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
	mCameraMan->injectMouseUp(arg, id);
	return true;

}



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
		/*OutputDebugString("------------------------------------\n");
		Vector v1(0,1,0);
		Vector v2(-0.6,-0.3,0);
		float angle = util::Math::getAngle(v1,v2)*(180/3.1415);

*/
		//OutputDebugString(s);
		OutputDebugString("------------------------------------\n");
		



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