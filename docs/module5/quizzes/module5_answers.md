# Module 5: Answers

1. What sensors can be used for dead reckoning?

  **accelerometer, gyroscope, compass, motor encoders**

2. What happens to the accuracy of dead reckoning estimates over time?  What can be done to mitigate this effect?

  **As the robot continues to move, the dead reckoning position estimates become less certain and less accurate. There are many solutions that can help reduce this loss of precision.  If available, a GPS could be used to refine estimates.  If a map of the area is available, a localization algorithm could help refine the position estimate.  If there are multiple sensors, additional sensors could be incorporated to improve the position predictions.**

3. What are the limitations of using a compass for dead-reckoning?

  **Compasses only measure orientation so they must be combined with other sensors to measure linear velocity.  Compasses can be affected by nearby magnetic fields.  Compasses only provide orientation in two-dimensions and not three.**

4. If a robot has a wheel radius of 2 cm and a wheel separation of 4, calculate the
the angle of the robot (theta) if the right wheel turned one revolution forward and the left wheel did not turn.

  **(2/4)(2\*pi) = pi**

5. Consider a robot whose dead-reckoning system seems to miss sudden accelerations or changes in position.  What would you propose to solve the problem?

  **Decrease the time between updates of the state to incorporate sudden changes.  Adding new sensors that have faster response times could also help.**

6. When designing a robot, how would you determine which sensors should be included?

  **Sensors should provide data about all aspects of the environment that the robot needs to know in order to perform its task.  If the environment is dynamic, then sensors should be chosen to collectively handle all scenarios.  Other aspects like cost, weight, power consumption, and ease of use could factor into the design as well.**

7. Consider a robot that has an accelerometer and encoders.  If the accelerometer estimates the velocity as 2 m/s with a variance of .5 and the encoders estimate the velocity as 3 m/s with a variance of 1, what is the combined estimate using the probabilistic equations discussed in lecture? What is the combined variance?

  **v = (2 + 1)^-1 = .333;  u = (2 \* 2 + 3 \* 1) \* .333 = 2.33 m/s**

8. If you are designing a Kalman filter to estimate the x-position and x-velocity of a robot what would be an appropriate state transition matrix (F)?

  **F = [[1, 1],[0, 1]] where x = [pos, vel]**

9. Calculate the updated state vector x if the original estimate is [[1], [3]], the measurement vector is [[0], [2]], the measurement estimation matrix H is [[0, 0], [0, 1]] and K is 0.5.

  **x = [[1], [3]] + 0.5 \* ([[0], [2]] - [[0], [3]]) = [[1], [2.5]]**

10. Can you use a Kalman filter to estimate a state vector consisting of x-position and x-acceleration?  Why or why not?

  **No, Kalman filters only work on linear relationships.  It would be impossible to design a state transition matrix F that can convert the current acceleration into position since the relationship is a quadratic.  There are variants of the Kalman Filter like the Extended Kalman Filter that could be used to solve non-linear relationships.**
