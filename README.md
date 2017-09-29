# Robotics Teaching Kit with 'Jet'

The Robotics Teaching Kit with 'Jet' includes example code, lecture slides, quiz/exam problem sets, labs/solutions, and projects for teaching a full-term curriculum robotics course. The material is organized into modules that cover specific topics. It is logical to teaching in order through the modules, but each module is self-contained so instructors can re-order modules as needed.

The kit is produced jointly by NVIDIA and Cal Poly San Luis Obispo.  All material is available under the [Creative Commons Attribution-NonCommercial License](http://creativecommons.org/licenses/by-nc/4.0/).

## 'Jet' Robot Hardware

**The TX1 'Jet' Robot Kit and the TK1 'Jet' Robot Kit are now available for purchase and shipping globally from Servocity!**

* [TX1 ‘Jet’ Robot Kit](https://www.servocity.com/tx1-jet-robot-kit)
* [TK1 ‘Jet’ Robot Kit](https://www.servocity.com/tk1-jet-robot-kit)

The full hardware bill of materials (BOM), including pricing and where to buy now, can be found here:  

* [TX1 ‘Jet’ Robot Kit BOM (TX1)](https://docs.google.com/spreadsheets/d/1jGn7AG5NivTjxPEppJEdIUVxhm5nB17T3ZtRTCYyuQg/edit?usp=sharing)
* [TK1 ‘Jet’ Robot Kit BOM (TK1)](https://docs.google.com/spreadsheets/d/14N_tkfNsItY9CV0vUGHCPpcZ-mqgsZsC87CQEHBXMmY/edit?usp=sharing)
 
The [HardwareTemplates](https://drive.google.com/drive/folders/0B8F3iGtBky5JQUIzR1JTd0xWRzg?usp=sharing) shared directory includes design files that can be used to laser cut the Jet's base mounting plate and sonar holders.  The `JetbotPlate` files are the layout of the base plate in different, common file formats. The `SonarHolders` files are the layout of the sonar holders.

## About the Content

#### Examples

The `/examples` folder includes a variety of demonstrations.  Many of the examples
have been converted into lab assignments; therefore the examples should not be provided
to students because the examples contain solutions to many labs.
You can run an example by following the instructions below:

1. Build and launch the rosjet platform (following the instructions in lab 1).
2. Navigate to the examples folder
3. Enter the command `catkin_make && source devel/setup.sh`
4. Run any of the examples by typing `rosrun [example_name] [example_name]`

#### Docs

The `/docs` folder contains the quizzes, projects and labs for the course.  To create the .pdf and .docx versions
of the documents, you must install [pandoc](http://pandoc.org/installing.html).

**NOTE: We currently recommend using the recently updated files in `/lab1_building_robot` from the latest Robotics-Teaching-Kit-with-Jet.zip static download instead of the files in `/lab1_building_robot` here in the repo (those files here in the repo will be updated soon). All other source files and documents generated from this repo are up to date.**

**NOTE: Although we provide instructions for Pandoc on Windows, it has not yet been extensively tested - Linux is highly recommended**

Then the labs can be built with the command `python make_labs.py` when you are in the
`/docs` directory.  The build folder will then contain the compiled documentation as
well as zipped folders that contain the code and solutions for the labs.

Students should receive both the lab description (.docx or .pdf) and the code.zip folder.
The solution.zip should be kept by the instructor.

## NVIDIA Deep Learning Institute (DLI) Online Labs

The Robotics Teaching Kit with 'Jet' includes access to free online Deep Learnining Institute (DLI) labs (“Qwiklabs”) using GPUs in the cloud - a value of up to $30 per person per lab. These online labs reinforce deep learning concepts presented in the teaching kit to students in a more applied manner. Each Qwiklab is a live, hands-on, self-paced learning environment that includes a set of interactive instructions to walk students through applied deep learning concepts. Students must complete each lab within the allotted time.

Online DLI Qwiklab topics include:

* Image Classification with NVIDIA DIGITS
* Object Detection with NVIDIA DIGITS
* Image Segmentation with TensorFlow
* And many more!

More DLI labs and detailed descriptions can be found [here](https://nvidia.qwiklab.com/tags/Deep%20Learning) in the catalogue. To see a list of ALL available labs please go to the [catalog](https://nvidia.qwiklab.com/catalog) and click on the "Labs" tab.

*To enable these labs for your students, please create an account at [nvidia.qwiklab.com](https://nvidia.qwiklab.com) and send your Qwiklab account email address to [NVDLI@nvidia.com](mailto: NVDLI@nvidia.com) with the subject line “DLI Robotics Teaching Kit Qwiklab Access”. Email instructions will then follow for giving access to your students.*

Please see `Online DLI Labs.pdf` from the Robotics Teaching Kit with 'Jet' `.zip` for more details.

## About the NVIDIA Deep Learning Institute (DLI)
The NVIDIA DLI offers hands-on training for developers, data scientists, and researchers looking to solve challenging problems with deep learning.

Through self-paced online labs and instructor-led workshops, DLI provides training on the latest techniques for designing, training, and deploying neural networks across a variety of application domains including self-driving cars, healthcare, robotics, finance, and video analytics.

#### Start a Deep Learning Project
Explore three simple steps to kick off your deep learning initiative for a solo project, a small team, or at scale: www.nvidia.com/deep-learning/developer.

#### Keep Learning with DLI
Check out upcoming workshops in your area at www.nvidia.com/dli. 

Request an onsite workshop for your team at www.nvidia.com/requestdli.