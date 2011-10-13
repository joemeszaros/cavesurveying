#include <OgreMesh.h> 
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <OgreSubMesh.h>
#include <OgreMeshManager.h>
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgreHardwareBufferManager.h>
#include <OgreManualObject.h>
#include <vector>
#include "../base.h"
#include <hash_map>
#include "../passage.h"

#ifndef MESHUTIL_H
#define MESHUTIL_H

namespace util
{
	class Mesh
	{
	public:
		static void getMeshInformation(const Ogre::Mesh* const mesh,
							size_t &vertex_count,
							Ogre::Vector3* &veVector3rtices,
							size_t &index_count,
							unsigned long* &indices,
							const Ogre::Vector3 &position  = Ogre::Vector3::ZERO,
							const Ogre::Quaternion &orient = Ogre::Quaternion::IDENTITY,
							const Ogre::Vector3 &scale = Ogre::Vector3::UNIT_SCALE);
		static Ogre::MeshPtr util::Mesh::createMesh();
		static Ogre::ManualObject* createManual(Ogre::SceneManager* mSceneMgr,Ogre::String name,Ogre::String materialname,stdext::hash_map<const Ogre::String, Ogre::Vector3> vertexlist, std::vector<Index2Str> indices, Ogre::ColourValue colour, Ogre::RenderOperation::OperationType optype = Ogre::RenderOperation::OT_TRIANGLE_LIST);
		static Ogre::ManualObject* createManual(Ogre::SceneManager* mSceneMgr,Ogre::String name,Ogre::String materialname ,std::vector<Ogre::Vector3> vertexlist, std::vector<Index2> indices, Ogre::ColourValue colour, Ogre::RenderOperation::OperationType optype);
		static Ogre::ManualObject* createManual(Ogre::SceneManager* mSceneMgr,Ogre::String name,Ogre::String materialname , Passage passage, Ogre::ColourValue colour, Ogre::RenderOperation::OperationType optype, bool shot, bool slices);
		static Ogre::Vector3 getPivotPoint(Passage& p);
		static void createSphere(const std::string& strName, const float r, const int nRings = 16, const int nSegments = 16);
		static Ogre::Vector3 getPivotPoint(stdext::hash_map<const Ogre::String, Ogre::Vector3> &vertexliststr);
		static Vector getPivotPoint(std::vector<EndPoint> &basepoints);
	};
}
#endif