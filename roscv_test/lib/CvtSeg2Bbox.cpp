#include "CvtSeg2Bbox.h"

using namespace std;
using namespace ros;
using namespace cv;

CvtSeg2Bbox::CvtSeg2Bbox(const ConfigParam& cfg) : cfgParam_(cfg)
{
  // VGA size
  nHeight = 480;
  nWidth = 640;

  bSizeCalcFlag = false;
}

CvtSeg2Bbox::~CvtSeg2Bbox()
{
}

// main loop: xml file checker
void CvtSeg2Bbox::MainLoopBboxChecker()
{
  return;
}

// main loop: xml file generator
void CvtSeg2Bbox::MainLoopBboxGenerator()
{
  // 1st, making polygonDB-based bbox
  // assigning variables for browsing annotated images recursively
  vector<String> vecAnnoFileNm;
  glob(cfgParam_.strAnnoFolderPath, vecAnnoFileNm, true);
  cfgParam_.vecImgBboxDB.clear();

  // browsing annotated images recursively
  for (size_t i = 0; i < vecAnnoFileNm.size(); i++)
  {
    // for debugging
    ROS_INFO("Processing_maskImgDB(%d,%d)", (int)(i), (int)(vecAnnoFileNm.size()));

    // assigning the raw image
    Mat imgRaw = imread(vecAnnoFileNm[i]);

    // image width and height info. (h1024, w2048)
    nHeight = imgRaw.rows;
    nWidth = imgRaw.cols;

    // generating bbox data w.r.t the labelDB
    vector<BboxDB> vecBboxDB;
    for (auto ii = 0; ii < cfgParam_.vecAnnoDB.size(); ii++)
    {
      // generating the filtered image using the label data
      Mat imgFiltered;
      imgFiltered = GenFilteredImg(imgRaw, nHeight, nWidth, ii, cfgParam_.nMorphThresh);

      // detecting canny edge data
      Mat imgCanny;
      imgCanny = CannyEdge(imgFiltered, cfgParam_.nCannyThresh);

      // generating bounding box data
      vector<Rect> vecBbox;
      vecBbox = GenBboxData(imgCanny, Scalar(cfgParam_.vecAnnoDB[ii].nRGB[2], cfgParam_.vecAnnoDB[ii].nRGB[1],
                                             cfgParam_.vecAnnoDB[ii].nRGB[0]),
                            cfgParam_.nPolyDPThesh);

      // saving bbox data
      if (vecBbox.size() > 0)
      {
        BboxDB tempBbox;
        tempBbox.vecBbox.clear();
        tempBbox.strLabel = cfgParam_.vecAnnoDB[ii].strLabel;
        for (auto iii = 0; iii < vecBbox.size(); iii++)
          tempBbox.vecBbox.push_back(vecBbox[iii]);

        vecBboxDB.push_back(tempBbox);
      }
    }

    // saving results using vector
    cfgParam_.vecImgBboxDB.push_back(vecBboxDB);
  }

  // for debugging
  ROS_INFO("vecImgBboxDB.size:%d", (int)(cfgParam_.vecImgBboxDB.size()));
  ROS_INFO(" ");

  // 2nd, making maskImg-based bbox
  // assigning variables for browsing polygon data w.r.t json file recursively
  vector<String> vecPolygonFileNm;
  glob(cfgParam_.strPolygonFolderPath, vecPolygonFileNm, true);
  cfgParam_.vecPolygonBboxDB.clear();

  // browsing mask images recursively
  for (size_t k = 0; k < vecPolygonFileNm.size(); k++)
  {
    // for debugging
    ROS_INFO("Processing_polygonDB(%d,%d)", (int)(k), (int)(vecPolygonFileNm.size()));

    // assigning the polygon file
    ifstream polyJson(vecPolygonFileNm[k]);
    json js;
    polyJson >> js;

    // generating polygon data by using the selected label
    vector<BboxDB> vecBboxDB;
    for (auto kk = 0; kk < js["objects"].size(); kk++)
    {
      // for using debugging image
      Mat imgTest = Mat::zeros(Size(nWidth, nHeight), CV_8UC3);

      // w.r.t the selected label
      for (auto kkk = 0; kkk < cfgParam_.vecAnnoDB.size(); kkk++)
      {
        Rect rectBbox;
        BboxDB tempBbox;

        // if the selected label in the objects of JSON file
        if ((js["objects"][kk]["label"] == cfgParam_.vecAnnoDB[kkk].strLabel))
        {
          vector<Point> vecContour;

          // generating polygon data
          for (auto kkkk = 0; kkkk < js["objects"][kk]["polygon"].size(); kkkk++)
          {
            // parsing each point data
            Point tempPt;
            tempPt.x = js["objects"][kk]["polygon"][kkkk][0];
            tempPt.y = js["objects"][kk]["polygon"][kkkk][1];
            vecContour.push_back(tempPt);
          }

          // calculating bounding box information
          if (vecContour.size() > 0)
          {
            rectBbox = boundingRect(vecContour);
            tempBbox.strLabel = cfgParam_.vecAnnoDB[kkk].strLabel;
            tempBbox.vecBbox.push_back(rectBbox);

            vecBboxDB.push_back(tempBbox);
          }
        }
      }
    }

    // saving polygon-based bbox DB
    cfgParam_.vecPolygonBboxDB.push_back(vecBboxDB);
  }

  // for debugging
  ROS_INFO("vecPolygonBboxDB.size:%d", (int)(cfgParam_.vecPolygonBboxDB.size()));
  ROS_INFO(" ");

  // assigning variables for browsing raw images with bbox result and saving bbox position data recursively
  vector<String> vecRawFileNm;
  glob(cfgParam_.strRawFolderPath, vecRawFileNm, true);

  // browsing raw images recursively
  for (size_t k = 0; k < vecRawFileNm.size(); k++)
  {
    // for debugging
    ROS_INFO("Processing_xmlDB(%d,%d)", (int)(k), (int)(vecRawFileNm.size()));

    // making the filename  using stringstream, with the numbering rule
    stringstream strStreamFileName;
    strStreamFileName << cfgParam_.strXmlFileNmFwd;
    strStreamFileName << std::setfill('0') << std::setw(cfgParam_.nXmlFileNmDigit) << k;
    strStreamFileName << "." + cfgParam_.strXmlExt;

    // making the full file path
    string strXmlFile;
    strXmlFile = cfgParam_.strXmlFolderPath + strStreamFileName.str();

    // // assigning the raw image
    // Mat imgRaw = imread(vecRawFileNm[k]);

    // // checking bbox, maskImg-based
    // for (auto kk = 0; kk < cfgParam_.vecImgBboxDB[k].size(); kk++)
    // {
    //   for (auto kkk = 0; kkk < cfgParam_.vecImgBboxDB[k][kk].vecBbox.size(); kkk++)
    //   {
    //     // drawing results, 3.4.0 only
    //     Rect rectBbox;
    //     rectBbox = cfgParam_.vecImgBboxDB[k][kk].vecBbox[kkk];
    //     rectangle(imgRaw, rectBbox.tl(), rectBbox.br(), colorStat_.scalRed, 2);
    //   }
    // }

    // // checking bbox, polygon-based
    // for (auto kk = 0; kk < cfgParam_.vecPolygonBboxDB[k].size(); kk++)
    // {
    //   for (auto kkk = 0; kkk < cfgParam_.vecPolygonBboxDB[k][kk].vecBbox.size(); kkk++)
    //   {
    //     // drawing results, 3.4.0 only
    //     Rect rectBbox;
    //     rectBbox = cfgParam_.vecPolygonBboxDB[k][kk].vecBbox[kkk];
    //     rectangle(imgRaw, rectBbox.tl(), rectBbox.br(), colorStat_.scalLime, 2);
    //   }
    // }

    // // for debugging
    // imshow("raw_bbox", imgRaw);

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
    TiXmlText* txtElem41 = new TiXmlText(to_string(nWidth));
    pElem41->LinkEndChild(txtElem41);
    TiXmlElement* pElem42 = new TiXmlElement("height");
    TiXmlText* txtElem42 = new TiXmlText(to_string(nHeight));
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

    for (auto kk = 0; kk < cfgParam_.vecImgBboxDB[k].size(); kk++)
    {
      for (auto kkk = 0; kkk < cfgParam_.vecImgBboxDB[k][kk].vecBbox.size(); kkk++)
      {
        TiXmlElement* pElem5 = new TiXmlElement("object");
        TiXmlElement* pElem51 = new TiXmlElement("name");
        TiXmlText* txtElem51 = new TiXmlText(cfgParam_.vecImgBboxDB[k][kk].strLabel);
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

        Rect rectBbox;
        rectBbox = cfgParam_.vecImgBboxDB[k][kk].vecBbox[kkk];
        TiXmlElement* pElem55 = new TiXmlElement("bndbox");
        TiXmlElement* pElem551 = new TiXmlElement("xmin");
        TiXmlText* txtElem551 = new TiXmlText(to_string(rectBbox.tl().x));
        pElem551->LinkEndChild(txtElem551);
        TiXmlElement* pElem552 = new TiXmlElement("ymin");
        TiXmlText* txtElem552 = new TiXmlText(to_string(rectBbox.tl().y));
        pElem552->LinkEndChild(txtElem552);
        TiXmlElement* pElem553 = new TiXmlElement("xmax");
        TiXmlText* txtElem553 = new TiXmlText(to_string(rectBbox.br().x));
        pElem553->LinkEndChild(txtElem553);
        TiXmlElement* pElem554 = new TiXmlElement("ymax");
        TiXmlText* txtElem554 = new TiXmlText(to_string(rectBbox.br().y));
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
      }
    }

    // saving xml file
    docXml.SaveFile(strXmlFile);

    // calculating size flag
    bSizeCalcFlag = GenSizeCalcFlag(k, (int)(vecRawFileNm.size()));

    // // pausing and destroying all imshow result
    // waitKey(0);
  }

  // for debugging
  ROS_INFO(" ");

  return;
}

