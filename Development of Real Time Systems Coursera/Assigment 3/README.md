## Overview

In this assignment we will focus a bit more on the theoretical side.
We will have a look at verifying real-time system by using the cyclic structured construct 
handled in the course and a simulation environment to automatically schedule a full timeline. 
The main purpose of the assignment is to expose the student to several ways of planning and 
verifying a real-time system in practice.

#### Assigment 1 

1. Input the tasks T1(2, 0.5), T2(3, 1.2), T3(6, 0.5) and 
   the RM scheduler into the SimSo simulator

2. Provide a report answering the following questions:

  - What is the utilization factor of the system and what is the value for Urm(3)
  - What is the minimum/maximum/average response time of all tasks?
  - Is any task missing the deadline? Which task? Where?
  - If a deadline is missed, could it be avoided by changing the scheduler?

#### Assigment 2
1. Input the tasks T1(2, 0.5, 1.9) T2(5, 2) T3(1, 0.1, 0.5) T4(10, 5, 20) 
   and the EDF scheduler into the SimSo simulator

2. Provide a report answering the following questions:

 - What is the utilization factor of the system and what is the value for Urm(4)
 - What is the minimum/maximum/average response time of all tasks?
 - Is any task missing the deadline? Which task? Where?
 - If a deadline is missed, could it be avoided by changing the scheduler?