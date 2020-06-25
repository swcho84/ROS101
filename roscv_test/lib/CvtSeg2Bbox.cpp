#include "CvtSeg2Bbox.h"

using namespace std;
using namespace ros;
using namespace cv;

CvtSeg2Bbox::CvtSeg2Bbox(const ConfigParam& cfg) : cfgParam_(cfg)
{
}

CvtSeg2Bbox::~CvtSeg2Bbox()
{
}

void CvtSeg2Bbox::MainLoop()
{
  // assigning variables for browsing annotated images recursively
  vector<String> vecFileNm;
  vector<Mat> vecData;
  glob(cfgParam_.strAnnoFolderPath, vecFileNm, true);

  // browsing annotated images recursively
  for (size_t k = 0; k < vecFileNm.size(); ++k)
  {
    // assigning the raw image
    Mat imgRaw = imread(vecFileNm[k]);

    // for debugging
    imshow("annotated", imgRaw);

    // image width and height info.
    int nHeight = imgRaw.rows;
    int nWidth = imgRaw.cols;

    // generating bbox data w.r.t the labelDB
    cfgParam_.vecBboxDB.clear();
    for (auto i = 0; i < cfgParam_.vecAnnoDB.size(); i++)
    {
      // generating the filtered image using the label data
      Mat imgFiltered;
      imgFiltered = GenFilteredImg(imgRaw, nHeight, nWidth, i, cfgParam_.nMorphThresh);

      // detecting canny edge data
      Mat imgCanny;
      imgCanny = CannyEdge(imgFiltered, cfgParam_.nCannyThresh);

      // generating bounding box data
      vector<Rect> vecBbox;
      vecBbox = GenBboxData(imgCanny, Scalar(cfgParam_.vecAnnoDB[i].nRGB[2], cfgParam_.vecAnnoDB[i].nRGB[1],
                                             cfgParam_.vecAnnoDB[i].nRGB[0]),
                            cfgParam_.nPolyDPThesh);

      // saving bbox data
      if (vecBbox.size() > 0)
      {
        BboxDB tempBbox;
        tempBbox.vecBbox.clear();
        tempBbox.strLabel = cfgParam_.vecAnnoDB[i].strLabel;
        for (auto ii = 0; ii < vecBbox.size(); ii++)
          tempBbox.vecBbox.push_back(vecBbox[ii]);

        cfgParam_.vecBboxDB.push_back(tempBbox);
      }

      // temporary pause
      // waitKey(0);
    }

    // for debugging
    for (auto i = 0; i < cfgParam_.vecBboxDB.size(); i++)
    {
      ROS_INFO("[%s][%d]bbox:", cfgParam_.vecBboxDB[i].strLabel.c_str(), (int)(i));
      for (auto j = 0; j < cfgParam_.vecBboxDB[i].vecBbox.size(); j++)
      {
        ROS_INFO("[%d]:tl(%d,%d),br(%d,%d)", (int)(j), cfgParam_.vecBboxDB[i].vecBbox[j].tl().x,
                 cfgParam_.vecBboxDB[i].vecBbox[j].tl().y, cfgParam_.vecBboxDB[i].vecBbox[j].br().x,
                 cfgParam_.vecBboxDB[i].vecBbox[j].br().y);
      }
    }

    // pausing and destroying all imshow result
    waitKey(0);
    ROS_INFO(" ");
    destroyAllWindows();
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

  return imgRes;
}
