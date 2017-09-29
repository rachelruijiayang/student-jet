## Configuring the Host Computer

This document describes the first steps you will need to go through in order to prepare
the host computer for interacting with Jet.

You must have a computer or virutal machine running Ubuntu.  Check out [Virtual Box](https://www.virtualbox.org/wiki/Downloads) if
you need to install on a Windows or Mac OSX computer.

## Installing jethost

* Install git

  `sudo apt-get install git`

* Choose a location for your ROS files and change to that directoy
  `cd FOLDER_FOR_ROS`

* Create a workspace

  `mkdir -p catkin_ws/src; cd catkin_ws/src`

* Clone this repository into the workspace

  `git clone https://github.com/NVIDIAGPUTeachingKit/jethost.git`

* Run the ros configuration script

  `rosjet/jethost_install.sh`

## Programming the Arduino

 * Connect your Arduino Mega to the computer with jethost

 * Compile and flash the Arduino

  `./jet_arduino/scripts/program.sh`

## Configuring ROS Environment Parameters
 * Connect to the same network that Jet is on.

 * Lookup your own IP address

  `ifconfig wlan0` if using WiFI

  `ifconfig eth0` if using ethernet

 * Lookup the Jetson's IP address using your router settings or connecting Jet to an HDMI monitor

 * Edit your /etc/hosts

  `sudo echo "YOUR_IP_ADDRESS jethost" >> /etc/hosts`
  `sudo echo "JET_IP_ADDRESS jet >> /etc/hosts"`

 * Set ROS_MASTER_URI in .bashrc

  `echo "export ROS_MASTER_URI=http://jet:11311" >> ~/.bashrc`

 * Source .bashrc

  `source ~/.bashrc`

 * SSH into Jet and perform similar updates

 `sudo echo "YOUR_IP_ADDRESS jethost" >> /etc/hosts`
 `sudo echo "localhost jet >> /etc/hosts"`
 `echo "export ROS_MASTER_URI=http://localhost:11311" >> ~/.bashrc`

 * Verify the configurations by running jet_real.launch on Jet

  `source ~/.bashrc; source catkin_ws/devel/setup.sh; roslaunch jet_bringup jet_real.launch`

 * On the jethost, make sure you can see the topics

  `rostopic list` should return all topics
  `rostopic echo arduino/encoder_left_value` should show the left encoder's data
