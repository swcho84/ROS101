#include "imgproc_lane_vehicle.h"

using namespace std;
using namespace ros;
using namespace cv;


ImgProc101::ImgProc101()
{
  if (!ReadRosParams())
  {
    ROS_ERROR("Wrong params!! Please check the parameter sheet..");
    exit(-1);
  }

  strPkgEnv_ = package::getPath("imgproc101");
  strLaneImgFile_ = strPkgEnv_ + strImgFolder_ + strLaneImgFile_;
  strVehicleImgFile_ = strPkgEnv_ + strImgFolder_ + strVehicleImgFile_;

  LDimg_ = cvLoadImage(strLaneImgFile_.c_str(), 1);
  VDimg_ = cvLoadImage(strVehicleImgFile_.c_str(), 1);
  
  cvNamedWindow("Lane:RawImg", 1);
  cvNamedWindow("Vehicle:RawImg", 1);

  cvShowImage("Lane:RawImg", LDimg_);
  cvShowImage("Vehicle:RawImg", VDimg_);

  ROS_INFO("load imgs..");
}

ImgProc101::~ImgProc101()
{
}

void ImgProc101::MainLoop()
{
  LaneDetection((unsigned char *)LDimg_->imageData, LDimg_->height, LDimg_->width);
  VehicleDetection((unsigned char *)VDimg_->imageData, VDimg_->height, VDimg_->width);
}

