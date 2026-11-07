# ECE 528/L - Robotics and Embedded Systems with Lab
**CSU Northridge**

**Department of Electrical and Computer Engineering**

## Line Follower Lab
The Line Follower lab interfaces with the following:

* User LEDs of the TI MSP432 LaunchPad
* Pololu Gearmotor with Encoder - [Product Link](https://www.pololu.com/product/3675)
* 8-Channel QTRX Sensor Array - [Product Link](https://www.pololu.com/product/3672)

## Overview
This lab utilizes the 8-Channel QTRX Reflectance Sensor Array to allow the TI-RSLK MAX Chassis to follow a black tape line maze. The sensors detect the robot's position relative to the black line and provide readings that are used to identify different maze situations, including center, slightly left or right, far left or right, turns, T-intersections, and dead ends. A finite state machine is implemented to control the robot's movement based on these situations, which allows the robot to navigate the line maze.

## Components Used
| Components Used | Quantity    | Manufacturer 
| -------------   | ----------- | -----------
| MSP432 Launchpad  | 1 | Texas Instruments
| USB-A to Micro-USB Cable  | 1 | N/A
| TI-RSLK MAX Chassis   | 1 | Pololu
| 8-Channel QTRX Sensor Array  | 1 | Pololu
| Black Tape (1-inch or 3/4-inch) | 1 | N/A

## Prelab
1. ```c
    void Chassis_Board_LEDs_Init()
    {
       P8->SEL0 &= ~0xE1;
       P8->SEL1 &= ~0xE1;
       P8->DIR |= 0xE1;
       P8->OUT &= ~0xE1;
     }
   ```
2.
   ```c
    void Print_Tenth()
    {
       for (int i = 10; i <= 51; i++)
       {
         if ((i % 10) == 0)
         {
           printf("Index %d: Every 10th iteration.\n", i);
         }
         else if ((i - 1) % 10 == 0)
         {
           printf("Index %d: Following the 10th iteration.\n", i);
         }
       }
    }
   ```

## Analysis and Results  
### Task 1  
The Detect_Line_Position function was updated to control the robot's movement based on the reflectance sensor reading. Motor command were used to move the robot forward when centered, adjust the motor speeds when slightly off center, and turn when detecting far right, far left, left turn, and right turn positions. The robot turns right when a T-intersection is detected. A counter was added to stop the motors after approximately 1.5 seconds, and resets whenever another sensor value is detected. The function is called from the Timer_A1_Periodic_Task function after each sensor reading.  

## Known Issues or Limitations  
During left turns, the reflectance sensor would briefly detect a dead end, which would cause the robot to stop. This issue did not occur during right turns. To accommodate for this, a counter was added so the motors stop only after 150 consecutive dead end readings, around 1.5 seconds. This allowed the robot to complete left turns without stopping prematurely.

## Author Contribution  
Anna  
- Pre-lab
- Wrote "Known Issues or Limitations"
- Wrote Task 1 in "Analysis and Results"
- Task 1

Mario  
- Task 1
- Wrote the Overview
  
## References
ECE 528/L Lab 3 - Line Follower.
