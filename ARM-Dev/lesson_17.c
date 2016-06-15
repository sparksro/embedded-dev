// Lesson 17
// In the last lesson we changed the structure of the program to use the systic
// interrupt to change the state of the LED.  In this lesson we examine the interrupt
// at a closer level.
//
#include "TM4C123GH6PM.h"
#include "bsp.h"

int main() {
    SYSCTL->RCGCGPIO  |= (1U << 5); /* enable Run mode for GPIOF */
    SYSCTL->GPIOHBCTL |= (1U << 5); /* enable AHB for GPIOF */
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);

    SysTick->LOAD = SYS_CLOCK_HZ/2U - 1U;
    SysTick->VAL  = 0U;
    SysTick->CTRL = (1U << 2) | (1U << 1) | 1U;

    SysTick_Handler();// The ability to call interrupt handlers as a regular c function
    // is unique feature of the ARM cortex M processor. Most all other chips do not allow this.
    // This is because no other processors allow interrupts to be regular C functions. Other
    // processors require a special entry code and then require a special way to return. Interrupts
    // generally have to save and restore more registers than regular C functions.
    // This lesson is a good one to watch one or multiple times.
    __enable_interrupt();
    while (1) {
        GPIOF_AHB->DATA_Bits[LED_GREEN] = LED_GREEN;
        GPIOF_AHB->DATA_Bits[LED_GREEN] = 0U;
    }
    //return 0;
}
