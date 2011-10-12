#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreWindowEventUtilities.h>
#include <OgreMaterialManager.h>
#include <OgreMaterial.h>
#include <OgreMeshSerializer.h>
#include <OgreMaterialSerializer.h>
#include <OgreImage.h>
#include <OgreTexture.h>
#include <OgreTextureManager.h>
#include <OgreManualObject.h>


#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

using namespace Ogre;

class OgreScretch : public Ogre::WindowEventListener, public Ogre::FrameListener
	, public OIS::KeyListener, public OIS::MouseListener
{
public:
    OgreScretch(void);
    virtual ~OgreScretch(void);
    bool go(void);

	DWORD tickAtStart;
	DWORD tickAtEnd;
private:
    Ogre::Root* mRoot;
    Ogre::String mPluginsCfg;
	Ogre::String mResourcesCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;

protected:
	void getMeshInformation(const Ogre::Mesh* const mesh,
                        size_t &vertex_count,
                        Ogre::Vector3* &veVector3rtices,
                        size_t &index_count,
                        unsigned long* &indices,
                        const Ogre::Vector3 &position  = Ogre::Vector3::ZERO,
                        const Ogre::Quaternion &orient = Ogre::Quaternion::IDENTITY,
						const Ogre::Vector3 &scale = Ogre::Vector3::UNIT_SCALE);
	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual void createScene(void);
	virtual void createFrameListener(void);
	virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	Ogre::Real mRotate;          // The rotate constant
	Ogre::Real mMove;
	Ogre::SceneNode *mCamNode;   
 	Ogre::Vector3 mDirection;    
	Ogre::SceneNode *manualnode;
	Ogre::SceneNode *parentnode;
	Ogre::SceneNode *hullNode;
	bool hullVisible,passageVisible,polygonVisible;
	Ogre::SceneNode *passageNode;
	Ogre::SceneNode *headNode;
	Ogre::SceneNode *sphereNode;
	Ogre::SceneNode *polygonNode;
	double alpha;
	double alphadiff;
	CEGUI::OgreRenderer* mRenderer;

	bool mShutDown;
 
};