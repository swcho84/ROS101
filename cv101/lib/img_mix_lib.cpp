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
  // assigning variables for browsing base images recursively
  vector<String> vecCvtBaseImgFileNm;
  glob("/home/drswcho/grabcut_insert/raw", vecCvtBaseImgFileNm, true);

  // assigning variables for browsing pet images recursively
  vector<String> vecCvtPetImgFileNm;  // cat and dog
  glob("/home/drswcho/grabcut_insert/cat_grabcut", vecCvtPetImgFileNm, true);

  // getting the base image
  imgBase_ = GetImgFromFile(vecCvtBaseImgFileNm[GenRandNum((int)(vecCvtBaseImgFileNm.size()))]);
  imgBaseSize_ = GetImgSize(imgBase_);

  // getting the target image (single type)
  imgTarget_ = GetImgFromFile(vecCvtPetImgFileNm[GenRandNum((int)(vecCvtPetImgFileNm.size()))]);
  imgTargetSize_ = GetImgSize(imgTarget_);

  // calculating the resized tareget image and mask
  float fWidthRatio = 0.1f;
  float fHeightRatio = 0.25f;
  float fInnerRatio = 0.1f;
  imgTargetResized_ = GetImgTargetResized(imgTarget_, imgTargetSize_, imgBaseSize_, fWidthRatio, fHeightRatio);
  imgTargetResizedSize_ = GetImgSize(imgTargetResized_);
  ptRndTargetResizedPos_ = GetRngPtTlForTargetResized(imgTargetResizedSize_, imgBaseSize_, fInnerRatio);
  vecSelectPixelMask_ = GetMaskInfo(imgTargetResized_, imgTargetResizedSize_);

  // calculating the mask, contour and mixed image
  imgForMix_ = GetImgMix(imgBase_, vecSelectPixelMask_, ptRndTargetResizedPos_, "black");
  imgForContour_ = GetImgMix(imgBase_, vecSelectPixelMask_, ptRndTargetResizedPos_, "contour");
  imgMixed_ = GetImgMix(imgForMix_, vecSelectPixelMask_, ptRndTargetResizedPos_, "rgb");

  // calculating the resized image
  Mat imgMixedResize;
  resize(imgMixed_, imgMixedResize, Size(640, 480));

  // calculating the resized bounding rectangle information
  vecRectTarget_ = GetTargetRect(imgForContour_);
  sort(vecRectTarget_.begin(), vecRectTarget_.end(), &sortArea);
  rectangle(imgMixedResize, vecRectTarget_[0].tl(), vecRectTarget_[0].br(), Scalar(0, 0, 255), 2, 8, 0);

  // for debugging
  imshow("imgMixedResize", imgMixedResize);

  waitKey(0);
}

