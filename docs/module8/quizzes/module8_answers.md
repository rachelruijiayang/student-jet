# Module 8: Answers

1.  What is the difference between multinomial resampling and systematic resampling?

  **Systematic resampling generates random samples that are evenly distributed throughout the sample space.  These samples will select higher weighted particles more often, but the sample space is evenly distributed.  Multinomial resampling just generates samples that can land anywhere in the sample space.**

2.  In Monte Carlo Localization, what does each of the particles represent?

  **Each particle represents a possible pose for the robot.**

3.  What is the purpose of incorporating motion noise into the motion model?

  **The motion model noise accounts for the physical "noise" that occurs when the robot moves.  Because of effects such as wheel slip, gear train inaccuracies, or electrical loses, a robot will not move exactly as commanded.**

4.  What is the purpose of incorporating sensor noise into the sensor model?

  **Sensor noise is added to model the fact that sensor readings are not completely reliable.  A sensor that is measuring a fixed object may produce a distribution of readings.  This is the effect that the sensor noise is attempting to capture.**

5.  Describe the problem of particle deprivation.

  **As particles are resample, the particles will converge around the higher weighted particles.  In location where the weights of the particles is low, these particles will have a small probability of being resampled.  Eventually the particles in these areas will be removed.**

6.  Describe 2 possible ways of estimating the position of a robot after the particles begin converging.

  **The position of the highest weight particle; the mean of the position of all the particles.**

7.  How can numbers be sampled from a Gaussian distribution to model motion or sensor noise?

  **One technique for sampling numbers from a Gaussian distribution is the Box-Muller transform.**

8.  What limitations arise from performing localization using only wheel encoders?

  **Because of wheel slippage, the localization estimate can drift over time and become very inaccurate.**

9.  What active sensors can be used to aid in localization?  

  **Laser scanner, sonar, radar, camera, radio**

10.  What is the update step in Monte Carlo Localization?

  **The update step is used to incorporate the latest sensor reading in order to generate new weights for each of the particles.**
