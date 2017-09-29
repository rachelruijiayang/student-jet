#Ros Prerequisites
sudo update-locale LANG=C LANGUAGE=C LC_ALL=C LC_MESSAGES=POSIX
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu trusty main" > /etc/apt/sources.list.d/ros-latest.list'
wget https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -O - | sudo apt-key add -
sudo apt-get update

#Ros Jade Base
sudo apt-get -y install ros-jade-desktop-full

#Python Dependencies
sudo apt-get -y install python-rosdep python-dev python-pip python-rosinstall python-wstool

sudo rosdep init
rosdep update
echo "source /opt/ros/jade/setup.bash" >> ~/.bashrc
source ~/.bashrc

#Ros packages
sudo apt-get -y install ros-jade-rosserial-arduino
sudo apt-get -y install ros-jade-rosserial
sudo apt-get -y install ros-jade-joy
sudo apt-get -y install ros-jade-teleop-twist-joy

# Configure Catkin Workspace
source /opt/ros/jade/setup.bash
cd ../../
catkin_init_workspace

#Build Arduino Ros libraries
cd src/jethost/jet_arduino/resources/lib
rm -rf ros_lib
rosrun rosserial_arduino make_libraries.py .

#Setup Platformio
sudo pip install platformio
platformio platforms install atmelavr
