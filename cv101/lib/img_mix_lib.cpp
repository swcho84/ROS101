#include "img_mix_lib.h"

using namespace std;
using namespace ros;
using namespace cv;

ImgMix::ImgMix()
{
}

ImgMix::~ImgMix()
{
}

void ImgMix::MainLoop()
{
  Mat imgBase;
  string strBaseImgPath = "/home/drswcho/grabcut_insert/raw_img/etridb_ca_000000.png";
  imgBase = imread(strBaseImgPath, IMREAD_COLOR);
  int nBaseWidth = imgBase.size().width;
  int nBaseHeight = imgBase.size().height;
  imshow("imgBase", imgBase);

  Mat imgTarget;
  string strTargetImgPath = "/home/drswcho/grabcut_insert/cat_grabcut/grabcut_169.jpg";
  imgTarget = imread(strTargetImgPath, IMREAD_COLOR);
  int nTargetWidth = imgTarget.size().width;
  int nTargetHeight = imgTarget.size().height;

  Mat imgTargetResized;
  if ((nTargetWidth > (nBaseWidth * 0.25)) || (nTargetHeight > (nBaseHeight * 0.5)))
  {
    resize(imgTarget, imgTargetResized, Size(imgTarget.size().width * 0.5, imgTarget.size().height * 0.5));
  }
  else
  {
    imgTarget.copyTo(imgTargetResized);
  }

  int nTargetResizedWidth = imgTargetResized.size().width;
  int nTargetResizedHeight = imgTargetResized.size().height;
  int nRngRangeWidth = (nBaseWidth - nBaseWidth*0.1)  - nTargetResizedWidth;
  int nRngRangeHeight = (nBaseHeight - nBaseHeight*0.1)  - nTargetResizedHeight;

  RNG rngPtTlX(getTickCount());
  RNG rngPtTlY(getTickCount());
  Point ptMixedTl;
  ptMixedTl.y = rngPtTlX(nRngRangeWidth);
  ptMixedTl.x = rngPtTlX(nRngRangeHeight);

  ROS_INFO("ptMixedTl(x,y):(%d,%d)", ptMixedTl.x, ptMixedTl.y);
  imshow("imgTargetResized", imgTargetResized);

  Mat imgMask;
  imgTargetResized.copyTo(imgMask);
  int nMaskWidth = imgMask.size().width;
  int nMaskHeight = imgMask.size().height;
  vector<SelectRGB> vecSelectPixelMask;
  for (unsigned int j = 0; j < nMaskHeight; j++)
  {
    uchar* ptInTargetResized = imgTargetResized.ptr<uchar>(j);
    uchar* ptInMask = imgMask.ptr<uchar>(j);
    for (unsigned int i = 0; i < nMaskWidth; i++)
    {
      uchar bTar = ptInTargetResized[i * 3 + 0];
      uchar gTar = ptInTargetResized[i * 3 + 1];
      uchar rTar = ptInTargetResized[i * 3 + 2];

      if ((bTar > 245) && (gTar > 245) && (rTar > 245))
      {
        ptInMask[i * 3 + 0] = 0;
        ptInMask[i * 3 + 1] = 0;
        ptInMask[i * 3 + 2] = 0;
      }
      else
      {
        ptInMask[i * 3 + 0] = 255;
        ptInMask[i * 3 + 1] = 255;
        ptInMask[i * 3 + 2] = 255;

        SelectRGB temp;
        temp.ptPixel.x = i;
        temp.ptPixel.y = j;
        temp.blue = bTar;
        temp.green = gTar;
        temp.red = rTar;
        vecSelectPixelMask.push_back(temp);
      }
    }
  }

  imshow("imgMask", imgMask);

  Mat imgForMixResult;
  imgBase.copyTo(imgForMixResult);
  int nMixResultWidth = imgForMixResult.size().width;
  int nMixResultHeight = imgForMixResult.size().height;
  for (unsigned int k = 0; k < vecSelectPixelMask.size(); k++)
  {
    Point ptMixRef;
    ptMixRef.x = ptMixedTl.x + vecSelectPixelMask[k].ptPixel.y;
    ptMixRef.y = ptMixedTl.y + vecSelectPixelMask[k].ptPixel.x;

    imgForMixResult.at<Vec3b>(ptMixRef.x, ptMixRef.y)[0] = 0;
    imgForMixResult.at<Vec3b>(ptMixRef.x, ptMixRef.y)[1] = 0;
    imgForMixResult.at<Vec3b>(ptMixRef.x, ptMixRef.y)[2] = 0;
  }

  ROS_INFO("imgBase(width,height):(%d,%d)", nMixResultWidth, nMixResultHeight);
  ROS_INFO("imgTarget(width,height):(%d,%d)", nMaskWidth, nMaskHeight);

  Mat imgMixedResult;
  imgForMixResult.copyTo(imgMixedResult);
  int nMixedResultWidth = imgMixedResult.size().width;
  int nMixedResultHeight = imgMixedResult.size().height;
  for (unsigned int k = 0; k < vecSelectPixelMask.size(); k++)
  {
    Point ptMixRef;
    ptMixRef.x = ptMixedTl.x + vecSelectPixelMask[k].ptPixel.y;
    ptMixRef.y = ptMixedTl.y + vecSelectPixelMask[k].ptPixel.x;

    imgMixedResult.at<Vec3b>(ptMixRef.x, ptMixRef.y)[0] = vecSelectPixelMask[k].blue;
    imgMixedResult.at<Vec3b>(ptMixRef.x, ptMixRef.y)[1] = vecSelectPixelMask[k].green;
    imgMixedResult.at<Vec3b>(ptMixRef.x, ptMixRef.y)[2] = vecSelectPixelMask[k].red;
  }

  imshow("imgMixedResult", imgMixedResult);

  Mat imgMixedResize;
  resize(imgMixedResult, imgMixedResize, Size(640, 480));

  imshow("imgMixedResize", imgMixedResize);

  waitKey(0);
}