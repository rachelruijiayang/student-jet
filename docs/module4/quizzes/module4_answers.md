# Module 4: Answers

1. What type of Machine Learning has unlabeled data, but the system learns from feedback on its actions?

  **Reinforcement Learning**

2. A machine learning model produces 40 true positives, 10 false positives, and 30 true negatives on 100 training examples.  What is the precision and recall?

  - **Precision: .8**
  - **Recall: .66**

3. A model has an accuracy of 95% on training data, but only 55% accuracy on test data.  Qualitatively, what is the bias (high/low) and variance (high/low)?

  **Low Bias, High Variance**

4. What are some relevant features for building a model that predicts where someone will enjoy a movie?

  **Any of the following would be acceptable**

  - **How many friends of the person enjoyed the movie**
  - **Number of actors in the movie that the person likes**
  - **Whether the person likes the genre of that movie**
  - **Critics rating of the movie**

5. Consider a fully-connected Neural Network with 10 input neurons, two hidden layers each with 30 neurons, and an output layer with 3 neurons.  How many weights are in this Neural Network (ignore any bias terms)?

  **10 x 30 x 30 x 3 = 27,000**

6. Consider a Neural Network that receives a 10 by 10 image and applies a convolution layer with 7 filters, a kernel size of 3, and a stride of 1.  Assume that network pads the image with zeros, and that each of these zeros is included in the multiplications.  How many individual multiplication operations are applied?

  **(10 x 10) x (3 x 3) x 7 = 6,300**

7. What is an example of an activation function for a Neural Network?

  **Any of the following are acceptable:**

  - **Rectified Linear Activation (ReLU)**
  - **Hyperbolic Tanger (tanh)**
  - **Sigmoid**

8. What is Gradient Descent used for in Neural Networks?

  **Gradient Descent is used to minimize the error of the Neural Network during training.**

9. What syntax is used to specify model definitions in Caffe?

  **Protocol Buffer**

10. In Caffe, what layers are used for training a Neural Network that are not used in the deployed Neural Network?

  - **data layers (perform cropping and subtraction of image means)**
  - **accuracy layer**
  - **loss layer**
