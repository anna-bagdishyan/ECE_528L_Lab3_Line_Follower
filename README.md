# ECE 528/L - Robotics and Embedded Systems with Lab
**CSU Northridge**

**Department of Electrical and Computer Engineering**

## Line Follower Lab
The Line Follower lab interfaces with the following:

* User LEDs of the TI MSP432 LaunchPad
* Pololu Gearmotor with Encoder - [Product Link](https://www.pololu.com/product/3675)
* 8-Channel QTRX Sensor Array - [Product Link](https://www.pololu.com/product/3672)

## Overview

## Components Used
| Components Used | Quantity    | Manufacturer 
| -------------   | ----------- | -----------
| MSP432 Launchpad  | 1 | Texas Instruments
| USB-A to Micro-USB Cable  | 1 | N/A
| TI-RSLK MAX Chassis   | 1 | Pololu
| 8-Channel QTRX Sensor Array  | 1 | Pololu

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

## Known Issues or Limitations  
There are no known current issues or limitations.  

## Author Contribution  
Anna  
- 

Mario  
- 
  
## References
ECE 528/L Lab 3 - Line Follower.