void ImgProc101::VehicleDetection(unsigned char *RGBimg, int height, int width)
{
	// color to gray
	unsigned char *input_img, *shadow_img, *edge_img, *merge_img;
	int x, y;
	input_img = (unsigned char *)calloc(sizeof(unsigned char), height*width);
	shadow_img = (unsigned char *)calloc(sizeof(unsigned char), height*width);
	edge_img = (unsigned char *)calloc(sizeof(unsigned char), height*width);
	merge_img = (unsigned char *)calloc(sizeof(unsigned char), height*width);

	IplImage *GrayImg, *ShadowImg, *EdgeImg, *MergeImg, *ShowImg;

	GrayImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	ShadowImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	EdgeImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	MergeImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	ShowImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);

	for (y = 1; y < (height); y++)
	{
		for (x = 1; x < (width); x++)
		{
			unsigned char R = RGBimg[(y*width + x) * 3 + 0];
			unsigned char G = RGBimg[(y*width + x) * 3 + 1];
			unsigned char B = RGBimg[(y*width + x) * 3 + 2];
			input_img[y*width + x] = (R + B + G) / 3.0;

			GrayImg->imageData[y*width + x] = input_img[y*width + x];
			ShadowImg->imageData[y*width + x] = input_img[y*width + x];
			MergeImg->imageData[y*width + x] = input_img[y*width + x];
		}
	}

	cvNamedWindow("GrayImgVD", 1);
	cvShowImage("GrayImgVD", GrayImg);

	// shadow image
	for (y = height / 3 * 2; y < height; y++) 
	{
		for (x = 0; x < width; x++) 
		{
			if (input_img[y*width + x] < 70) 
			{
				shadow_img[y*width + x] = 1;
				ShadowImg->imageData[y*width + x] = 255;
			}
			else 
			{
				shadow_img[y*width + x] = 0;
			}
			
		}
	}

	cvNamedWindow("ShadowImgVD", 1);
	cvShowImage("ShadowImgVD", ShadowImg);

	// edge image
	for (y = height / 3 * 2; y < height; y++)
	{
		for (x = 1; x < (width - 1); x++) 
		{
			int Sobel_Value = input_img[(y + 1)*width + (x - 1)] - input_img[(y - 1)*width + (x - 1)]
								+ 2 * input_img[(y + 1)*width + x] - 2 * input_img[(y - 1)*width + x]
								+ input_img[(y + 1)*width + (x + 1)] - input_img[(y - 1)*width + (x + 1)];

			if (Sobel_Value > 127)
			{
				edge_img[y*width + x] = 255;
			}
			else if (Sobel_Value < -127)
			{
				edge_img[y*width + x] = 0;
			}
			else
			{
				edge_img[y*width + x] = Sobel_Value + 127;
			}

			EdgeImg->imageData[y*width + x] = edge_img[y*width + x];
		}
	}

	cvNamedWindow("EdgeImgVD", 1);
	cvShowImage("EdgeImgVD", EdgeImg);

	// Merge Shadow and Edge Image
	for (y = height / 3 * 2; y < height; y++) 
	{
		for (x = 0; x < width; x++) 
		{
			if (shadow_img[y*width + x] == 1 && edge_img[y*width + x] > (90+127)) 
			{
				merge_img[y*width + x] = 1;
				MergeImg->imageData[y*width + x] = 255;
			}
			else 
			{
				merge_img[y*width + x] = 0;
			}
		}
	}
	cvNamedWindow("MergeImgVD", 1);
	cvShowImage("MergeImgVD", MergeImg);

	// Linked 
	int LinkEdge_SX[5000] = { -1, }, LinkEdge_SY[5000] = { -1 }, LinkEdge_EX[5000] = { -1 }, LinkEdge_EY[5000] = { -1 }, LinkEdge_NUM[5000] = { 0, };
	int LinkedEdgeNum = -1;
	for (y = height / 3 * 2; y < height; y++) 
	{
		for (x = 0; x < width; x++) 
		{
			if (merge_img[y*width + x] == 1) 
			{
				LinkEdge_SX[LinkedEdgeNum + 1] = x; 
				LinkEdge_SY[LinkedEdgeNum + 1] = y; 
				LinkEdge_EX[LinkedEdgeNum + 1] = x;
				LinkEdge_EY[LinkedEdgeNum + 1] = y; 
				LinkEdge_NUM[LinkedEdgeNum + 1] = 1;
				while (x < width) 
				{
					x += 1;
					if (merge_img[y*width + x] == 1) 
					{
						LinkEdge_EX[LinkedEdgeNum + 1] = x; 
						LinkEdge_EY[LinkedEdgeNum + 1] = y;
						LinkEdge_NUM[LinkedEdgeNum + 1] += 1;
					}
					else if (merge_img[(y + 1)*width + x] == 1) 
					{
						LinkEdge_EX[LinkedEdgeNum + 1] = x; 
						LinkEdge_EY[LinkedEdgeNum + 1] = y;
						LinkEdge_NUM[LinkedEdgeNum + 1] += 1;
					}
					else if (merge_img[(y - 1)*width + x] == 1) 
					{
						LinkEdge_EX[LinkedEdgeNum + 1] = x; 
						LinkEdge_EY[LinkedEdgeNum + 1] = y;
						LinkEdge_NUM[LinkedEdgeNum + 1] += 1;
					}
					else {
						LinkedEdgeNum += 1;
						break;
					}
				}
			}
		}
	}

	for (y = 0; y < (height); y++)
	{
		for (x = 0; x < (width); x++)
		{
			ShowImg->imageData[(y*width + x) * 3 + 0] = RGBimg[(y*width + x) * 3 + 0];
			ShowImg->imageData[(y*width + x) * 3 + 1] = RGBimg[(y*width + x) * 3 + 1];
			ShowImg->imageData[(y*width + x) * 3 + 2] = RGBimg[(y*width + x) * 3 + 2];
		}
	}

	int k; int sty; int endy; int i, j;
	for (k = 1;k<LinkedEdgeNum;k++)
	{
		if (LinkEdge_NUM[k] > 45)
		{
			if (LinkEdge_SY[k] > LinkEdge_EY[k])
			{
				sty = LinkEdge_EY[k];
				endy = LinkEdge_SY[k];
			}
			else
			{
				sty = LinkEdge_SY[k];
				endy = LinkEdge_EY[k];
			}

			for (i = sty ;i<=endy;i++)
			{
				//for (j = linkededge(k).sx : 1 : linkededge(k).ex)
				for(j=LinkEdge_SX[k];j<LinkEdge_EX[k];j++)
				{
					ShowImg->imageData[(i*width + j) * 3 + 0] = 0;
					ShowImg->imageData[(i*width + j) * 3 + 1] = 255;
					ShowImg->imageData[(i*width + j) * 3 + 2] = 0;
				}
			}
		}
	}

	cvNamedWindow("MergeResultVD1", 1);
	cvShowImage("MergeResultVD1", ShowImg);

	int n;
	// remove 1 
	for (k = 0; k < LinkedEdgeNum; k++) 
	{
		for (n = k+1; n < LinkedEdgeNum; n++) 
		{
			if (LinkEdge_NUM[k] > 0 && LinkEdge_NUM[n] > 0)
			{
				if (LinkEdge_SX[n] >= LinkEdge_SX[k] && LinkEdge_SY[n] >= LinkEdge_SY[k]
					&& LinkEdge_EX[n] <= LinkEdge_EX[k] && LinkEdge_EY[n] <= LinkEdge_EY[k])
				{
					LinkEdge_SX[n] = -1;
					LinkEdge_SY[n] = -1;
					LinkEdge_EX[n] = -1;
					LinkEdge_EY[n] = -1;
					LinkEdge_NUM[n] = 0;
				}
				else if(LinkEdge_SX[n] >= LinkEdge_SX[k] && LinkEdge_SY[n] >= LinkEdge_SY[k]
					&& LinkEdge_EX[n] <= LinkEdge_EX[k] && LinkEdge_EY[n] <= LinkEdge_EY[k])
				{
					LinkEdge_SX[k] = -1;
					LinkEdge_SY[k] = -1;
					LinkEdge_EX[k] = -1;
					LinkEdge_EY[k] = -1;
					LinkEdge_NUM[k] = 0;
				}
			}
		}
	}
	for (y = 0; y < (height); y++)
	{
		for (x = 0; x < (width); x++)
		{
			ShowImg->imageData[(y*width + x) * 3 + 0] = RGBimg[(y*width + x) * 3 + 0];
			ShowImg->imageData[(y*width + x) * 3 + 1] = RGBimg[(y*width + x) * 3 + 1];
			ShowImg->imageData[(y*width + x) * 3 + 2] = RGBimg[(y*width + x) * 3 + 2];
		}
	}

	for (k = 1; k < LinkedEdgeNum; k++)
	{
		if (LinkEdge_NUM[k] > 45)
		{
			if (LinkEdge_SY[k] > LinkEdge_EY[k])
			{
				sty = LinkEdge_EY[k];
				endy = LinkEdge_SY[k];
			}
			else
			{
				sty = LinkEdge_SY[k];
				endy = LinkEdge_EY[k];
			}

			//for (i = sty; i <= endy; i++)
			{
				int LGN = LinkEdge_EX[k] - LinkEdge_SX[k];

				for (j = LinkEdge_SX[k]; j < LinkEdge_EX[k]; j++)
				{
					ShowImg->imageData[(endy*width + j) * 3 + 0] = 0;
					ShowImg->imageData[(endy*width + j) * 3 + 1] = 255;
					ShowImg->imageData[(endy*width + j) * 3 + 2] = 0;
				}

				for (j = LinkEdge_SX[k]; j < LinkEdge_EX[k]; j++)
				{
					ShowImg->imageData[((endy - LGN)*width + j) * 3 + 0] = 0;
					ShowImg->imageData[((endy - LGN)*width + j) * 3 + 1] = 255;
					ShowImg->imageData[((endy - LGN)*width + j) * 3 + 2] = 0;
				}

				for (i = endy-LGN; i < endy; i++)
				{
					ShowImg->imageData[(i*width + LinkEdge_SX[k]) * 3 + 0] = 0;
					ShowImg->imageData[(i*width + LinkEdge_SX[k]) * 3 + 1] = 255;
					ShowImg->imageData[(i*width + LinkEdge_SX[k]) * 3 + 2] = 0;
				}

				for (i = endy - LGN; i < endy; i++)
				{
					ShowImg->imageData[(i*width + LinkEdge_EX[k]) * 3 + 0] = 0;
					ShowImg->imageData[(i*width + LinkEdge_EX[k]) * 3 + 1] = 255;
					ShowImg->imageData[(i*width + LinkEdge_EX[k]) * 3 + 2] = 0;
				}
			}
		}
	}

	cvNamedWindow("Remove 1", 1);
	cvShowImage("Remove 1", ShowImg);
	
	//remove 2
	for (k = 0; k < LinkedEdgeNum; k++) 
	{
		for (n = 0; n < LinkedEdgeNum; n++) 
		{
			if (LinkEdge_NUM[k] > 0 && LinkEdge_NUM[n] > 0 && k != n) 
			{
				if (LinkEdge_SX[n] > LinkEdge_SX[k] && LinkEdge_SX[n] < LinkEdge_EX[k]) 
				{
					if ((LinkEdge_SY[n] + 1) == LinkEdge_SY[k] || (LinkEdge_SY[n] - 1) == LinkEdge_SY[k] || LinkEdge_SY[n] == LinkEdge_SY[k]
						|| (LinkEdge_EY[n]) == LinkEdge_EY[k] || (LinkEdge_EY[n] - 1) == LinkEdge_EY[k] || (LinkEdge_EY[n] +1) == LinkEdge_EY[k]) 
					{
						if (LinkEdge_EX[k] > LinkEdge_EX[n]) 
						{
							LinkEdge_SX[n] = -1; 
							LinkEdge_SY[n] = -1;
							LinkEdge_EX[n] = -1; 
							LinkEdge_EY[n] = -1; 
							LinkEdge_NUM[n] = 0;
						}
						else 
						{
							LinkEdge_NUM[k] += abs(LinkEdge_EY[n] - LinkEdge_EY[k]);
							LinkEdge_EX[k] = LinkEdge_EX[n];
							LinkEdge_EY[k] = LinkEdge_EY[n];
							LinkEdge_SX[n] = -1; 
							LinkEdge_SY[n] = -1;
							LinkEdge_EX[n] = -1; 
							LinkEdge_EY[n] = -1; 
							LinkEdge_NUM[n] = 0;
						}
					}
				}
			}
		}
	}

	for (y = 0; y < (height); y++)
	{
		for (x = 0; x < (width); x++)
		{
			ShowImg->imageData[(y*width + x) * 3 + 0] = RGBimg[(y*width + x) * 3 + 0];
			ShowImg->imageData[(y*width + x) * 3 + 1] = RGBimg[(y*width + x) * 3 + 1];
			ShowImg->imageData[(y*width + x) * 3 + 2] = RGBimg[(y*width + x) * 3 + 2];
		}
	}

	for (k = 1; k < LinkedEdgeNum; k++)
	{
		if (LinkEdge_NUM[k] > 45)
		{
			if (LinkEdge_SY[k] > LinkEdge_EY[k])
			{
				sty = LinkEdge_EY[k];
				endy = LinkEdge_SY[k];
			}
			else
			{
				sty = LinkEdge_SY[k];
				endy = LinkEdge_EY[k];
			}

			//for (i = sty; i <= endy; i++)
			{
				int LGN = LinkEdge_EX[k] - LinkEdge_SX[k];

				for (j = LinkEdge_SX[k]; j < LinkEdge_EX[k]; j++)
				{
					ShowImg->imageData[(endy*width + j) * 3 + 0] = 0;
					ShowImg->imageData[(endy*width + j) * 3 + 1] = 255;
					ShowImg->imageData[(endy*width + j) * 3 + 2] = 0;
				}

				for (j = LinkEdge_SX[k]; j < LinkEdge_EX[k]; j++)
				{
					ShowImg->imageData[((endy - LGN)*width + j) * 3 + 0] = 0;
					ShowImg->imageData[((endy - LGN)*width + j) * 3 + 1] = 255;
					ShowImg->imageData[((endy - LGN)*width + j) * 3 + 2] = 0;
				}

				for (i = endy - LGN; i < endy; i++)
				{
					ShowImg->imageData[(i*width + LinkEdge_SX[k]) * 3 + 0] = 0;
					ShowImg->imageData[(i*width + LinkEdge_SX[k]) * 3 + 1] = 255;
					ShowImg->imageData[(i*width + LinkEdge_SX[k]) * 3 + 2] = 0;
				}

				for (i = endy - LGN; i < endy; i++)
				{
					ShowImg->imageData[(i*width + LinkEdge_EX[k]) * 3 + 0] = 0;
					ShowImg->imageData[(i*width + LinkEdge_EX[k]) * 3 + 1] = 255;
					ShowImg->imageData[(i*width + LinkEdge_EX[k]) * 3 + 2] = 0;
				}
			}
		}
	}

	cvNamedWindow("Remove 2", 1);
	cvShowImage("Remove 2", ShowImg);

}

