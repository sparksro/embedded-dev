// Lesson 20
// In this lesson we simulate race conditions and a methods how to solve.
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

    SysTick_Handler();

    __enable_irq();
    while (1) {
        //GPIOF_AHB->DATA_Bits[LED_GREEN] = LED_GREEN;
        //GPIOF_AHB->DATA_Bits[LED_GREEN] = 0U;
    	//GPIOF_AHB->DATA = GPIOF_AHB-> | LED_GREEN;

    	GPIOF_AHB->DATA |= LED_GREEN;// equivalent to above
    	//GPIOF_AHB->DATA = GPIOF_AHB-> & ~LED_GREEN;
    	GPIOF_AHB->DATA &= ~LED_GREEN;//equivalent to above

    	// Doing the above actually sets us up for a race condition.  Watch the video to see how to diagnose it.
    	// Race conditions can cause disasters and are hard to diagnose.  There are two ways to help
    	// prevent them.  One mutual exclusion
    	__disable_irq();//one way of doing it.
    	GPIOF_AHB->DATA |= LED_GREEN;//The piece of code between disable and enable is a critical section.
    	// This makes the code atomic. The better solution however was our original code that uses the
    	// data bits array and each is accessed separately so there is no race conditions.
    	__enable_irq();// this will prevent preemption and eliminate the race condition.

    	__disable_irq();
    	GPIOF_AHB->DATA &= ~LED_GREEN;
    	__enable_irq();
    }
    //return 0;
}