// calculating the bounding rectangle w.r.t the resized target image
vector<Rect> ImgMix::GetTargetRect(Mat imgInput)
{
  Mat imgContourResize;
  resize(imgInput, imgContourResize, Size(640, 480));
  cvtColor(imgContourResize, imgContourResize, CV_BGR2GRAY);
  threshold(imgContourResize, imgContourResize, 250, 255, THRESH_BINARY);

  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  findContours(imgContourResize, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  vector<vector<Point> > contours_poly(contours.size());
  vector<Rect> result(contours.size());
  for (size_t i = 0; i < contours.size(); i++)
  {
    approxPolyDP(contours[i], contours_poly[i], 3, true);
    result[i] = boundingRect(contours_poly[i]);
  }

  return result;
}

// calculating the image w.r.t the string command
Mat ImgMix::GetImgMix(Mat imgInput, vector<SelectRGB> vecInput, Point ptInput, string strCmd)
{
  Mat result;
  imgInput.copyTo(result);
  vector<Point> vecSelectPtMask;

  if (strCmd == "contour")
    result = Mat::zeros(imgInput.size(), CV_8UC3);
  else
    imgInput.copyTo(result);

  for (unsigned int k = 0; k < vecInput.size(); k++)
  {
    Point ptMixRef;
    ptMixRef.x = ptInput.y + vecInput[k].ptPixel.y;
    ptMixRef.y = ptInput.x + vecInput[k].ptPixel.x;

    if (strCmd == "black")
    {
      result.at<Vec3b>(ptMixRef.x, ptMixRef.y)[0] = 0;
      result.at<Vec3b>(ptMixRef.x, ptMixRef.y)[1] = 0;
      result.at<Vec3b>(ptMixRef.x, ptMixRef.y)[2] = 0;
    }
    else if (strCmd == "rgb")
    {
      result.at<Vec3b>(ptMixRef.x, ptMixRef.y)[0] = vecInput[k].blue;
      result.at<Vec3b>(ptMixRef.x, ptMixRef.y)[1] = vecInput[k].green;
      result.at<Vec3b>(ptMixRef.x, ptMixRef.y)[2] = vecInput[k].red;
    }
    else if (strCmd == "contour")
    {
      result.at<Vec3b>(ptMixRef.x, ptMixRef.y)[0] = 255;
      result.at<Vec3b>(ptMixRef.x, ptMixRef.y)[1] = 255;
      result.at<Vec3b>(ptMixRef.x, ptMixRef.y)[2] = 255;
    }
    else
    {
    }
  }

  return result;
}

// calculating the mask information
vector<SelectRGB> ImgMix::GetMaskInfo(Mat imgTargetResized, ImgSize imgTargetResizedSize)
{
  vector<SelectRGB> result;
  for (unsigned int j = 0; j < imgTargetResizedSize.nHeight; j++)
  {
    uchar* ptInTargetResized = imgTargetResized.ptr<uchar>(j);
    for (unsigned int i = 0; i < imgTargetResizedSize.nWidth; i++)
    {
      uchar bTar = ptInTargetResized[i * 3 + 0];
      uchar gTar = ptInTargetResized[i * 3 + 1];
      uchar rTar = ptInTargetResized[i * 3 + 2];

      if (!((bTar > 245) && (gTar > 245) && (rTar > 245)))
      {
        SelectRGB temp;
        temp.ptPixel.x = i;
        temp.ptPixel.y = j;
        temp.blue = bTar;
        temp.green = gTar;
        temp.red = rTar;
        result.push_back(temp);
      }
    }
  }
  return result;
}

// calculating the random top-left point w.r.t the resized target
Point ImgMix::GetRngPtTlForTargetResized(ImgSize imgTargetResizedSize, ImgSize imgBaseSize, float fRatio)
{
  Point result;
  int nRngRangeHeight = (imgBaseSize.nHeight - imgTargetResizedSize.nHeight * 1.5f);
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> rngPtTlX(
      0, ((imgBaseSize.nWidth - (imgBaseSize.nWidth * fRatio)) - imgTargetResizedSize.nWidth));
  uniform_int_distribution<> rngPtTlY(
      (int)(imgBaseSize.nHeight * 0.35f),
      ((imgBaseSize.nHeight - (imgBaseSize.nHeight * fRatio)) - imgTargetResizedSize.nHeight));
  result.x = rngPtTlX(gen);
  result.y = rngPtTlY(gen);

  if (result.x > (imgBaseSize.nWidth - imgTargetResizedSize.nWidth))
    result.x = (imgBaseSize.nWidth - imgTargetResizedSize.nWidth);
  if (result.y > (imgBaseSize.nHeight - imgTargetResizedSize.nHeight))
    result.y = (imgBaseSize.nHeight - imgTargetResizedSize.nHeight);
  return result;
}

// generating the random number w.r.t the range of number of image
int ImgMix::GenRandNum(int nSize)
{
  int result;
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> rngRange(0, nSize - 1);
  result = rngRange(gen);
  return result;
}

// calculating the resized target image
Mat ImgMix::GetImgTargetResized(Mat imgTarget, ImgSize imgTargetSize, ImgSize imgBaseSize, float fWidthRatio,
                                float fHeightRatio)
{
  Mat result;
  if ((imgTargetSize.nWidth > ((int)(imgBaseSize.nWidth * fWidthRatio))) ||
      (imgTargetSize.nHeight > ((int)(imgBaseSize.nHeight * fHeightRatio))))
  {
    float fRatio = 0.5f;
    Size szResizeTarget;
    szResizeTarget.width = (int)(imgTargetSize.nWidth * fRatio);
    szResizeTarget.height = (int)(imgTargetSize.nHeight * fRatio);
    resize(imgTarget, result, szResizeTarget);
  }
  else
    imgTarget.copyTo(result);
  return result;
}

// getting the size information of the image
ImgSize ImgMix::GetImgSize(Mat imgInput)
{
  ImgSize result;
  result.nWidth = imgInput.size().width;
  result.nHeight = imgInput.size().height;
  return result;
}

// getting the image from file
Mat ImgMix::GetImgFromFile(string strBaseImgName)
{
  Mat result;
  result = imread(strBaseImgName, IMREAD_COLOR);
  return result;
}

bool ImgMix::sortArea(cv::Rect rect1, cv::Rect rect2)
{
  int nArea1 = rect1.width * rect1.height;
  int nArea2 = rect2.width * rect2.height;
  return (nArea1 > nArea2);
}