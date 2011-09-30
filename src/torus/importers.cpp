#include "importers.h"
#include "inc/img.h"

void importers::SurvexImporter::import(std::string filename, vector<Ogre::Vector3> &vertexlist, std::vector<Index2> &indices) {

 img_point imgpt;
  int result;


//vector<Ogre::Vector3> vertexlist;
//vector<Index2> indices;
int pos = 0;
  string stnm;
img* pimg = img_open(filename.c_str());
  if (pimg == NULL)
    throw(("unable to open file"));  
  do {
    result = img_read_item(pimg, &imgpt);
    switch (result) {
    
      case img_MOVE:
		  vertexlist.push_back(Ogre::Vector3(imgpt.x,imgpt.y,imgpt.z));
     break;
        
      case img_LINE:
		vertexlist.push_back(Ogre::Vector3(imgpt.x,imgpt.y,imgpt.z));
		indices.push_back(Index2(vertexlist.size()-1,vertexlist.size()-2));
        break;
        
      case img_LABEL:  
		
		  stnm = pimg->label;/*
        // vlozime fix station
        stnm = pimg->label;
        if ((filterl > 0) && (strncmp(stnm, this->filter, filterl) == 0)) {
          stnm = &stnm[filterl];
          while ((*stnm != 0) && (*stnm == pimg->separator)) {
            stnm++;
          }
        }
        orig_name = stnm;
        if (strlen(stnm) < 1)
          break;
        if (svxs2ths.find(orig_name) == svxs2ths.end()) {
          sprintf(xb.get_buffer(), "%.16g", imgpt.x + this->calib_x);
          sprintf(yb.get_buffer(), "%.16g", imgpt.y + this->calib_y);
          sprintf(zb.get_buffer(), "%.16g", imgpt.z + this->calib_z);
          tmpsurvey = this->db->csurveyptr;
          new_name = this->station_name(stnm, pimg->separator, &tmpsst);
          // thprintf("%s -> %s\n", pimg->label, new_name.c_str());
          tmpdata = NULL;
          if (tmpsst.survey != NULL) {
            n1 = tmpsst.name.c_str();
            n2 = tmpsst.name.c_str();
            tmpdata = tmpsst.survey->data;
            this->db->csurveyptr = tmpsst.survey;
          } else {
            n1 = new_name.c_str();
            n2 = new_name.c_str();
            if (this->fsptr != NULL)
              tmpdata = this->fsptr->data;
            else {
              notimpst++;
              // do not import station
              break;
            }
          }
          tmppos.x = imgpt.x;
          tmppos.y = imgpt.y;
          tmppos.z = imgpt.z;
          tmpsst.fullname = new_name;
          svxpos2ths[tmppos] = tmpsst;
          svxs2ths[orig_name] = new_name;
          args[1] = xb.get_buffer();
          args[2] = yb.get_buffer();
          args[3] = zb.get_buffer();
          args[0] = n1.get_buffer();
          tmpdata->cs = this->cs;
          tmpdata->set_data_fix(4, args);
          // ak bude entrance, vlozi aj station
          if ((pimg->flags & img_SFLAG_ENTRANCE) != 0) {
            args[0] = n2.get_buffer();
	    args[1] = strcpy(a1, "");
            args[2] = strcpy(a2, "entrance");
            tmpdata->set_data_station(3, args, TT_UTF_8);
          }
          if ((pimg->flags & img_SFLAG_FIXED) == 0) {
            args[0] = n2.get_buffer();
            args[1] = strcpy(a1, "");
            args[2] = strcpy(a2, "not");
            args[3] = strcpy(a3, "fixed");
            tmpdata->set_data_station(4, args, TT_UTF_8);
          }
          this->db->csurveyptr = tmpsurvey;
        }*/
        break;
      case img_BAD:
        img_close(pimg);
        throw(("invalid file format"));
        break;
    }
  } while (result != img_STOP);
  img_close(pimg);


}

