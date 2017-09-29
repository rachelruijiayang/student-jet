# Module 2: Answers

1. What is the farthest distance the Jet sonar module can measure?

  **4-5 meters**

2. Tablets and cellphones can detect whether they are being used in a portrait or landscape
  orientation.  What sensor is used to detect this?

  **gyroscope**

3. What does a gyroscope measure?

  **Rate of angular rotation about an axis.**

4. The Jet encoders can detect 3200 ticks per revolution.  If a wheel has moved 1000 ticks
   forward and Jet has 6 inch diameter wheels, how many inches has the robot moved forward?

  **5.89 in.**

5. Explain why the motors cannot be directly connected to the Jetson TK1.

  **The motors require a higher current than the pins on the Jetson can supply.  The h-bridge
shield can supply the current to run the motors.**

6. How do you read the encoder values?

  **The encoder values are published to ROS topics /left_encoder and /right_encoder.**

7. Describe the reason for the 6-pin connector on the Jet motors.

  **2 pins are used to run the motor.  The other 4 pins are for the encoder:  Vcc, ground, and
  2 encoder pins.**

8. Describe the reason for the 4-pin connector on the sonar module.

  **2 pins are Vcc and ground.  1 pins is to trigger the sonar pulse.  The final pin is for
  measuring how long it takes for the sound to reflect back.**

9. You would like to measure how bumpy or smooth the ground is that Jet is running on.  What
   sensor would be best suited for this?

  **Accelerometer**

10. What is gyroscope drift?

  **Over time, a gyroscope will accumulate error and drift away from the actual position.**
