#include "meshutil.h"


using namespace Ogre;


void MeshUtil::getMeshInformation(const Ogre::Mesh* const mesh,
                        size_t &vertex_count,
                        Ogre::Vector3* &vertices,
                        size_t &index_count,
                        unsigned long* &indices,
                        const Ogre::Vector3 &position,
                        const Ogre::Quaternion &orient,
                        const Ogre::Vector3 &scale)
{
    bool added_shared = false;
    size_t current_offset = 0;
    size_t shared_offset = 0;
    size_t next_offset = 0;
    size_t index_offset = 0;
 
    vertex_count = index_count = 0;
 
    // Calculate how many vertices and indices we're going to need
    for ( unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
    {
		
        Ogre::SubMesh* submesh = mesh->getSubMesh(i);
        // We only need to add the shared vertices once
        if(submesh->useSharedVertices)
        {
            if( !added_shared )
            {
                vertex_count += mesh->sharedVertexData->vertexCount;
                added_shared = true;
            }
        }
        else
        {
            vertex_count += submesh->vertexData->vertexCount;
        }
        // Add the indices
        index_count += submesh->indexData->indexCount;
    }
 
    // Allocate space for the vertices and indices
    vertices = new Ogre::Vector3[vertex_count];
    indices = new unsigned long[index_count];
 
    added_shared = false;
 
    // Run through the submeshes again, adding the data into the arrays
    for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
    {
        Ogre::SubMesh* submesh = mesh->getSubMesh(i);
 
        Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;
 
        if ((!submesh->useSharedVertices) || (submesh->useSharedVertices && !added_shared))
        {
            if(submesh->useSharedVertices)
            {
                added_shared = true;
                shared_offset = current_offset;
            }
 
            const Ogre::VertexElement* posElem =
                vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
 
            Ogre::HardwareVertexBufferSharedPtr vbuf =
                vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());
 
            unsigned char* vertex =
                static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
 
            // There is _no_ baseVertexPointerToElement() which takes an Ogre::Real or a double
            //  as second argument. So make it float, to avoid trouble when Ogre::Real will
            //  be comiled/typedefed as double:
            //Ogre::Real* pReal;
            float* pReal;
 
            for( size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
            {
                posElem->baseVertexPointerToElement(vertex, &pReal);
                Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);
                vertices[current_offset + j] = (orient * (pt * scale)) + position;
            }
 
            vbuf->unlock();
            next_offset += vertex_data->vertexCount;
        }
 
        Ogre::IndexData* index_data = submesh->indexData;
        size_t numTris = index_data->indexCount / 3;
        Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
 
        bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);
 
        unsigned long* pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
        unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);
 
        size_t offset = (submesh->useSharedVertices)? shared_offset : current_offset;
 
        if ( use32bitindexes )
        {
            for ( size_t k = 0; k < numTris*3; ++k)
            {
                indices[index_offset++] = pLong[k] + static_cast<unsigned long>(offset);
            }
        }
        else
        {
            for ( size_t k = 0; k < numTris*3; ++k)
            {
                indices[index_offset++] = static_cast<unsigned long>(pShort[k]) +
                                          static_cast<unsigned long>(offset);
            }
        }
 
        ibuf->unlock();
        current_offset = next_offset;
    }
}



