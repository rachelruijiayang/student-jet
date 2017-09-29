# Module 5: Questions

1. What sensors can be used for dead reckoning?

2. What happens to the accuracy of dead reckoning estimates over time?  What can be done to mitigate this effect?

3. What are the limitations of using a compass for dead-reckoning?

4. If a robot has a wheel radius of 2 cm and a wheel separation of 4, calculate the
the angle of the robot (theta) if the right wheel turned one revolution forward and the left wheel did not turn.

5. Consider a robot whose dead-reckoning system seems to miss sudden accelerations or changes in position.  What would you propose to solve the problem?

6. When designing a robot, how would you determine which sensors should be included?

7. Consider a robot that has an accelerometer and encoders.  If the accelerometer estimates the velocity as 2 m/s with a variance of .5 and the encoders estimate the velocity as 3 m/s with a variance of 1, what is the combined estimate using the probabilistic equations discussed in lecture? What is the combined variance?

8. If you are designing a Kalman filter to estimate the x-position and x-velocity of a robot what would be an appropriate state transition matrix (F)?

9. Calculate the updated state vector x if the original estimate is [[1], [3]], the measurement vector is [[0], [2]], the measurement estimation matrix H is [[0, 0], [0, 1]] and K is 0.5.

10. Can you use a Kalman filter to estimate a state vector consisting of x-position and x-acceleration?  Why or why not?