void ImgProc101::LaneDetection(unsigned char *RGBimg, int height, int width)
{
	// color to gray
	unsigned char *input_img;
	unsigned char *edge_img;
	unsigned char *binary_img;
	int x, y;
	input_img = (unsigned char *)calloc(sizeof(unsigned char), height*width);
	edge_img = (unsigned char *)calloc(sizeof(unsigned char), height*width);
	binary_img = (unsigned char *)calloc(sizeof(unsigned char), height*width);

	IplImage *GrayImg, *EdgeImg, *BImg;

	GrayImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	EdgeImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	BImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

	for (y = 1; y < (height); y++) 
	{
		for (x = 1; x < (width); x++) 
		{
			unsigned char R = RGBimg[(y*width + x) * 3 + 0];
			unsigned char G = RGBimg[(y*width + x) * 3 + 1];
			unsigned char B = RGBimg[(y*width + x) * 3 + 2];
			input_img[y*width + x] = (R + B + G) / 3.0;

			GrayImg->imageData[y*width + x] = input_img[y*width + x];
		}
	}

	cvNamedWindow("GrayImgLD", 1);
	cvShowImage("GrayImgLD", GrayImg);

	// edge image 
	for (y = 0; y < height; y++) 
	{
		for (x = 1; x < (width - 1); x++) 
		{
			edge_img[y*width + x] = input_img[y*width + x] - input_img[y*width + (x - 1)];
			EdgeImg->imageData[y*width + x] = edge_img[y*width + x]+127;
		}
	}

	cvNamedWindow("EdgeImgLD_Sub", 1);
	cvShowImage("EdgeImgLD_Sub", EdgeImg);

	for (y = 1; y < (height - 1); y++) 
	{
		for (x = 1; x < (width - 1); x++) 
		{
			int Sobel_Value = input_img[(y + 1)*width + (x + 1)] - input_img[(y + 1)*width + (x - 1)]
				+ 2 * input_img[y*width + (x + 1)] - 2 * input_img[y*width + (x - 1)]
				+ input_img[(y - 1)*width + (x + 1)] - input_img[(y - 1)*width + (x - 1)];

			if(Sobel_Value>127)
			{
				edge_img[y*width + x] = 255;
			}
			else if(Sobel_Value<-127)
			{
				edge_img[y*width + x] = 0;
			}
			else
			{
				edge_img[y*width + x] = Sobel_Value+127;
			}

			EdgeImg->imageData[y*width + x] = edge_img[y*width + x];
		}
	}

	cvNamedWindow("EdgeImgLD_Sobel", 1);
	cvShowImage("EdgeImgLD_Sobel", EdgeImg);

	// binarization image
	for (y = (height / 3 * 2) ; y < (height - 1); y++)
	{
		for (x = 1; x < (width / 2 - 1); x++) 
		{
			if (edge_img[y*width + x] < (-100+127))
				binary_img[y*width + x] = 1;
			else
				binary_img[y*width + x] = 0;

			BImg->imageData[y*width + x] = binary_img[y*width + x]*255;
		}
		for (x = (width / 2); x < (width - 1); x++) 
		{
			if (edge_img[y*width + x] >(100 + 127))
				binary_img[y*width + x] = 1;
			else
				binary_img[y*width + x] = 0;
			BImg->imageData[y*width + x] = binary_img[y*width + x] * 255;
		}
	}

	cvNamedWindow("BImgLD", 1);
	cvShowImage("BImgLD", BImg);

	// hough transform 
	double hough_height =
		sqrtf(width*width + height*height) / 2.0;
	int CenterX = width / 2;
	int CenterY = height / 2;

	int acm_width = 180;
	int acm_height = (int)(hough_height * 2);
	int acm_size = acm_width*acm_height;

	int *acmm_left = (int *)malloc(sizeof(int)* acm_size);
	int *acmm_right = (int *)malloc(sizeof(int)* acm_size);
	memset(acmm_left, 0, sizeof(int)*acm_size);
	memset(acmm_right, 0, sizeof(int)*acm_size);

	double table_sin[180], table_cos[180];
	double DEG2RAD = CV_PI/ 180;
	int angle;

	for(angle = 0;angle<180;angle++) 
	{
		table_sin[angle] = sin(angle*DEG2RAD);
		table_cos[angle] = cos(angle*DEG2RAD);
	}

	for(y = height / 3 * 2;y< height;y++) 
	{
		for(x = 0;x<width/2;x++) 
		{
			if(binary_img[y*width + x] == 1) 
			{
				for(angle = 0;angle< 180; angle++) 
				{
					int r = (x - CenterX)*table_cos[angle]+ (y - CenterY)*table_sin[angle];
					r = r+ hough_height;
					acmm_left[r*acm_width+angle] += 1;
				}
			}
		}
		for(x=width/2;x<width;x++) 
		{
			if(binary_img[y*width + x] == 1) 
			{
				for(angle= 0;angle< 180;angle++) 
				{
					int r = (x - CenterX)*table_cos[angle] + (y - CenterY)*table_sin[angle];
					r = r + hough_height;
					acmm_right[r*acm_width+angle] += 1;
				}
			}
		}
	}

	IplImage *HoughLeftImg, *HoughRightImg;

	HoughLeftImg = cvCreateImage(cvSize(acm_width, acm_height), IPL_DEPTH_8U, 1);
	HoughRightImg = cvCreateImage(cvSize(acm_width, acm_height), IPL_DEPTH_8U, 1);

	for (y = 0; y < acm_height; y++)
	{
		for (x = 0; x < acm_width; x++)
		{
			HoughLeftImg->imageData[y*acm_width + x] = acmm_left[y*acm_width + x];
			HoughRightImg->imageData[y*acm_width + x] = acmm_right[y*acm_width + x];
		}
	}

	cvNamedWindow("HougLeftImg", 1);
	cvShowImage("HoughLeftImg", HoughLeftImg);
	cvNamedWindow("HougRightImg", 1);
	cvShowImage("HoughRightImg", HoughRightImg);

	int rho = 0;
	int max_angle_left = -0, max_rho_left = 0, max_value_left = 0;
	int max_angle_right = -0, max_rho_right = 0, max_value_right = 0;

	for(angle = 0;angle<acm_width;angle++)
	{
		for(rho=1;rho<acm_height;rho++) 
		{
			if (max_value_left < acmm_left[rho*acm_width+ angle]) 
			{
				max_angle_left = angle;
				max_rho_left = rho;
				max_value_left = acmm_left[rho*acm_width+ angle];
			}
			if (max_value_right < acmm_right[rho*acm_width+ angle]) 
			{
				max_angle_right = angle;
				max_rho_right = rho;
				max_value_right = acmm_right[rho*acm_width+ angle];
			}
		}
	}
	for (x = 0;x < width / 2; x++) 
	{
		y = (max_rho_left - hough_height - (x - CenterX)* table_cos[max_angle_left])/ table_sin[max_angle_left];
		y += CenterY;
		if (y > 0 && y < height) 
		{
			RGBimg[(y*width + x) * 3 + 2] = 255;
			RGBimg[(y*width + x) * 3 + 1] = 0;
			RGBimg[(y*width + x) * 3 + 0] = 0;
		}
	}

	for (x = width / 2; x < width; x++) 
	{
		y = (max_rho_right - hough_height - (x - CenterX) * table_cos[max_angle_right]) / table_sin[max_angle_right];
		y += CenterY;
		if (y > 0 && y < height) {
			RGBimg[(y*width + x) * 3 + 2] = 255;
			RGBimg[(y*width + x) * 3 + 1] = 0;
			RGBimg[(y*width + x) * 3 + 0] = 0;
		}
	}
	IplImage *LDResultImg;

	LDResultImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			LDResultImg->imageData[(y*width + x) * 3 + 0] = RGBimg[(y*width + x) * 3 + 0];
			LDResultImg->imageData[(y*width + x) * 3 + 1] = RGBimg[(y*width + x) * 3 + 1];
			LDResultImg->imageData[(y*width + x) * 3 + 2] = RGBimg[(y*width + x) * 3 + 2];
		}
	}

	cvNamedWindow("LDResult", 1);
	cvShowImage("LDResult", LDResultImg);
}

// reading rosparams
bool ImgProc101::ReadRosParams()
{
  try
  {
    NodeHandle nh("");
    ReadRosParam(nh, "/imgproc101/imgFolder", strImgFolder_);
    ReadRosParam(nh, "/imgproc101/LaneImg", strLaneImgFile_);
    ReadRosParam(nh, "/imgproc101/VehicleImg", strVehicleImgFile_);
  }
  catch (RosParamNotFoundException& ex)
  {
    ROS_ERROR("Failed to read param at key \"%s\"", ex.key.c_str());
    return false;
  }

  return true;
}
void ImgProc101::ReadRosParam(ros::NodeHandle& nh, const string& key, float& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void ImgProc101::ReadRosParam(ros::NodeHandle& nh, const string& key, double& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void ImgProc101::ReadRosParam(ros::NodeHandle& nh, const string& key, bool& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void ImgProc101::ReadRosParam(ros::NodeHandle& nh, const string& key, int32_t& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void ImgProc101::ReadRosParam(ros::NodeHandle& nh, const string& key, string& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
  if (val.empty())
    throw RosParamNotFoundException(key);
}