// get size calculation flag
bool CvtSeg2Bbox::GetSizeCalcFlag()
{
  return bSizeCalcFlag;
}

// generating size calculation flag for terminating converter
bool CvtSeg2Bbox::GenSizeCalcFlag(int nSize, int nTotal)
{
  bool bRes = false;
  if (fabs(nSize - nTotal) == 1.0f)
    bRes = true;
  return bRes;
}

// generating bbox data
vector<Rect> CvtSeg2Bbox::GenBboxData(Mat imgIn, Scalar color, int nThresh)
{
  // finding contours
  vector<vector<Point>> vecContours;
  vector<Vec4i> vecHierarchy;
  findContours(imgIn, vecContours, vecHierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

  // finding bounding boxes
  vector<vector<Point>> vecContoursPoly(vecContours.size());
  vector<vector<Point>> vecHull(vecContours.size());
  vector<Rect> vecRes(vecContours.size());
  Mat imgDrawing = Mat::zeros(imgIn.size(), CV_8UC3);

  if (vecContours.size() > 0)
  {
    // finding bounding boxes using approximated polygons
    for (size_t i = 0; i < vecContours.size(); i++)
    {
      approxPolyDP(vecContours[i], vecContoursPoly[i], nThresh, false);
      convexHull(vecContoursPoly[i], vecHull[i]);
      vecRes[i] = boundingRect(vecHull[i]);
    }

    // drawing bbox data for debugging
    // for (size_t i = 0; i < vecContours.size(); i++)
    // {
    //   drawContours(imgDrawing, vecHull, (int)(i), color);
    //   rectangle(imgDrawing, vecRes[i].tl(), vecRes[i].br(), color, 2);
    // }

    // for debugging
    // imshow("Contours", imgDrawing);
  }

  return vecRes;
}

// detecting canny edge data
Mat CvtSeg2Bbox::CannyEdge(Mat imgIn, int nThresh)
{
  Mat imgRes;
  Canny(imgIn, imgRes, nThresh, (nThresh * 2));
  return imgRes;
}

// generating filtered image using erode
Mat CvtSeg2Bbox::GenFilteredImg(Mat imgIn, int nHeight, int nWidth, int nAnno, int nTrial)
{
  // filtering image using the label info.
  Mat imgRes(nHeight, nWidth, CV_8UC1);
  uchar* reqData = imgIn.data;
  for (int y = 0; y < nHeight; y++)
  {
    uchar* resData = imgRes.data;
    for (int x = 0; x < nWidth; x++)
    {
      uchar b = reqData[y * nWidth * 3 + x * 3];
      uchar g = reqData[y * nWidth * 3 + x * 3 + 1];
      uchar r = reqData[y * nWidth * 3 + x * 3 + 2];

      if ((b == cfgParam_.vecAnnoDB[nAnno].nRGB[2]) && (g == cfgParam_.vecAnnoDB[nAnno].nRGB[1]) &&
          (r == cfgParam_.vecAnnoDB[nAnno].nRGB[0]))
      {
        resData[nWidth * y + x] = 255;
      }
      else
      {
        resData[nWidth * y + x] = 0;
      }
    }
  }

  // making smooth image using morphological filtering
  Mat mask = getStructuringElement(MORPH_RECT, Size(5, 5), Point(1, 1));
  morphologyEx(imgRes, imgRes, cv::MorphTypes::MORPH_OPEN, mask, Point(-1, -1), nTrial);

  // for debugging
  // imshow("filtered", imgRes);

  return imgRes;
}
