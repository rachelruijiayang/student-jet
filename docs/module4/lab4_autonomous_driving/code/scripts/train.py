#! /usr/bin/env python
#https://prateekvjoshi.com/2016/02/16/deep-learning-with-caffe-in-python-part-iii-training-a-cnn/

import os
import ros
import rospkg

rospack = rospkg.RosPack()

base_path = rospack.get_path('lab4_autonomous_driving')
network_path = os.path.join(base_path, "neuralnetwork")
trainproto_path = os.path.join(network_path, "train.prototxt")

os.chdir(network_path)
os.system("~/caffe/build/tools/caffe train --solver " + trainproto_path)
