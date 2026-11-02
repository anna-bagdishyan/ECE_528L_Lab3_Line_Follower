/**
 * @file main.c
 *
 * @brief Main source code for the Line_Follower program.
 *
 * This file contains the main entry point for the Line_Follower program.
 * The main controller demonstrates a Line Follower robot without using an advanced algorithm.
 *
 * It interfaces the following peripherals using GPIO to demonstrate line following:
 *  - 8-Channel QTRX Sensor Array module
 *
 * Timers are used in this lab:
 *  - SysTick:  Used to generate periodic interrupts at a specified rate (1 kHz)
 *  - Timer A0: Used to generate PWM signals that will be used to drive the DC motors
 *  - Timer A1: Used to generate periodic interrupts at a specified rate (1 kHz)
 *
 * @note For more information regarding the 8-Channel QTRX Sensor Array module,
 * refer to the product page: https://www.pololu.com/product/3672
 *
 * @author
 *
 */

#include "msp.h"
#include "inc/Clock.h"
#include "inc/CortexM.h"
#include "inc/GPIO.h"
#include "inc/EUSCI_A0_UART.h"
#include "inc/Motor.h"
#include "inc/Timer_A1_Interrupt.h"
#include "inc/SysTick_Interrupt.h"
#include "inc/Reflectance_Sensor.h"

// Initialize constant PWM duty cycle values for the motors
#define PWM_NOMINAL 2500

// Initialize a global variable for Timer A1 to keep track of elapsed time is milliseconds
static uint32_t Timer_A1_ms_elapsed = 0;


static uint32_t Timer_elapsed = 0;

static uint8_t turn_around = 0;

enum
{
    center = 0x18,
    slightly_left_fc = 0x1C,
    slightly_right_fc = 0x38,
    far_left_fc = 0x01,
    far_right_fc = 0x80,
    left_turn = 0xF8,
    right_turn = 0x1F,
    t_intersection = 0xFF,
    dead_end = 0x00
} Line_Position;

void Detect_Line_Position(uint8_t reflectance_sensor_data)
{

    if (reflectance_sensor_data != dead_end)
    {
        Timer_elapsed = 0;
    }

    switch(reflectance_sensor_data)
        {
            case center:
            {
                LED1_Output(RED_LED_OFF);
                LED2_Output(RGB_LED_GREEN);
                Motor_Forward(PWM_NOMINAL, PWM_NOMINAL);
                break;
            }
            case slightly_left_fc:
            {
                LED1_Output(RED_LED_OFF);
                LED2_Output(RGB_LED_YELLOW);
                Motor_Forward(PWM_NOMINAL, 1700);
                break;
            }
            case slightly_right_fc:
            {
                LED1_Output(RED_LED_OFF);
                LED2_Output(RGB_LED_PINK);
                Motor_Forward(1700, PWM_NOMINAL);
                break;
            }
            case far_left_fc:
            {
                LED1_Output(RED_LED_OFF);
                LED2_Output(RGB_LED_WHITE);
                Motor_Right(1700,1700);
                break;
            }
            case far_right_fc:
            {
                LED1_Output(RED_LED_OFF);
                LED2_Output(RGB_LED_SKY_BLUE);
                Motor_Left(1700,1700);
                break;
            }
            case left_turn:
            {
                LED1_Output(RED_LED_ON);
                LED2_Output(RGB_LED_WHITE);
                Motor_Left(1000,2000);
                break;
            }
            case right_turn:
            {
                LED1_Output(RED_LED_ON);
                LED2_Output(RGB_LED_SKY_BLUE);
                Motor_Right(2000, 1000);
                break;
            }
            case t_intersection:
            {
                LED1_Output(RED_LED_OFF);
                LED2_Output(RGB_LED_BLUE);
                Motor_Right(PWM_NOMINAL, PWM_NOMINAL);
                break;
            }
            case dead_end:
            {
                LED1_Output(RED_LED_OFF);
                LED2_Output(RGB_LED_RED);

                Timer_elapsed++;

                if (Timer_elapsed >= 150)
                {
                    Motor_Stop();
                }

                break;
            }
            default:
            {
                LED1_Output(RED_LED_OFF);
                LED2_Output(RGB_LED_OFF);
                break;
            }
        }
}

void Timer_A1_Periodic_Task(void)
{
    // Increment Timer_A1_ms_elapsed by 1 every time the Timer A1 periodic interrupt occurs
    Timer_A1_ms_elapsed++;

    // Start the process of reading the reflectance sensor array every 10 ms (i.e. 10, 20, 30, ...)
    if ((Timer_A1_ms_elapsed % 10) == 0)
    {
        Reflectance_Sensor_Start();
    }

    // Finish reading the reflectance sensor sensor array after 1 ms (i.e. 11, 21, 31, ...)
    if ((Timer_A1_ms_elapsed % 10) == 1)
        {
            uint8_t Reflectance_Sensor_Data = Reflectance_Sensor_End();
            Detect_Line_Position(Reflectance_Sensor_Data);
        }

}

int main(void)
{
    // Ensure that interrupts are disabled during initialization
    DisableInterrupts();

    // Initialize the 48 MHz Clock
    Clock_Init48MHz();

    // Initialize the built-in red LED and the RGB LED on the MSP432 microcontroller
    LED1_Init();
    LED2_Init();

    // Initialize the EUSCI_A0_UART module
    EUSCI_A0_UART_Init_Printf();

    // Initialize the 8-channel QTRX Reflectance Sensor Array module
    Reflectance_Sensor_Init();

    // Initialize the SysTick timer to generate periodic interrupts every 1 ms
    SysTick_Interrupt_Init(SYSTICK_INT_NUM_CLK_CYCLES, SYSTICK_INT_PRIORITY);

    // Initialize Timer A1 periodic interrupts every 1 ms
    Timer_A1_Interrupt_Init(&Timer_A1_Periodic_Task, TIMER_A1_INT_CCR0_VALUE);

    // // Initialize the motors
    Motor_Init();

    // Enable the interrupts used by the modules
    EnableInterrupts();

    while(1)
    {

    }
}
