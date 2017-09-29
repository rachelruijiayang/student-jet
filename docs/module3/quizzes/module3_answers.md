# Module 3: Answers

1. Apply the horizontal Sobel edge detector to the following image patch.  Use border values to
   extend the image where necessary.

```
10 | 20
-------
30 | 40
```

**Answer**

```
-80 | -80
---------
-80 | -80
```

2. Apply the averaging blur filter to the following image patch.  Use border values to extend the image where necessary.  Round output values to nearest integer.

```
10 | 20
-------
30 | 40
```

**Answer**

```
16 | 23
-------
27 | 30
```

3. Name the advantages and disadvantages of processing images at a higher resolution.

  **Advantages:  more information, higher quality picture**

  **Disadvantages:  slower, more processing**

4. Threshold the following grayscale image using 127 as the threshold.

```
50 | 100
-------
150 | 200
```

**Answer**

```
0 | 0
-----
1 | 1
```

5. Apply the Gaussian blur filter to the following image patch.  Use border values to extend
   the image where necessary.  Round output values to the nearest integer.

```
10 | 20
-------
30 | 40
```

**Answer**

```
14 | 21
-------
20 | 36
```

6. All the lines running through a single point in Cartesian become what in the Hough space?

  **A curve**

7. In Hough space, how are likely lines selected?

  **When curves intersect in Hough space, this corresponds to lines that run through multiple
  points in Cartesian space.  The (r,theta) parameters at the intersection are likely lines in
  the image.**

8. What does the zeroth order spatial moment represent?

  **It represents the area of a segmented object.**

9. What is meant by 24-bit color?

  **Each color channel is represented by 8-bit (1 byte).  There are 3 color channels: Red, Green, and Blue.**

10. How can a color image be converted to grayscale?

  **Average the RGB values for each pixel.  The averaged value is the grayscale value for the pixel.**
