#include "img_crop_resize_lib.h"

using namespace std;
using namespace ros;
using namespace cv;

ImgCropResize::ImgCropResize()
{
}

ImgCropResize::~ImgCropResize()
{
}

void ImgCropResize::MainLoop()
{
  // assigning variables for browsing annotated images recursively
  vector<String> vecCvtImgFileNm;
  glob("/home/drswcho/need_to_crop", vecCvtImgFileNm, true);
  for (size_t i = 0; i < vecCvtImgFileNm.size(); i++)
  {
    // assigning the raw image
    Mat imgRaw = imread(vecCvtImgFileNm[i]);
    ROS_INFO("Process[%d]:%s", (int)(i), vecCvtImgFileNm[i].c_str());

    // setting ROI    
    Rect rectCrop;
    rectCrop.x = 0;
    rectCrop.y = 55;
    rectCrop.width = 640;
    rectCrop.height = 425;
    
    // releasing ROI info and resizing data
    Mat imgCrop(imgRaw, rectCrop);
    resize(imgCrop, imgCrop, Size(640, 480), 0.0, 0.0, CV_INTER_NN);

    // extracting the file name with the extension only
    istringstream ss(vecCvtImgFileNm[i]);
    string strBuffer;
    string strFileName;
    int nCounter = 0;
    while (getline(ss, strBuffer, '/'))
    {
      if (nCounter == 4)
      {
        strFileName = strBuffer;
        break;
      }
      else
        nCounter++;
    }

    // saving new image
    string strImgFilePath;
    strImgFilePath = "/home/drswcho/done_crop/" + strFileName;
    imwrite(strImgFilePath, imgCrop);

    if (abs((int)(i) - (vecCvtImgFileNm.size() - 1)) == 0)
      break;

    // for debugging
    // imshow("raw", imgRaw);
    // imshow("imgCrop", imgCrop);

    // pause
    // waitKey(0);
  }
}
