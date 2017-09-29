# Module 9: Answers

1. What are some limitations of aerial maps?

  **Usually only accurate to a couple of meters, do not show objects hidden beneath other objects, may be out of date.**

2. What is the method of detecting overlapping images in image stitching that was discussed in lecture?

  **Keypoints (features) are identified in all of the images.  Then these features are matched between the images to detect overlapping regions.  Good keypoints are unique and invariant to small differences in scale and orientation.**

3. What class in OpenCV is used for stitching images or maps together?

  **Stitcher**

4. What are some examples of information that can be included in maps that is not present in traditional aerial images?

  **semantic information (place names), timely information (traffic conditions, road closures), hyperspectral information (non-visible light emissions), and thermal information (heat signatures from animals)**

5. Name three tools or techniques that can be used to generate point clouds.

  **stereo cameras, LiDar, Radar, structure from motion, and image stitching**

6. What are the two things that SLAM is trying to maximize the likelihood of?

  **SLAM maximizes the likelihood of the map given the sensor data and robot pose, and SLAM maximizes the likelihood of the robot pose given the map and the sensor data.**

7. Why are particle filters often preferred to Kalman Filters for SLAM?

  **The computational complexity of Kalman Filters is quadratic with the number of landmarks, while the computational complexity of particle filters can be logarithmic with respect to the number of landmarks.**

8. What are the attributes of a good landmark?

  **Easy to differentiate from the background environment, distinct from other landmarks.**

9. What causes the Loop Closure problem?

  **The Loop Closure problem occurs when small errors in mapping and SLAM compound to produce a map that is significantly different from reality.  Closing the loop requires the robot to analyze large parts of the map to detect overlap.**

10. Why is it difficult to use a Monocular camera for SLAM?

  **It is difficult to extract robust landmark locations and/or point clouds from a monocular camera.  However, ORB-SLAM and LSD-SLAM have shown that monocular slam is possible.**
