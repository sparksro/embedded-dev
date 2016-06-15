// lesson 16 - Interupts
#include <stdint.h>
#include "tm4c_cmsis.h"
#include "bsp.h"

int main()
{
// The delay function is an example of busy-wait polling. This lesson it becomes obsolete. It ties up the CPU completely
// and makes it unavailable for any other work.
// Interrupts are like an alarm clock to wake you or the CPU when the time is right.
// The CPU has an interrupt line.  As long as its low it fetches the next instruction but if the line is high
// then a preemption happens and it proceeds to process the interrupt.  The interrupt lines signal to high
// can happen any time Asynchronously and not according to the clock.  On the other hand instruction processing
// happens according to the clock.  Each task starts processing on the clock high.
// In Tiva C you can use SysTic for this function.

    SYSCTL->RCGC2 |= (1U << 5);
    SYSCTL->GPIOHSCTL = (1U << 5);
    GPIOF_HS->DIR |= ( LED_RED | LED_BLUE | LED_GREEN );
    GPIOF_HS->DEN |= ( LED_RED | LED_BLUE | LED_GREEN );

    SysTick->LOAD = SYS_CLOCK_HZ/2U - 1U;
    SysTick->VAL  = 0U;
      //set bits 2,1,0 for clock source, interupt inable and counter enable
    SysTick->CTRL = (1U << 2) | (1U << 1) | 1U;
    __enable_interrupt();// clears the premask bit and allows interrupts to get to the cpu.

    while (1){

    }

    //return 0;
}