Ogre::MeshPtr MeshUtil::createMesh() {
    
    /// Create the mesh via the MeshManager
		Ogre::MeshPtr msh = MeshManager::getSingleton().createManual("ColourCube", "General");

    /// Create one submesh
    SubMesh* sub = msh->createSubMesh();
 
    const float sqrt13 = 0.577350269f; /* sqrt(1/3) */
 
    /// Define the vertices (8 vertices, each consisting of 2 groups of 3 floats
    const size_t nVertices = 8;
    const size_t vbufCount = 3*2*nVertices;
    float vertices[vbufCount] = {
            -100.0,100.0,-100.0,        //0 position
            -sqrt13,sqrt13,-sqrt13,     //0 normal
            100.0,100.0,-100.0,         //1 position
            sqrt13,sqrt13,-sqrt13,      //1 normal
            100.0,-100.0,-100.0,        //2 position
            sqrt13,-sqrt13,-sqrt13,     //2 normal
            -100.0,-100.0,-100.0,       //3 position
            -sqrt13,-sqrt13,-sqrt13,    //3 normal
            -100.0,100.0,100.0,         //4 position
            -sqrt13,sqrt13,sqrt13,      //4 normal
            100.0,100.0,100.0,          //5 position
            sqrt13,sqrt13,sqrt13,       //5 normal
            100.0,-100.0,100.0,         //6 position
            sqrt13,-sqrt13,sqrt13,      //6 normal
            -100.0,-100.0,100.0,        //7 position
            -sqrt13,-sqrt13,sqrt13,     //7 normal
    };
 
    RenderSystem* rs = Root::getSingleton().getRenderSystem();
    RGBA colours[nVertices];
    RGBA *pColour = colours;
    // Use render system to convert colour value since colour packing varies
    rs->convertColourValue(ColourValue(1.0,0.0,0.0), pColour++); //0 colour
    rs->convertColourValue(ColourValue(1.0,1.0,0.0), pColour++); //1 colour
    rs->convertColourValue(ColourValue(0.0,1.0,0.0), pColour++); //2 colour
    rs->convertColourValue(ColourValue(0.0,0.0,0.0), pColour++); //3 colour
    rs->convertColourValue(ColourValue(1.0,0.0,1.0), pColour++); //4 colour
    rs->convertColourValue(ColourValue(1.0,1.0,1.0), pColour++); //5 colour
    rs->convertColourValue(ColourValue(0.0,1.0,1.0), pColour++); //6 colour
    rs->convertColourValue(ColourValue(0.0,0.0,1.0), pColour++); //7 colour
 
    /// Define 12 triangles (two triangles per cube face)
    /// The values in this table refer to vertices in the above table
    const size_t ibufCount = 36;
    unsigned short faces[ibufCount] = {
            0,2,3,
            0,1,2,
            1,6,2,
            1,5,6,
            4,6,5,
            4,7,6,
            0,7,4,
            0,3,7,
            0,5,1,
            0,4,5,
            2,7,3,
            2,6,7
    };
 
    /// Create vertex data structure for 8 vertices shared between submeshes
    msh->sharedVertexData = new VertexData();
    msh->sharedVertexData->vertexCount = nVertices;
 
    /// Create declaration (memory format) of vertex data
    VertexDeclaration* decl = msh->sharedVertexData->vertexDeclaration;
    size_t offset = 0;
    // 1st buffer
    decl->addElement(0, offset, VET_FLOAT3, VES_POSITION);
    offset += VertexElement::getTypeSize(VET_FLOAT3);
    decl->addElement(0, offset, VET_FLOAT3, VES_NORMAL);
    offset += VertexElement::getTypeSize(VET_FLOAT3);
    /// Allocate vertex buffer of the requested number of vertices (vertexCount) 
    /// and bytes per vertex (offset)
    HardwareVertexBufferSharedPtr vbuf = 
        HardwareBufferManager::getSingleton().createVertexBuffer(
        offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
    /// Upload the vertex data to the card
    vbuf->writeData(0, vbuf->getSizeInBytes(), vertices, true);
 
    /// Set vertex buffer binding so buffer 0 is bound to our vertex buffer
    VertexBufferBinding* bind = msh->sharedVertexData->vertexBufferBinding; 
    bind->setBinding(0, vbuf);
 
    // 2nd buffer
    offset = 0;
    decl->addElement(1, offset, VET_COLOUR, VES_DIFFUSE);
    offset += VertexElement::getTypeSize(VET_COLOUR);
    /// Allocate vertex buffer of the requested number of vertices (vertexCount) 
    /// and bytes per vertex (offset)
    vbuf = HardwareBufferManager::getSingleton().createVertexBuffer(
        offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
    /// Upload the vertex data to the card
    vbuf->writeData(0, vbuf->getSizeInBytes(), colours, true);
 
    /// Set vertex buffer binding so buffer 1 is bound to our colour buffer
    bind->setBinding(1, vbuf);
 
    /// Allocate index buffer of the requested number of vertices (ibufCount) 
    HardwareIndexBufferSharedPtr ibuf = HardwareBufferManager::getSingleton().
        createIndexBuffer(
        HardwareIndexBuffer::IT_16BIT, 
        ibufCount, 
        HardwareBuffer::HBU_STATIC_WRITE_ONLY);
 
    /// Upload the index data to the card
    ibuf->writeData(0, ibuf->getSizeInBytes(), faces, true);
 
    /// Set parameters of the submesh
    sub->useSharedVertices = true;
    sub->indexData->indexBuffer = ibuf;
    sub->indexData->indexCount = ibufCount;
    sub->indexData->indexStart = 0;
 
    /// Set bounding information (for culling)
    msh->_setBounds(AxisAlignedBox(-100,-100,-100,100,100,100));
    msh->_setBoundingSphereRadius(Math::Sqrt(3*100*100));
 
    /// Notify -Mesh object that it has been loaded
    //msh->load();
    return msh;
	}


ManualObject* MeshUtil::createManual(Ogre::SceneManager* mSceneMgr,Ogre::String name,Ogre::String materialname ,stdext::hash_map<const Ogre::String, Ogre::Vector3> vertexlist, std::vector<Index2Str> indices, Ogre::ColourValue colour, Ogre::RenderOperation::OperationType optype) {

	ManualObject* manual = mSceneMgr->createManualObject(name);
	manual->setDynamic(true);
	manual->begin(materialname, optype);
	for(std::vector<Index2Str>::iterator it = indices.begin(); it != indices.end(); ++it) {
		manual->position(vertexlist[(*it).i1]);
		manual->colour(colour);
		manual->position(vertexlist[(*it).i2]);
		manual->colour(colour);
	} 
	manual->end();
	return manual;
};

ManualObject* MeshUtil::createManual(Ogre::SceneManager* mSceneMgr,Ogre::String name,Ogre::String materialname ,std::vector<Ogre::Vector3> vertexlist, std::vector<Index2> indices, Ogre::ColourValue colour, Ogre::RenderOperation::OperationType optype) {

	ManualObject* manual = mSceneMgr->createManualObject(name);
	manual->setDynamic(true);
	manual->begin(materialname, optype);
	for(std::vector<Index2>::iterator it = indices.begin(); it != indices.end(); ++it) {
		manual->position(vertexlist[(*it).i1]);
		manual->colour(colour);
		manual->position(vertexlist[(*it).i2]);
		manual->colour(colour);
	} 
	manual->end();
	return manual;
};


ManualObject* MeshUtil::createManual(Ogre::SceneManager* mSceneMgr,Ogre::String name,Ogre::String materialname , Passage passage, Ogre::ColourValue colour, Ogre::RenderOperation::OperationType optype,bool shot, bool slices) {

	ManualObject* manual = mSceneMgr->createManualObject(name);
	manual->setDynamic(true);
	manual->begin(materialname, optype);
	
	SourcePoint prev = passage.points.front();

	for(std::vector<SourcePoint>::iterator it = passage.points.begin(); it != passage.points.end(); ++it) {
	
		if (shot) {
			manual->position(prev.x,prev.y,prev.z);
			manual->colour(Ogre::ColourValue(1,1,1));
			manual->position(it->x,it->y,it->z);
			manual->colour(Ogre::ColourValue(1,1,1));
		}
		if (it->points.size() > 0 && (slices || shot)) {
			BasePoint prevoncircle = it->points.back();

			for(std::vector<BasePoint>::iterator it2 = (*it).points.begin(); it2 != (*it).points.end(); ++it2) {
				//adding sourcepoint->basepoint lines
				if (shot) {
					manual->position(it->x,it->y,it->z);
					manual->colour(colour);
					manual->position(it2->x,it2->y,it2->z);
					manual->colour(colour); 
				}

				if (slices) {
					manual->position(prevoncircle.x,prevoncircle.y,prevoncircle.z);
					manual->colour(Ogre::ColourValue(0,1,0));
					manual->position(it2->x,it2->y,it2->z);
					manual->colour(Ogre::ColourValue(0,1,0));
					prevoncircle =  *it2;
				}
			}
		}
		prev = *it;
	} 
	manual->end();
	return manual;
};

Ogre::Vector3 MeshUtil::getPivotPoint(Passage& p) {

	int cnt = 0;
 	Point pivot(0,0,0);

	for (std::vector<SourcePoint>::iterator it = p.points.begin(); it != p.points.end();++it) {
		
		pivot += it->toPoint();
		cnt++;
	}
	pivot /= cnt;
	return Ogre::Vector3(pivot.x, pivot.y, pivot.z);
};

Ogre::Vector3 MeshUtil::getPivotPoint(stdext::hash_map<const Ogre::String, Ogre::Vector3> &vertexliststr) {
	int cnt = 0;
 	Point pivot(0,0,0);
	Ogre::Vector3 act;

	for(stdext::hash_map<const Ogre::String,Ogre::Vector3>::iterator it =  vertexliststr.begin();it != vertexliststr.end();++it) {
		if (it->first.compare(0, 1, "x")) { 
			act = it->second;
			pivot += Point(act.x, act.y, act.z);
			cnt++;
		}
	}
	pivot /= cnt;
	return Ogre::Vector3(pivot.x, pivot.y, pivot.z);
}


Point MeshUtil::getPivotPoint(std::vector<BasePoint> &basepoints) {
	int cnt = 0;
 	Point pivot(0,0,0);
	Point act;

	for(std::vector<BasePoint>::iterator it = basepoints.begin();it != basepoints.end();++it) {
		pivot += it->toPoint();
		cnt++;
	}
	pivot /= cnt;
	return Point(pivot.x, pivot.y, pivot.z);
}

void MeshUtil::createSphere(const std::string& strName, const float r, const int nRings, const int nSegments)
 {
     MeshPtr pSphere = MeshManager::getSingleton().createManual(strName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
     SubMesh *pSphereVertex = pSphere->createSubMesh();
 
     pSphere->sharedVertexData = new VertexData();
     VertexData* vertexData = pSphere->sharedVertexData;
 
     // define the vertex format
     VertexDeclaration* vertexDecl = vertexData->vertexDeclaration;
     size_t currOffset = 0;
     // positions
     vertexDecl->addElement(0, currOffset, VET_FLOAT3, VES_POSITION);
     currOffset += VertexElement::getTypeSize(VET_FLOAT3);
     // normals
     vertexDecl->addElement(0, currOffset, VET_FLOAT3, VES_NORMAL);
     currOffset += VertexElement::getTypeSize(VET_FLOAT3);
     // two dimensional texture coordinates
     vertexDecl->addElement(0, currOffset, VET_FLOAT2, VES_TEXTURE_COORDINATES, 0);
     currOffset += VertexElement::getTypeSize(VET_FLOAT2);
 
     // allocate the vertex buffer
     vertexData->vertexCount = (nRings + 1) * (nSegments+1);
     HardwareVertexBufferSharedPtr vBuf = HardwareBufferManager::getSingleton().createVertexBuffer(vertexDecl->getVertexSize(0), vertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
     VertexBufferBinding* binding = vertexData->vertexBufferBinding;
     binding->setBinding(0, vBuf);
     float* pVertex = static_cast<float*>(vBuf->lock(HardwareBuffer::HBL_DISCARD));
 
     // allocate index buffer
     pSphereVertex->indexData->indexCount = 6 * nRings * (nSegments + 1);
     pSphereVertex->indexData->indexBuffer = HardwareBufferManager::getSingleton().createIndexBuffer(HardwareIndexBuffer::IT_16BIT, pSphereVertex->indexData->indexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
     HardwareIndexBufferSharedPtr iBuf = pSphereVertex->indexData->indexBuffer;
     unsigned short* pIndices = static_cast<unsigned short*>(iBuf->lock(HardwareBuffer::HBL_DISCARD));
 
     float fDeltaRingAngle = (Math::PI / nRings);
     float fDeltaSegAngle = (2 * Math::PI / nSegments);
     unsigned short wVerticeIndex = 0 ;
 
     // Generate the group of rings for the sphere
     for( int ring = 0; ring <= nRings; ring++ ) {
         float r0 = r * sinf (ring * fDeltaRingAngle);
         float y0 = r * cosf (ring * fDeltaRingAngle);
 
         // Generate the group of segments for the current ring
         for(int seg = 0; seg <= nSegments; seg++) {
             float x0 = r0 * sinf(seg * fDeltaSegAngle);
             float z0 = r0 * cosf(seg * fDeltaSegAngle);
 
             // Add one vertex to the strip which makes up the sphere
             *pVertex++ = x0;
             *pVertex++ = y0;
             *pVertex++ = z0;
 
             Vector3 vNormal = Vector3(x0, y0, z0).normalisedCopy();
             *pVertex++ = vNormal.x;
             *pVertex++ = vNormal.y;
             *pVertex++ = vNormal.z;
 
             *pVertex++ = (float) seg / (float) nSegments;
             *pVertex++ = (float) ring / (float) nRings;
 
             if (ring != nRings) {
                                // each vertex (except the last) has six indices pointing to it
                 *pIndices++ = wVerticeIndex + nSegments + 1;
                 *pIndices++ = wVerticeIndex;               
                 *pIndices++ = wVerticeIndex + nSegments;
                 *pIndices++ = wVerticeIndex + nSegments + 1;
                 *pIndices++ = wVerticeIndex + 1;
                 *pIndices++ = wVerticeIndex;
                 wVerticeIndex ++;
             }
         }; // end for seg
     } // end for ring
 
     // Unlock
     vBuf->unlock();
     iBuf->unlock();
     // Generate face list
     pSphereVertex->useSharedVertices = true;
 
     // the original code was missing this line:
     pSphere->_setBounds( AxisAlignedBox( Vector3(-r, -r, -r), Vector3(r, r, r) ), false );
     pSphere->_setBoundingSphereRadius(r);
         // this line makes clear the mesh is loaded (avoids memory leaks)
         pSphere->load();
  };