#! /usr/bin/env python

import os
import random
import ros
import rospkg
import cv2
import sys
import shutil
import rospy

i = 0
data = []

rospack = rospkg.RosPack()

base_path = rospack.get_path('lab4_autonomous_driving')
raw_path = os.path.join(base_path, "resources", "raw")
img_path = os.path.join(base_path, "resources", "img")
data_path = os.path.join(base_path, "resources", "data")
network_path = os.path.join(base_path, "neuralnetwork")

train_percent = .8
if len(sys.argv) > 1:
    train_percent = float(sys.argv[1])

#Clear the contents of the image directory
for f in os.listdir(img_path):
    pth = os.path.join(img_path, f)
    if os.path.isfile(pth):
        os.unlink(pth)

#Clear the contents of the data directory
for f in os.listdir(data_path):
    pth = os.path.join(data_path, f)
    if os.path.isfile(pth):
        os.unlink(pth)

#Read the raw videos and direction
for f in os.listdir(raw_path):
    if ".avi" in f:
        dir_file = open(os.path.join(raw_path, f.replace(".avi", ".csv")))
        vid = cv2.VideoCapture()
        vid.open(os.path.join(raw_path, f))
        hasFrame = True
        while hasFrame:
            hasFrame, img = vid.read()
            im_name = os.path.join(img_path, str(i) + ".jpg")
            if hasFrame:
                icon = cv2.resize(img,(80, 60), interpolation = cv2.INTER_AREA)
                cv2.imwrite(im_name, icon)
                data.append((im_name, dir_file.readline()[0]))
                i += 1

#Shuffle the image and direction pairs
random.shuffle(data)

#Write the train examples to the training file
train_file = os.path.join(data_path, "train_files.txt")
with open(train_file, 'w') as train:
    for i in range(int(train_percent * len(data))):
        train.write(data[i][0] + " " + data[i][1] + "\n")

#Write the test examples to the testing file
test_file = os.path.join(data_path, "test_files.txt")
with open(test_file, 'w') as test:
    for i in range(int(train_percent * len(data)), len(data)):
        test.write(data[i][0] + " " + data[i][1] + "\n")

#Format the data for use in Caffe models
train_lmdb = os.path.join(data_path, "train_lmdb")
test_lmdb = os.path.join(data_path, "test_lmdb")
mean_image = os.path.join(data_path, "mean_image.binaryproto")
shutil.rmtree(train_lmdb)
shutil.rmtree(test_lmdb)
os.system("GLOG_logtostderr=1 ~/caffe/build/tools/convert_imageset --resize_height=60 --resize_width=80 --shuffle / " + train_file + " " + train_lmdb)
os.system("GLOG_logtostderr=1 ~/caffe/build/tools/convert_imageset --resize_height=60 --resize_width=80 --shuffle / " + test_file + " " + test_lmdb)
os.system("~/caffe/build/tools/compute_image_mean " + train_lmdb + " " + mean_image)
