# Module 1: Answers

1. What types of computing cores are available on the Jetson TK1?

  **There are 4 ARM A15 cores, 1 low power ARM core, and 192 CUDA cores on the GPU.**

2. How can you remotely connect to the Jetson TK1?

  - **Command line: using ssh**
  - **Graphical: using a vnc client**

3. Describe the reasons for having the Arduino Mega run alongside the TK1.

  **The Arduino Mega handles low-level embedded functionality such as reading sensors and controlling the motors.**

4. What components are directly connected to the battery?

  **The Jetson TK1 and the H-bridge shield.**

5. Describe the capabilities of ROS nodes.

  **ROS nodes are processes that perform some computation.  They can be reading a sensor and publishing the sensor value.  They can also be used to send commands to the motors.**

6. What does it mean for ROS Topics to be 'strongly typed'?

  **Topics can only send messages that are only of the correct type for that topic.**

7. What command is used to clean out any recently compiled ROS nodes?

  **`catkin_make clean`**

8. Describe the relationship between the Ubuntu Linux OS and ROS.

  **Linux is the actual running OS kernel.  ROS is a framework that runs on top of Linux and provides messaging between ROS processes.**

9. How are ROS nodes started?

  **The can be started using the `roslaunch` command.**

10. How can you know what topics are available on a ROS system?

  **`rostopic list`**
