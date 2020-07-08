#include "CvtSeg2Bbox.h"

using namespace std;
using namespace ros;
using namespace cv;

CvtSeg2Bbox::CvtSeg2Bbox(const ConfigParam& cfg) : cfgParam_(cfg)
{
  // VGA size
  nHeight = 480;
  nWidth = 640;
}

CvtSeg2Bbox::~CvtSeg2Bbox()
{
}

void CvtSeg2Bbox::MainLoop()
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

  // assigning variables for browsing raw images with bbox result and saving bbox position data recursively
  vector<String> vecRawFileNm;
  glob(cfgParam_.strRawFolderPath, vecRawFileNm, true);

  // browsing raw images recursively
  for (size_t k = 0; k < vecRawFileNm.size(); k++)
  {
    // assigning the raw image
    Mat imgRaw = imread(vecRawFileNm[k]);

    // checking bbox, maskImg-based
    for (auto kk = 0; kk < cfgParam_.vecImgBboxDB[k].size(); kk++)
    {
      for (auto kkk = 0; kkk < cfgParam_.vecImgBboxDB[k][kk].vecBbox.size(); kkk++)
      {
        // drawing results, 3.4.0 only
        Rect rectBbox;
        rectBbox = cfgParam_.vecImgBboxDB[k][kk].vecBbox[kkk];
        rectangle(imgRaw, rectBbox.tl(), rectBbox.br(), colorStat_.scalRed, 2);
      }
    }

    // checking bbox, polygon-based
    for (auto kk = 0; kk < cfgParam_.vecPolygonBboxDB[k].size(); kk++)
    {
      for (auto kkk = 0; kkk < cfgParam_.vecPolygonBboxDB[k][kk].vecBbox.size(); kkk++)
      {
        // drawing results, 3.4.0 only
        Rect rectBbox;
        rectBbox = cfgParam_.vecPolygonBboxDB[k][kk].vecBbox[kkk];
        rectangle(imgRaw, rectBbox.tl(), rectBbox.br(), colorStat_.scalLime, 2);
      }
    }

    // for debugging
    imshow("raw_bbox", imgRaw);

    // pausing and destroying all imshow result
    waitKey(0);
  }

  return;
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