#define M_PI 3.14159265358979323846

void importers::PlotImporter::import(std::string filename, vector<Ogre::Vector3> &vertexlist, std::vector<Index2> &indices,std::vector<CaveOffset> &offsets) {
	ifstream in(filename.c_str());
	stringstream ss;

	string line,segments;
	double x,y,z;
	int index = 0,pos = 0,vpos = 0;
	double o1,o2,o3,o4;

	while(getline(in,line)) {

		if (line[0] == 'M' || line[0] == 'D') 
		{
			index = 0;
			ss << line;
			while (getline(ss,segments,' ')) {
				if (segments.size() == 0 || (segments[0] == ' ' && segments.size() == 1)) continue;

				switch (index) {
					case 0: break;
					case 1: x = atof(segments.c_str()); break;
					case 2: y = atof(segments.c_str()); break;
					case 3: z = atof(segments.c_str()); break;
					case 6: o1 = atof(segments.c_str()); break;
					case 7: o2 = atof(segments.c_str()); break;
					case 8: o3 = atof(segments.c_str()); break;
					case 9: o4 = atof(segments.c_str()); break;
				}
				index++;
			}

			vertexlist.push_back(Ogre::Vector3(x,y,z));
			offsets.push_back(CaveOffset(
				o1 < -900 ? 0 : o1,
				o2 < -900 ? 0 : o2,
				o3 < -900 ? 0 : o3,
				o4 < -900 ? 0 : o4));

			ss.clear();
			if (line[0] == 'D') {
				indices.push_back(Index2(pos-1,pos));
			}
			pos++;
		}

	}
	

}


void importers::PolygonImporter::import(std::string filename, stdext::hash_map<const std::string,Ogre::Vector3> &vertexlist, std::vector<Index2Str> &indices) {
	bool dataOK = false;
	stdext::hash_map<const std::string,BPoint> points;
	points["0"] = BPoint(Ogre::Vector3(0,0,0),true);

	CaveCoord cv;
	Ogre::Vector3 t;

	double xd, yd, zd;
	string line, segments;
	vector<string> items;
	ifstream in(filename.c_str());
	stringstream ss;
	string startpoint;
	string endpoint;
	double hossz;
	double irany;
	double lejtes;
	int pos = -1;	

	while(getline(in,line)) {

		if (line.find("End of survey data.") != -1) dataOK = false;

		if (dataOK)
		{
			ss << line; 

			while (getline(ss,segments,'\t')) {
				items.push_back(segments);
			}


			if (items.size() < 5) continue;
			startpoint = items[0];
			endpoint = items[1];
			indices.push_back(Index2Str(startpoint,endpoint));

			for (int i = 2; i <=4; i++) {
				pos = items[i].find(",");
				if (pos != -1)
				{ items[i].replace(pos,1,"."); }
			}
			hossz = atof(items[2].c_str());
			irany = atof(items[3].c_str());
			lejtes = atof(items[4].c_str());
			cv = CaveCoord(hossz, irany *  M_PI / 180, lejtes * M_PI / 180);
			xd = cv.Length *  cos(cv.Vertical) * cos(cv.Azimuth);
			yd = cv.Length * cos(cv.Vertical) * sin(cv.Azimuth);
			zd = cv.Length * sin(cv.Vertical);
			t = points[startpoint].p;
			BPoint ep = points[endpoint];
			if (ep.contains == false)
			{
				points[endpoint] = BPoint(Ogre::Vector3(  t.x + xd,t.y + yd,t.z + zd),true);
			}
			items.clear();
			ss.clear();
		}

		int  a = line.find("From");
		if (line.find("From") != -1) {
			dataOK = true;
		}
	}

	for(stdext::hash_map<const std::string,BPoint>::iterator it =  points.begin();it != points.end();++it) {
		vertexlist[(*it).first] = it->second.p;
	}


}