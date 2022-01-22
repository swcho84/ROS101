import numpy as np
from scipy import io
import cv2
import os

# assigning the res reference path (img, yolo_label)
resImgDstPath = os.path.join(os.path.expanduser('~'), "MoraiImgLabelDataHandler/img/")
resLabelYoloDstPath = os.path.join(os.path.expanduser('~'), "MoraiImgLabelDataHandler/yolo_label/")

# loading image files
imgFileList = os.listdir(resImgDstPath)
imgFileListJpgWext= [file for file in imgFileList if file.endswith(".png")]
imgFileListJpgWextSorted = sorted(imgFileListJpgWext)

# loading label files
labelFileList = os.listdir(resLabelYoloDstPath)
labelFileListTxtWext= [file for file in labelFileList if file.endswith(".txt")]
labelFileListTxtWextSorted = sorted(labelFileListTxtWext)

# showing the labeled result, example code
while True:
  imgSrc = cv2.imread(resImgDstPath + imgFileListJpgWextSorted[1], cv2.IMREAD_COLOR)
  imgDst = imgSrc
  imgDstHeight, imgDstWidth, imgDstChannel = imgDst.shape
  labelSrc = open(resLabelYoloDstPath + labelFileListTxtWextSorted[1], mode='r', encoding='utf-8')

  ptLts = []
  ptRbs = []
  for line in labelSrc:
    parseLineSrc = line.split()
    # print(parseLineSrc)   # ptCen_x, ptCen_y, bbox_width, bbox_height (normalized by using image size(width, height)
    ptLt = np.array([[int(float(parseLineSrc[1])*imgDstWidth) - int(float(parseLineSrc[3])*imgDstWidth*0.5)], [int(float(parseLineSrc[2])*imgDstHeight) - int(float(parseLineSrc[4])*imgDstHeight*0.5)]])
    ptRb = np.array([[ptLt[0][0] + int(float(parseLineSrc[3])*imgDstWidth)], [ptLt[1][0] + int(float(parseLineSrc[4])*imgDstHeight)]])
    ptLts.append(ptLt)
    ptRbs.append(ptRb)

  for j in range(len(ptLts)):
    cv2.rectangle(img=imgDst, pt1=(ptLts[j][0][0], ptLts[j][1][0]), pt2=(ptRbs[j][0][0], ptRbs[j][1][0]), color=(0,255,0), thickness=3, lineType=cv2.LINE_AA)

  cv2.imshow('imgDst', imgDst)
  cv2.waitKey(30)

cv2.destroyAllWindows()