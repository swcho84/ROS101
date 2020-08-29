#include "img_grabcut_insert_lib.h"

using namespace std;
using namespace ros;
using namespace cv;

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
  vector<String> vecCvtPetImgFileNm;   // cat and dog
  glob("/home/drswcho/grabcut_insert/dog", vecCvtPetImgFileNm, true);

  // setting mouse callback
  namedWindow("mouse_function", WINDOW_AUTOSIZE);
  setMouseCallback("mouse_function", ImgGrabCutInsert::CbMouseEvent, (void*)this);

  // image loop
  for (size_t i = 0; i < vecCvtPetImgFileNm.size(); i++)
  {
    // resetting the rectangle and line data
    ResetRectLineData();

    // receiving mouse callback and confirming the result
    while (1)
    {
      // assigning the raw image
      Mat imgRaw = imread(vecCvtPetImgFileNm[i]);
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

    // applying grabcut algorithm
    Mat imgObj;
    imgObj = GenCropImg(imgRawGrabCut_, rectROI_);

    // saving the result   
    // extracting the file name with the extension only
    istringstream ss(vecCvtPetImgFileNm[i]);
    string strBuffer;
    string strFileName;
    int nCounter = 0;
    while (getline(ss, strBuffer, '/'))
    {
      if (nCounter == 5) // file name address
      {
        strFileName = strBuffer;
        break;
      }
      else
        nCounter++;
    }

    // cat and dog
    string strGrabCutSavePath;
    string strGrabCutSaveFolterPath = "/home/drswcho/grabcut_insert/dog_grabcut/";
    strGrabCutSavePath = strGrabCutSaveFolterPath + "grabcut_" + strFileName;
    imwrite(strGrabCutSavePath, imgObj);

    // for debugging
    imshow("object", imgObj);

    waitKey(0);

    // destroying window
    destroyWindow("raw");
  }
}

// executing the grabcut algorithm for cropping object
Mat ImgGrabCutInsert::GenCropImg(Mat imgInput, Rect rectROI)
{
  Mat result;

  // grabcut algorithm
  Mat grabcut;            // segmentation result (4 possible values)
  Mat bgModel, fgModel;   // the models (internally used)
  int nIter = 10;         // iteration

  // GrabCut segmentation
  grabCut(imgInput,      // input image
          grabcut,              // segmentation result
          rectROI,            // rectangle containing foreground
          bgModel, fgModel,    // models
          10,                   // number of iterations
          GC_INIT_WITH_RECT);  // use rectangle

  // Get the pixels marked as likely foreground
  compare(grabcut, GC_PR_FGD, grabcut, CMP_EQ);

  // Generate output image
  Mat foreground(imgInput.size(), CV_8UC3, Scalar(255, 255, 255));
  imgInput.copyTo(foreground, grabcut);  // bg pixels not copied
  foreground.copyTo(result);
  return result;
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
