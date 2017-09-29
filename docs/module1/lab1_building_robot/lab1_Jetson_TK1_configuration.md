## Configuring the Jet Robot

This document describes the first steps you will need to go through in order to prepare
the Jetson board for use with Jet.

After opening the NVIDIA Jetson box, you will need the following items:

* Jetson board
* micro USB cable
* AC power adapter

In addition, you will need:

* an ethernet cable
* a router that is connected to the Internet

## Preparing the Jetson Board

* Plug one end of the ethernet cable into the Jetson board and plug the other end into the router
* Do not plug in power adapter just yet (you will plug in power during the OS flash step)

## Running JetPack

Download and install the [NVIDIA Jetpack](https://developer.nvidia.com/embedded/jetpack).
You will need to be running Ubuntu 14.04 on your host computer.

Once Jetpack is up and running perform the following actions:

* Select TK1 as target board
* Click the `Clear Actions` button (upper right corner).  This will de-select all of the options.
* Select the following options for install:
    - `Driver for OS`
    - `File System`
    - `Flash OS`
    - `CUDA Toolkit for L4T`
    - `cuDNN Package`
    - `OpenCV for Tegra`
    - also select the box `Automatically resolve dependency conflicts`
* On the Network Layout page:
    - Select `Device accesses Internet via router/switch`
* On the Network Interface Selection page:
    - select `eth0` (assuming your host computer only has 1 ethernet)

## Flash the OS

After you have started the installation, the JetPack installer will download files and
install them.  As the installer continues, it will reach a point where it will flash the
OS to the Jetson board.  At this point, the installer will ask you to put the board into
Force USB Recovery Mode:

* Connect the micro USB cable to the Jetson TK1 and the host computer
* Plug the AC power adapter into AC power and connect the power jack to the board
* Enter USB Recovery Mode using the following sequence:
    - Press and release Power button
    - Hold down the Force Recovery button, then press and release Reset (while holding down Force Recovery)
    - You can check if the board is in Recovery mode by connecting to the Jetson board via ssh and running `lsusb`.  There should be a device with vendor 'NVidia Corp'
    - Begin the flashing process on the host by pressing Enter.  This will take several minutes.

## Installing the Jet software

Once the install is complete, you can go ahead and disconnect the micro USB cable.  Now we will install the rosjet libraries and utilities.  On your host computer, download the lab1 zip file from your instructor.

* On your host computer, download the lab1 zip file from your instructor, then unzip the folder.

  `wget http://instructorurl/lab1_building_robot-code.zip; unzip lab1_building_robot-code.zip; rm lab1_building_robot-code.zip`

* Connect to the Jetson via ssh
  The username is 'ubuntu' and the password is 'ubuntu'. You can find it's ip address by looking at your router's configuration.

* On the Jetson, install git

  `sudo apt-get install git`

* On the Jetson, make the ROS workspace directory

  `mkdir -p ~/catkin_ws/src; cd ~/catkin_ws/src`

* On your host computer, extract the lab1 zip file.  Then copy the `rosjet` folder to the Jetson

  `scp -r ~/lab1_building_robot-code/rosjet ubuntu@JETSONURL:~/catkin_ws/src/rosjet`

* On the Jetson, run the ros configuration script

  `./rosjet/rosjet_install.sh`

* Configuration of the Jetson is now complete; reboot the Jetson board before continuing.

* On the host computer, create a folder for ROS packages:

  `mkdir -p ~/catkin_ws/src; cd ~/catkin_ws/src`

 * On the host computer, copy the `jethost` folder to the workspace

  `cp -r ~/lab1_building_robot-code/jethost ~/catkin_ws/src/jethost`

 * On the host computer, run the jethost installation script

  `./jethost/jethost_install.sh`

## Configuring ROS Environment Parameters

 * On your host computer, lookup your own IP address

  `ifconfig wlan0` if using WiFI

  `ifconfig eth0` if using ethernet

 * Lookup the Jetson's IP address using your router settings or connecting Jet to an HDMI monitor

 * Edit your `/etc/hosts`

  `sudo echo "YOUR_IP_ADDRESS jethost" >> /etc/hosts`

  `sudo echo "JET_IP_ADDRESS jet" >> /etc/hosts`

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
