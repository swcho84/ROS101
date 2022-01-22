import numpy as np
import os
import shutil
import cv2
import scipy as io

# assigning the forward file name as string
fileResFwdName = "etridb_ca_"

# assigning the digit for file name
fileBwdNumDigit = 6

# assigning the file number offset
fileOffset = 9958

# assigning the label info.
labelInfo = ["person", "four_wheel_vehicle", "two_wheel_vehicle", "stroller", "pet", "post_office_symbol", "postman_vest"]

# assigning the VGA size, width
refVgaWidth = 640
refVgaHeight = 480

# converting the string label from string MoraiSim to TF usecase
def CvtLabelStrInfo(inStr):
  if inStr == "Pedestrian":
    resStr = labelInfo[0]
  elif inStr == "Vehicle":
    resStr = labelInfo[1]
  elif inStr == "SurroundVehicle" or inStr == "Two_Wheel_Vehicle":
    resStr = labelInfo[2]
  elif inStr == "Stroller" or inStr == "MultiEgoVehicle":
    resStr = labelInfo[3]
  elif inStr == "Obstacle":
    resStr = labelInfo[4]
  return resStr

# converting the int label from string label for YOLO
def CvtLabelIntInfo(inStr):
  for i in range(len(labelInfo)):
    if labelInfo[i] == inStr:
      resIntLabel = i
  return resIntLabel

# selecting the src reference path
basicImgSrcPath = os.path.join(os.path.expanduser('~'), "MoraiLauncher_Lin/MoraiLauncher_Lin_Data/SaveFile/SensorData/CAMERA_1/")
basicLabelSrcPath = os.path.join(os.path.expanduser('~'), "MoraiLauncher_Lin/MoraiLauncher_Lin_Data/SaveFile/SensorData/CAMERA_2/")

# assigning the res reference path (img, yolo_label)
resImgDstPath = os.path.join(os.path.expanduser('~'), "MoraiImgLabelDataHandler/img/")
resLabelYoloDstPath = os.path.join(os.path.expanduser('~'), "MoraiImgLabelDataHandler/yolo_label/")

# collecting the img and txt file name list
fileImgSrcList = os.listdir(basicImgSrcPath)
fileImgSrcListWext = [file for file in fileImgSrcList if file.endswith(".png")]
fileImgSrcListWextSorted = sorted(fileImgSrcListWext, reverse=False)
fileImgFwdName = []
for i in range(len(fileImgSrcListWextSorted)):
  fileInfo = os.path.splitext(fileImgSrcListWextSorted[i])
  fileTxtNameList = fileInfo[0].split("_")
  fileSrcFwdName = fileTxtNameList[0]
  fileImgFwdName.append(fileSrcFwdName)

fileLabelSrcListWextSorted = []
for j in range(len(fileImgFwdName)):
  fileLabelSrc = os.path.join(fileImgFwdName[j] + "_" + "Instance" + ".txt")
  fileLabelSrcListWextSorted.append(fileLabelSrc)

# for debugging
print(fileImgSrcListWextSorted[1])
print(fileLabelSrcListWextSorted[1])

# copying img files
fileImgCounter = 0
for fileImgSrc in fileImgSrcListWextSorted:
  srcFile = os.path.join(basicImgSrcPath + fileImgSrc)
  fileNumber = fileImgCounter + fileOffset
  resFile = os.path.join(resImgDstPath + fileResFwdName + str('%06d' % fileNumber) + ".png")
  shutil.copy(srcFile, resFile)
  fileImgCounter += 1

# reading the Morai label files
lineLabelArr = []
for fileLabelSrc in fileLabelSrcListWextSorted:
  srcFile = os.path.join(basicLabelSrcPath + fileLabelSrc)
  txtRead = open(srcFile, mode='r', encoding='UTF-8')
  sizeTxtRead = sum(1 for line in open(srcFile))
  dataTxtRead = txtRead.read()
  lineArr = []
  for line in dataTxtRead.splitlines():
    lineArr.append(line)
  lineLabelArr.append(lineArr)

# generating the yolo label files
fileLabelCounter = 0
for i in range(len(lineLabelArr)):
  fileNumber = fileLabelCounter + fileOffset
  resFile = os.path.join(resLabelYoloDstPath + fileResFwdName + str('%06d' % fileNumber) + ".txt")
  resTxt = open(resFile, mode='w', encoding='UTF-8')
  for j in range(len(lineLabelArr[i])):
    labelArr = lineLabelArr[i][j].split()

    # reading label info
    objStrYoloClass = CvtLabelIntInfo(CvtLabelStrInfo(labelArr[0]))
    ptXLt = float(labelArr[4])
    ptYLt = float(labelArr[5])
    ptXRb = float(labelArr[6])
    ptYRb = float(labelArr[7])

    # calculating the center point and bbox(width, height)
    bboxWidth = ptXRb - ptXLt
    bboxHeight = ptYRb - ptYLt
    ptXCen = ptXLt + (float(bboxWidth)/2.0)
    ptYCen = ptYLt + (float(bboxHeight)/2.0)

    # normalizing the center point and bbox size
    normPtXCen = round((ptXCen)/(float(refVgaWidth)), 4)
    normPtYCen = round((ptYCen)/(float(refVgaHeight)), 4)
    normBboxWidth = round((bboxWidth)/(float(refVgaWidth)), 4)
    normBboxHeight = round((bboxHeight) / (float(refVgaHeight)), 4)

    # writing the file info
    resTxt.write(str(objStrYoloClass))
    resTxt.write(" ")
    resTxt.write(str(normPtXCen))
    resTxt.write(" ")
    resTxt.write(str(normPtYCen))
    resTxt.write(" ")
    resTxt.write(str(normBboxWidth))
    resTxt.write(" ")
    resTxt.write(str(normBboxHeight))
    resTxt.write(" ")
    resTxt.write("\n")
  resTxt.close()
  fileLabelCounter += 1
