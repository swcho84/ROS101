#include "CvtKitty2Bbox.h"

using namespace std;
using namespace ros;
using namespace cv;

CvtKtt2Bbox::CvtKtt2Bbox(const ConfigParam& cfg) : cfgParam_(cfg)
{
  // default: VGA size
  nHeight = 480;
  nWidth = 640;

  // for cityscapes, (h1024, w2048)
  nHeightCityScapeDB = 1024;
  nWidthCityScapeDB = 2048;

  bSizeCalcFlag = false;
}

CvtKtt2Bbox::~CvtKtt2Bbox()
{
}

// main loop: xml file generator
void CvtKtt2Bbox::MainLoopBboxGenerator()
{
  // // 1st, resizing raw image and saving resized images
  // // assigning variables for browsing annotated images recursively
  // vector<String> vecImgFileNm;
  // glob(cfgParam_.strKttImgFolderPath, vecImgFileNm, true);

  // // browsing annotated images recursively
  // for (size_t i = 0; i < vecImgFileNm.size(); i++)
  // {
  //   // assigning the raw image
  //   Mat imgRaw = imread(vecImgFileNm[i]);

  //   // image width and height info. (h1024, w2048)
  //   nHeight = imgRaw.rows;
  //   nWidth = imgRaw.cols;

  //   // resizing w.r.t the cityscapesDB
  //   Mat imgResize;
  //   resize(imgRaw, imgResize, Size(nWidthCityScapeDB, nHeightCityScapeDB), 0, 0, CV_INTER_NN);

  //   // making the filename  using stringstream, with the numbering rule
  //   stringstream strStreamImgFileName;
  //   strStreamImgFileName << cfgParam_.strKttImgFileNmFwd;
  //   strStreamImgFileName << std::setfill('0') << std::setw(cfgParam_.nKttImgFileNmDigit) << i;
  //   strStreamImgFileName << "." + cfgParam_.strKttImgExt;

  //   // making the full file path
  //   string strCvtImgFile;
  //   strCvtImgFile = cfgParam_.strKttCvtImgFolderPath + strStreamImgFileName.str();

  //   // saving the resized image
  //   imwrite(strCvtImgFile, imgResize);

  //   // calculating size flag
  //   bSizeCalcFlag = GenSizeCalcFlag(i, (int)(vecImgFileNm.size()));
  // }

  // 2nd, reading, matching, resizing raw bbox data and saving resized bbox data w.r.t the xml type
  vector<String> vecImgFileNm;
  vector<String> vecCvtImgFileNm;
  vector<String> vecTxtFileNm;
  vecKittyDB.clear();
  glob(cfgParam_.strKttImgFolderPath, vecImgFileNm, true);
  glob(cfgParam_.strKttCvtImgFolderPath, vecCvtImgFileNm, true);
  glob(cfgParam_.strKttLabelFolderPath, vecTxtFileNm, true);

  // browsing annotated images recursively
  for (size_t i = 0; i < vecImgFileNm.size(); i++)
  {
    // assigning the raw image
    Mat imgRaw = imread(vecImgFileNm[i]);
    Mat imgCvtRaw = imread(vecCvtImgFileNm[i]);

    // image width and height info. (h1024, w2048)
    nHeight = imgRaw.rows;
    nWidth = imgRaw.cols;

    // reading txt file
    ifstream openFile(vecTxtFileNm[i]);
    if (openFile.is_open())
    {
      // parsing kitty label into vector-list type
      string strLine;
      vector<KittyDB> tempKittyVec;

      // parsing line-by-line
      while (getline(openFile, strLine))
      {
        istringstream strStrmLine(strLine);
        string strToken;
        int nFlag = 0;
        KittyDB tempKittyDB;

        // parsing space-by-space
        while (getline(strStrmLine, strToken, ' '))
        {
          switch (nFlag)
          {
            case 0:
            {
              tempKittyDB.strLabel = strToken;
              break;
            }
            case 1:
            {
              tempKittyDB.nTruncated = atoi(strToken.c_str());
              break;
            }
            case 2:
            {
              tempKittyDB.nOcculded = atoi(strToken.c_str());
              break;
            }
            case 3:
            {
              tempKittyDB.fAlphaAngRad = (float)(atoi(strToken.c_str()));
              break;
            }
            case 4:
            {
              tempKittyDB.fBbox[0] = (float)(atoi(strToken.c_str()));
              float nNormalized = tempKittyDB.fBbox[0] / nWidth;
              float nResized = nNormalized * nWidthCityScapeDB;
              tempKittyDB.fBbox[0] = nResized;
              break;
            }
            case 5:
            {
              tempKittyDB.fBbox[1] = (float)(atoi(strToken.c_str()));
              float nNormalized = tempKittyDB.fBbox[1] / nHeight;
              float nResized = nNormalized * nHeightCityScapeDB;
              tempKittyDB.fBbox[1] = nResized;
              break;
            }
            case 6:
            {
              tempKittyDB.fBbox[2] = (float)(atoi(strToken.c_str()));
              float nNormalized = tempKittyDB.fBbox[2] / nWidth;
              float nResized = nNormalized * nWidthCityScapeDB;
              tempKittyDB.fBbox[2] = nResized;
              break;
            }
            case 7:
            {
              tempKittyDB.fBbox[3] = (float)(atoi(strToken.c_str()));
              float nNormalized = tempKittyDB.fBbox[3] / nHeight;
              float nResized = nNormalized * nHeightCityScapeDB;
              tempKittyDB.fBbox[3] = nResized;
              break;
            }
            case 8:
            {
              tempKittyDB.fObjDimM[0] = (float)(atoi(strToken.c_str()));
              break;
            }
            case 9:
            {
              tempKittyDB.fObjDimM[1] = (float)(atoi(strToken.c_str()));
              break;
            }
            case 10:
            {
              tempKittyDB.fObjDimM[2] = (float)(atoi(strToken.c_str()));
              break;
            }
            case 11:
            {
              tempKittyDB.fObjLocM[0] = (float)(atoi(strToken.c_str()));
              break;
            }
            case 12:
            {
              tempKittyDB.fObjLocM[1] = (float)(atoi(strToken.c_str()));
              break;
            }
            case 13:
            {
              tempKittyDB.fObjLocM[2] = (float)(atoi(strToken.c_str()));
              break;
            }
            case 14:
            {
              tempKittyDB.fRotAngRad = (float)(atoi(strToken.c_str()));
              break;
            }
          }

          nFlag++;
        }

        // saving parsing result w.r.t space
        tempKittyVec.push_back(tempKittyDB);
      }

      // saving parsing result w.r.t line
      vecKittyDB.push_back(tempKittyVec);
      openFile.close();
    }

    // for debugging
    ROS_INFO("Processing_xmlDB(%d,%d)", (int)(i), (int)(vecImgFileNm.size()));

    // making the filename  using stringstream, with the numbering rule
    stringstream strStreamFileName;
    strStreamFileName << cfgParam_.strKttXmlFileNmFwd;
    strStreamFileName << std::setfill('0') << std::setw(cfgParam_.nKttXmlFileNmDigit) << i;
    strStreamFileName << "." + cfgParam_.strKttXmlExt;

    // making the full file path
    string strXmlFile;
    strXmlFile = cfgParam_.strKttXmlFolderPath + strStreamFileName.str();

    // declarating xml file
    TiXmlDocument docXml;

    // w.r.t pascal VOC xml file
    TiXmlElement* pRoot = new TiXmlElement("annotation");
    docXml.LinkEndChild(pRoot);

    TiXmlElement* pElem0 = new TiXmlElement("folder");
    TiXmlText* txtElem0 = new TiXmlText("VOC2017");
    pElem0->LinkEndChild(txtElem0);
    pRoot->LinkEndChild(pElem0);

    TiXmlElement* pElem1 = new TiXmlElement("filename");
    TiXmlText* txtElem1 = new TiXmlText(strStreamFileName.str());
    pElem1->LinkEndChild(txtElem1);
    pRoot->LinkEndChild(pElem1);

    TiXmlElement* pElem2 = new TiXmlElement("source");
    TiXmlElement* pElem21 = new TiXmlElement("database");
    TiXmlText* txtElem21 = new TiXmlText("ETRI collision avoidance DB");
    pElem21->LinkEndChild(txtElem21);
    TiXmlElement* pElem22 = new TiXmlElement("annotation");
    TiXmlText* txtElem22 = new TiXmlText("PASCAL VOC2017");
    pElem22->LinkEndChild(txtElem22);
    pElem2->LinkEndChild(pElem21);
    pElem2->LinkEndChild(pElem22);
    pRoot->LinkEndChild(pElem2);

    TiXmlElement* pElem3 = new TiXmlElement("owner");
    TiXmlElement* pElem31 = new TiXmlElement("institute");
    TiXmlText* txtElem31 = new TiXmlText("ETRI");
    pElem31->LinkEndChild(txtElem31);
    TiXmlElement* pElem32 = new TiXmlElement("name");
    TiXmlText* txtElem32 = new TiXmlText("Dr. Eunhye Kim");
    pElem32->LinkEndChild(txtElem32);
    pElem3->LinkEndChild(pElem31);
    pElem3->LinkEndChild(pElem32);
    pRoot->LinkEndChild(pElem3);

    TiXmlElement* pElem4 = new TiXmlElement("size");
    TiXmlElement* pElem41 = new TiXmlElement("width");
    TiXmlText* txtElem41 = new TiXmlText(to_string(nWidthCityScapeDB));
    pElem41->LinkEndChild(txtElem41);
    TiXmlElement* pElem42 = new TiXmlElement("height");
    TiXmlText* txtElem42 = new TiXmlText(to_string(nHeightCityScapeDB));
    pElem42->LinkEndChild(txtElem42);
    TiXmlElement* pElem43 = new TiXmlElement("depth");
    TiXmlText* txtElem43 = new TiXmlText("3");
    pElem43->LinkEndChild(txtElem43);
    pElem4->LinkEndChild(pElem41);
    pElem4->LinkEndChild(pElem42);
    pElem4->LinkEndChild(pElem43);
    pRoot->LinkEndChild(pElem4);

    TiXmlElement* pElem5 = new TiXmlElement("segmented");
    TiXmlText* txtElem5 = new TiXmlText("0");
    pElem5->LinkEndChild(txtElem5);
    pRoot->LinkEndChild(pElem5);

    // making xml file
    for (auto kk = 0; kk < vecKittyDB[i].size(); kk++)
    {
      for (auto kkk = 0; kkk < cfgParam_.vecAnnoKttDB.size(); kkk++)
      {
        // reselecting data using the selected label
        if (cfgParam_.vecAnnoKttDB[kkk].strLabel == vecKittyDB[i][kk].strLabel)
        {
          TiXmlElement* pElem5 = new TiXmlElement("object");
          TiXmlElement* pElem51 = new TiXmlElement("name");
          TiXmlText* txtElem51 = new TiXmlText(vecKittyDB[i][kk].strLabel);
          pElem51->LinkEndChild(txtElem51);
          TiXmlElement* pElem52 = new TiXmlElement("pose");
          TiXmlText* txtElem52 = new TiXmlText("Left");
          pElem52->LinkEndChild(txtElem52);
          TiXmlElement* pElem53 = new TiXmlElement("truncated");
          TiXmlText* txtElem53 = new TiXmlText("1");
          pElem53->LinkEndChild(txtElem53);
          TiXmlElement* pElem54 = new TiXmlElement("difficult");
          TiXmlText* txtElem54 = new TiXmlText("0");
          pElem54->LinkEndChild(txtElem54);

          Point ptTl, ptBr;
          ptTl.x = (int)(vecKittyDB[i][kk].fBbox[0]);
          ptTl.y = (int)(vecKittyDB[i][kk].fBbox[1]);
          ptBr.x = (int)(vecKittyDB[i][kk].fBbox[2]);
          ptBr.y = (int)(vecKittyDB[i][kk].fBbox[3]);
          TiXmlElement* pElem55 = new TiXmlElement("bndbox");
          TiXmlElement* pElem551 = new TiXmlElement("xmin");
          TiXmlText* txtElem551 = new TiXmlText(to_string(ptTl.x));
          pElem551->LinkEndChild(txtElem551);
          TiXmlElement* pElem552 = new TiXmlElement("ymin");
          TiXmlText* txtElem552 = new TiXmlText(to_string(ptTl.y));
          pElem552->LinkEndChild(txtElem552);
          TiXmlElement* pElem553 = new TiXmlElement("xmax");
          TiXmlText* txtElem553 = new TiXmlText(to_string(ptBr.x));
          pElem553->LinkEndChild(txtElem553);
          TiXmlElement* pElem554 = new TiXmlElement("ymax");
          TiXmlText* txtElem554 = new TiXmlText(to_string(ptBr.y));
          pElem554->LinkEndChild(txtElem554);
          pElem55->LinkEndChild(pElem551);
          pElem55->LinkEndChild(pElem552);
          pElem55->LinkEndChild(pElem553);
          pElem55->LinkEndChild(pElem554);

          pElem5->LinkEndChild(pElem51);
          pElem5->LinkEndChild(pElem52);
          pElem5->LinkEndChild(pElem53);
          pElem5->LinkEndChild(pElem54);
          pElem5->LinkEndChild(pElem55);
          pRoot->LinkEndChild(pElem5);

          // // for debugging
          // ROS_INFO("[%d]label(%s), bbox(tl,br):(%d,%d)////(%d,%d)", (int)(kk), vecKittyDB[i][kk].strLabel.c_str(),
          //         (int)(vecKittyDB[i][kk].fBbox[0]), (int)(vecKittyDB[i][kk].fBbox[1]),
          //         (int)(vecKittyDB[i][kk].fBbox[2]),
          //         (int)(vecKittyDB[i][kk].fBbox[3]));
          // rectangle(imgCvtRaw, ptTl, ptBr, colorStat_.scalRed, 2);
        }
      }
    }

    // // for debugging
    // ROS_INFO(" ");

    // saving xml file
    docXml.SaveFile(strXmlFile);

    // calculating size flag
    bSizeCalcFlag = GenSizeCalcFlag(i, (int)(vecImgFileNm.size()));

    // // for debugging
    // imshow("imgCvtRaw", imgCvtRaw);

    // // pausing and destroying all imshow result
    // waitKey(0);
  }

  return;
}

// get size calculation flag
bool CvtKtt2Bbox::GetSizeCalcFlag()
{
  return bSizeCalcFlag;
}

// generating size calculation flag for terminating converter
bool CvtKtt2Bbox::GenSizeCalcFlag(int nSize, int nTotal)
{
  bool bRes = false;
  if (fabs(nSize - nTotal) == 1.0f)
    bRes = true;
  return bRes;
}