#Configure time-zone
sudo dpkg-reconfigure tzdata

#Ros Prerequisites
sudo update-locale LANG=C LANGUAGE=C LC_ALL=C LC_MESSAGES=POSIX
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu xenial main" > /etc/apt/sources.list.d/ros-latest.list'
wget https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -O - | sudo apt-key add -
sudo apt-get update

#Ros installation (Kinetic for ubuntu 16.04)
sudo apt-get -y install ros-kinetic-ros-base --allow-unauthenticated

#Python Dependencies
sudo apt-get -y install python-rosdep python-dev python-pip python-rosinstall python-wstool --allow-unauthenticated

sudo c_rehash /etc/ssl/certs #TX1 has problems with the imaging of its certificates. If this step is not followed rosdep init will fail

sudo rosdep init
rosdep update
echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
source ~/.bashrc

#Ros packages
sudo apt-get -y install ros-kinetic-rosserial-arduino --allow-unauthenticated
sudo apt-get -y install ros-kinetic-rosserial --allow-unauthenticated
sudo apt-get -y install ros-kinetic-eigen-conversions --allow-unauthenticated
sudo apt-get -y install ros-kinetic-tf2-geometry-msgs --allow-unauthenticated
sudo apt-get -y install ros-kinetic-angles --allow-unauthenticated
sudo apt-get -y install ros-kinetic-web-video-server --allow-unauthenticated
sudo apt-get -y install ros-kinetic-rosbridge-suite --allow-unauthenticated
sudo apt-get -y install ros-kinetic-rospy-tutorials --allow-unauthenticated
sudo apt-get -y install ros-kinetic-joy --allow-unauthenticated
sudo apt-get -y install ros-kinetic-teleop-twist-joy --allow-unauthenticated
sudo apt-get -y install ros-kinetic-roslint --allow-unauthenticated
sudo apt-get -y install ros-kinetic-controller-manager --allow-unauthenticated
sudo apt-get -y install ros-kinetic-camera-calibration-parsers --allow-unauthenticated
sudo apt-get -y install ros-kinetic-xacro --allow-unauthenticated
sudo apt-get -y install ros-kinetic-robot-state-publisher --allow-unauthenticated
sudo apt-get -y install ros-kinetic-diff-drive-controller --allow-unauthenticated
sudo apt-get -y install ros-kinetic-ros-control --allow-unauthenticated
sudo apt-get -y install ros-kinetic-dynamic-reconfigure --allow-unauthenticated
sudo apt-get -y install ros-kinetic-fake-localization --allow-unauthenticated
sudo apt-get -y install ros-kientic-joint-state-controller --allow-unauthenticated

#USB_CAM package is not integrated in ROS Kinectic repository, you need to install it from source
cd ~/catkin_ws/src
git clone https://github.com/bosch-ros-pkg/usb_cam.git
cd ..

# Configure Catkin Workspace
source /opt/ros/kinetic/setup.bash
cd ~/catkin_ws/src
catkin_init_workspace

#Install Ros Opencv bindings from source (If the vision_opencv package fails compilation, please download it and move to your catkin workspace and catkin_make)
cd ~/catkin_ws
wstool init src src/rosjet/TX1_rosjet.rosinstall
wstool merge -t src src/rosjet/TX1_rosjet.rosinstall
wstool update -t src

#Install Caffe
sudo add-apt-repository universe
sudo apt-get update -y
/bin/echo -e "\e[1;32mLoading Caffe Dependencies.\e[0m"
sudo apt-get install cmake -y
# General Dependencies
sudo apt-get install libprotobuf-dev libleveldb-dev libsnappy-dev \
libhdf5-serial-dev protobuf-compiler -y
sudo apt-get install --no-install-recommends libboost-all-dev -y
# BLAS
sudo apt-get install libatlas-base-dev -y
# Remaining Dependencies
sudo apt-get install libgflags-dev libgoogle-glog-dev liblmdb-dev -y
sudo apt-get install python-dev python-numpy -y

sudo usermod -a -G video $USER
/bin/echo -e "\e[1;32mCloning Caffe into the home directory\e[0m"
# Place caffe in the home directory
cd $HOME
# Git clone Caffe
git clone https://github.com/BVLC/caffe.git 
cd caffe 
cp Makefile.config.example Makefile.config
# Regen the makefile; On 16.04, aarch64 has issues with a static cuda runtime
cmake -DCUDA_USE_STATIC_CUDA_RUNTIME=OFF
# Include the hdf5 directory for the includes; 16.04 has issues for some reason
echo "INCLUDE_DIRS += /usr/include/hdf5/serial/" >> Makefile.config
/bin/echo -e "\e[1;32mCompiling Caffe\e[0m"
make -j4 all

# Run the tests to make sure everything works - This takes a really long time, so comment it if you want to run it later.
/bin/echo -e "\e[1;32mRunning Caffe Tests\e[0m"
make -j4 runtest

# System Optimizations
gsettings set org.gnome.settings-daemon.plugins.power button-power shutdown
gsettings set org.gnome.desktop.screensaver lock-enabled false
sudo apt-get -y install compizconfig-settings-manager
gsettings set org.gnome.desktop.interface enable-animations false
gsettings set com.canonical.Unity.Lenses remote-content-search none
echo -e '[SeatDefaults]\nautologin-user=ubuntu' > login_file; sudo mv login_file /etc/lightdm/lightdm.conf
gsettings set org.gnome.Vino enabled true
gsettings set org.gnome.Vino disable-background true
gsettings set org.gnome.Vino prompt-enabled false
gsettings set org.gnome.Vino require-encryption false

echo "alias sr='source ~/catkin_ws/devel/setup.bash'" >> ~/.bashrc

cd ~/catkin_ws
catkin_make && source devel/setup.sh

#Before starting with ROS, you might want to remove OpenCV4Tegra if you had flashed that from JetPack, and install OpenCV 3.1 instead as there are some configurations issues that needs to be resolved for using OpenCV4Tegra with ROS Kinetic. (Note: OpenCV4Tegra is designed in such a way that it utilizes the power of the Nvidia GPU. OpenCV 3.1 only uses CPU.)
#Comment out all the lines from below if you want to continue with OpenCV4Tegra.

#Uninstalling OpenCV4Tegra
sudo apt-get purge libopencv4tegra-dev libopencv4tegra
sudo apt-get purge libopencv4tegra-repo 
sudo apt-get update

#OpenCV 3.1 Installation 
sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
sudo apt-get install python2.7-dev
sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
sudo apt-get install libgtkglext1 libgtkglext1-dev
sudo apt-get install qtbase5-dev
sudo apt-get install libv4l-dev v4l-utils qv4l2 v4l2ucp
git clone https://github.com/opencv/opencv.git
curl -L https://github.com/opencv/opencv/archive/3.2.0.zip -o opencv-3.2.0.zip
unzip opencv-3.2.0.zip
cd opencv-3.2.0
mkdir release
cd release
cmake -D WITH_CUDA=ON -D CUDA_ARCH_BIN="5.3" -D CUDA_ARCH_PTX="" -D WITH_OPENGL=ON -D WITH_LIBV4L=ON -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j4
sudo make install

