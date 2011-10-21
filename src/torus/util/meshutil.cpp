#include "meshutil.h"

using namespace Ogre;


void util::Mesh::getMeshInformation(const Ogre::Mesh* const mesh,
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






ManualObject* util::Mesh::createManual(Ogre::SceneManager* mSceneMgr,Ogre::String name,Ogre::String materialname ,stdext::hash_map<const Ogre::String, Ogre::Vector3> vertexlist, std::vector<Index2Str> indices, Ogre::ColourValue colour, Ogre::RenderOperation::OperationType optype) {

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

ManualObject* util::Mesh::createManual(Ogre::SceneManager* mSceneMgr,Ogre::String name,Ogre::String materialname ,std::vector<Ogre::Vector3> vertexlist, std::vector<Index2> indices, Ogre::ColourValue colour, Ogre::RenderOperation::OperationType optype) {

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


ManualObject* util::Mesh::createManual(Ogre::SceneManager* mSceneMgr,Ogre::String name,Ogre::String materialname , Passage passage, Ogre::ColourValue colour, Ogre::RenderOperation::OperationType optype,bool shot, bool slices) {

	int id = 0;
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
			EndPoint prevoncircle = it->points.back();

			for(std::vector<EndPoint>::iterator it2 = (*it).points.begin(); it2 != (*it).points.end(); ++it2) {
				//adding sourcepoint->EndPoint lines
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

simplex::Plane* util::Mesh::createBestFitPlanes(Passage &passage) {

	simplex::Plane * planes = new simplex::Plane[passage.points.size()];
	
	int id = 0;
	int cnt = 0;
	
	

	for(std::vector<SourcePoint>::iterator it = passage.points.begin(); it != passage.points.end(); ++it) {
	
		planes[cnt] = util::Math::getBestFittingPlane(*it);
		cnt++;
	}

	return planes;
};


Vector util::Mesh::getPivotPoint(Passage& p) {

	int cnt = 0;
 	Vector pivot(0,0,0);

	for (std::vector<SourcePoint>::iterator it = p.points.begin(); it != p.points.end();++it) {
		
		pivot += *it;
		cnt++;
	}
	pivot /= cnt;
	return pivot;
};

Ogre::Vector3 util::Mesh::getPivotPoint(stdext::hash_map<const Ogre::String, Ogre::Vector3> &vertexliststr) {
	int cnt = 0;
 	Vector pivot(0,0,0);
	Ogre::Vector3 act;

	for(stdext::hash_map<const Ogre::String,Ogre::Vector3>::iterator it =  vertexliststr.begin();it != vertexliststr.end();++it) {
		if (it->first.compare(0, 1, "x")) { 
			act = it->second;
			pivot += Vector(act.x, act.y, act.z);
			cnt++;
		}
	}
	pivot /= cnt;
	return Ogre::Vector3(pivot.x, pivot.y, pivot.z);
}


Vector util::Mesh::getPivotPoint(std::vector<EndPoint> &basepoints) {
	int cnt = 0;
 	Vector pivot(0,0,0);
	Vector act;

	for(std::vector<EndPoint>::iterator it = basepoints.begin();it != basepoints.end();++it) {
		pivot += *it;
		cnt++;
	}
	pivot /= cnt;
	return Vector(pivot.x, pivot.y, pivot.z);
};

