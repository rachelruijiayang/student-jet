# rosjet

ROS nodes and arduino libraries for the NVIDIA Robot Teaching Kit with `Jet`.

## installation

For installing and configuring your Jetson board for the Jet robot, see the TX1INSTALLATION file.

## Tips

1. For introduction and working knowledge refer to the books 'A gentle introduction to ROS' and 'Learning ROS for robotics programming'. The ROS online documentation and forums also have a lot of help.
2. For any issues with Ubuntu refer to the ubuntu forums online.
3. The nvidia developer forums offer incredible insight and support into any problems you might face. Kindly create an account and you will find help.
4. Regarding the files and scripts found in this material, kindly go through all the scipts and instructions before getting started. Lookout for the comments and instructions.
5. Post rosjet_install.sh is run, Restart the computer. After this, there might be a problem in UBUNTU 16.04 (Jetson TX1 in case you are working on it using a extended monitor and want to use ti without performing an ssh into it) which makes the gnome terminal and other apps not open. If this happens follow these steps:

'sudo nano /etc/default/locale'

Once it opens change it from 

LANG=C
LC_ALL=C
LC_MESSAGES=POSIX
LANGUAGE=C

to

LANG=en_US.UTF-8
LC_ALL=en_US.UTF-8
LC_MESSAGES=POSIX
LANGUAGE=en_US.UTF-8

## Running rosjet

For Gazebo Simulation:
```
roslaunch jet_bringup jet_gazebo.launch
```

For Real Robot:
```
roslaunch jet_bringup jet_real.launch
```
