# Harvester Project

## Overview


The goal of this project is to program Jet to move all of the colored balloons into their respective goals.  Each robot will have 1 minute to score as many balloons as possible.

## Physical Design

A sample layout for the arena is shown in Figure \ref{competition_start}.  The area after the robot has successfully moved all of the balloons is shown in Figure \ref{competition_end}.  The edges of the arena should be made with a tape that is distinct from the ground color.  The goals should be cardboard boxes that are either painted or covered in colored construction paper for the red and blue goals.  The balloons should be sufficiently large so that the robots can readily identify them.  

![Competition Start\label{competition_start}](projects/resources/harvester_1.png "Competition Starting")

![Competition End\label{competition_end}](projects/resources/harvester_2.png "Competition End")

Students are allowed to add cardboard "arms" to their robots to facilitate the movement of the balloons.  The "arms" must be static and not controlled by motors.

## Requirements

A balloon is scored when the majority of the balloon is within the bounds of the goal.  

1 point is awarded for every balloon that is placed in the appropriate goal.  A penalty of -3 points is added to the robot's score for each balloon that is placed in the wrong goal.  The winning robot is the robot with the highest score.

The robots will be assessed a -10 penalty if the entire robot leaves the arena boundary.   Balloons that are pushed outside of the arena must be left there.
