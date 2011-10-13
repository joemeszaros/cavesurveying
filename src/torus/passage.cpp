
#include "passage.h"

void Passage::load(const char* pFilename)
{

	TiXmlDocument doc( "d:\\tmp\\cave.xml" );
	bool loadOkay = doc.LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
		exit( 1 );
	}
	//doc.Print( stdout );

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlElement* pElem2;
	TiXmlHandle hRoot(0);
	pElem=hDoc.FirstChildElement().Element();
	if (!pElem) return;
	// save this for later
	hRoot=TiXmlHandle(pElem);

	pElem=hRoot.FirstChild( "passages" ).FirstChild("passage").FirstChild().Element();

	
	//printf("%f\n" ,x);
	for( pElem; pElem; pElem=pElem->NextSiblingElement())
	{
		double x = atof(pElem->Attribute("x"));
		double y = atof(pElem->Attribute("y"));
		double z = atof(pElem->Attribute("z"));

		SourcePoint bp(x,y,z);

		pElem2 = pElem->FirstChild()->ToElement();
		for( pElem2; pElem2; pElem2=pElem2->NextSiblingElement()) 
		{

			const char *pX=pElem2->Attribute("x");
			const char *pY=pElem2->Attribute("y");
			const char *pZ=pElem2->Attribute("z");
			if (pX && pY && pZ) 
			{
				EndPoint p(atof(pX),atof(pY),atof(pZ));
				printf("%s %s\n",pY,pY);
				bp.points.push_back(p);
			}
			
		}
		this->points.push_back(bp);
	}
}

