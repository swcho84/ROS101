#include "img_grabcut_insert_lib.h"

using namespace std;
using namespace ros;
using namespace cv;

RNG rng(543210);

ImgGrabCutInsert::ImgGrabCutInsert()
{
  // initializing the rectangle and line data
  ResetRectLineData();
}

ImgGrabCutInsert::~ImgGrabCutInsert()
{
}

void ImgGrabCutInsert::MainLoop()
{
  // assigning variables for browsing annotated images recursively
  vector<String> vecCvtCatImgFileNm;
  glob("/home/drswcho/grabcut_insert/cat", vecCvtCatImgFileNm, true);

  // setting mouse callback
  namedWindow("mouse_function", WINDOW_AUTOSIZE);
  setMouseCallback("mouse_function", ImgGrabCutInsert::CbMouseEvent, (void*)this);

  // image loop
  for (size_t i = 0; i < vecCvtCatImgFileNm.size(); i++)
  {
    // resetting the rectangle and line data
    ResetRectLineData();

    // receiving mouse callback and confirming the result
    while (1)
    {
      // assigning the raw image
      Mat imgRaw = imread(vecCvtCatImgFileNm[i]);
      cvtColor(imgRaw, imgRaw, CV_BGRA2BGR);
      imgRaw.copyTo(imgRawFunc_);
      imgRaw.copyTo(imgRawGrabCut_);

      // for grabcut algorithm
      rectangle(imgRaw, rectROI_, Scalar(0, 0, 255), 2, 8, 0);
      line(imgRaw, ptLineTl_, ptLineBr_, Scalar(255, 0, 0), 2, 8, 0);

      // for debugging
      imshow("raw", imgRaw);

      // breaking the while loop
      int key = waitKey(30);
      if (key == 'n')
        break;
    }

    // grabcut algorithm
    Mat result;            // segmentation result (4 possible values)
    Mat bgModel, fgModel;  // the models (internally used)

    // GrabCut segmentation
    grabCut(imgRawGrabCut_,      // input image
            result,              // segmentation result
            rectROI_,            // rectangle containing foreground
            bgModel, fgModel,    // models
            1,                   // number of iterations
            GC_INIT_WITH_RECT);  // use rectangle

    // Get the pixels marked as likely foreground
    compare(result, GC_PR_FGD, result, CMP_EQ);

    // Generate output image
    Mat foreground(imgRawGrabCut_.size(), CV_8UC3, Scalar(255, 255, 255));
    Mat background(imgRawGrabCut_.size(), CV_8UC3, Scalar(255, 255, 255));
    imgRawGrabCut_.copyTo(foreground, result);  // bg pixels not copied
    background = imgRawGrabCut_ - foreground;
    imshow("foreground", foreground);

    waitKey(0);

    // destroying window
    destroyWindow("raw");
  }
}

// assigning mouse callback, c++ class style
void ImgGrabCutInsert::CbMouseEvent(int event, int x, int y, int flags, void* param)
{
  ImgGrabCutInsert* thiz = static_cast<ImgGrabCutInsert*>(param);
  thiz->mouseClick(event, x, y, flags, thiz->imgRawFunc_);
}

// setting mouse events on the designated window
void ImgGrabCutInsert::mouseClick(int event, int x, int y, int flags, Mat img)
{
  switch (event)
  {
    case EVENT_MOUSEMOVE:
    {
      if ((bLtMousePressed_ == true) && (bMdMousePressed_ == false))
      {
        nCurrRectX_ = x;
        nCurrRectY_ = y;
        rectangle(img, Point(nInitRectX_, nInitRectY_), Point(nCurrRectX_, nCurrRectY_), Scalar(0, 0, 255), 2, 8, 0);
      }
      else if ((bLtMousePressed_ == false) && (bMdMousePressed_ == true))
      {
        nCurrLineX_ = x;
        nCurrLineY_ = y;
        line(img, Point(nInitLineX_, nInitLineY_), Point(nCurrLineX_, nCurrLineY_), Scalar(255, 0, 0), 2, 8, 0);
      }
      else
      {
      }
      break;
    }
    case EVENT_LBUTTONDOWN:
    {
      bLtMousePressed_ = true;
      nInitRectX_ = x;
      nInitRectY_ = y;
      break;
    }
    case EVENT_LBUTTONUP:
    {
      bLtMousePressed_ = false;
      rectROI_.x = nInitRectX_;
      rectROI_.y = nInitRectY_;
      rectROI_.width = nCurrRectX_ - nInitRectX_;
      rectROI_.height = nCurrRectY_ - nInitRectY_;

      rectangle(img, rectROI_, Scalar(0, 0, 255), 2, 8, 0);
      break;
    }
    case EVENT_MBUTTONDOWN:  // set GC_PR_BGD(GC_PR_FGD) labels
    {
      bMdMousePressed_ = true;
      nInitLineX_ = x;
      nInitLineY_ = y;
      break;
    }
    case EVENT_MBUTTONUP:
    {
      bMdMousePressed_ = false;
      ptLineTl_.x = nInitLineX_;
      ptLineTl_.y = nInitLineY_;
      ptLineBr_.x = nCurrLineX_;
      ptLineBr_.y = nCurrLineY_;
      line(img, ptLineTl_, ptLineBr_, Scalar(255, 0, 0), 2, 8, 0);
      break;
    }
  }

  // for debugging
  imshow("mouse_function", img);
}

// resetting the rectangle and line data
void ImgGrabCutInsert::ResetRectLineData()
{
  bLtMousePressed_ = false;
  bMdMousePressed_ = false;
  nInitRectX_ = 0;
  nInitRectY_ = 0;
  nCurrRectX_ = 0;
  nCurrRectY_ = 0;

  nInitLineX_ = 0;
  nInitLineY_ = 0;
  nCurrLineX_ = 0;
  nCurrLineY_ = 0;

  rectROI_.x = nInitRectX_;
  rectROI_.y = nInitRectY_;
  rectROI_.width = nCurrRectX_ - nInitRectX_;
  rectROI_.height = nCurrRectY_ - nInitRectY_;

  ptLineTl_.x = nInitLineX_;
  ptLineTl_.y = nInitLineY_;
  ptLineBr_.x = nCurrLineX_;
  ptLineBr_.y = nCurrLineY_;
}
