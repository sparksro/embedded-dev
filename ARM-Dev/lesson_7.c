
// lesson 7 - Arrays and pointer arithmetic
// The following code uses arrays and arithmetic to make code that is interrupt safe.
// It is using the APB bus.  It is older and slower and was kept only for backward compatibility.
// We could use the AHB bus. (see p 46 of data sheet) The APB bus is default and to use the AHB bus we have to switch it.
// Need to find in the data sheet the instructions to switch to the high performance bus. (data sheet p256)
// Next go to the tm4c123gh6pm.h header file and look for the GPIOHBCTL register (line 2054)
#include"tm4c123gh6pm.h"

#define RCGCGPIO ( *((unsigned int *) 0x400FE608U) ) // wake up block F
#define GPIOF_BASE 0x40025000U
#define GPIOF_DIR (*((unsigned int *)(GPIOF_BASE + 0x400U)) )// pin Direction as output// add in the AHB to use these instead of those associated with the APB bus.
#define GPIOF_DEN (*((unsigned int *)(GPIOF_BASE + 0x51CU)) )// pin set to Digital Enable
#define GPIOF_DATA (*((unsigned int *)(GPIOF_BASE + 0x3FCU)) )

// this is a good way to define bit positions that helps avoid mistakes
#define LED_RED (1U << 1)// uses bit shift as apposed to my direct assignment above
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)

int main()
{
      SYSCTL_RCGCGPIO_R |= (1U << 5);
      SYSCTL_GPIOHBCTL_R = (1U << 5); //Set the bit to turn on the use of the AHB bus.
      GPIO_PORTF_AHB_DIR_R |= ( LED_RED | LED_BLUE | LED_RED );// change all the names to add the _AHB
      GPIO_PORTF_AHB_DEN_R |= ( LED_RED | LED_BLUE | LED_RED );

      GPIO_PORTF_AHB_DATA_R = LED_BLUE;
      while (1){

        //GPIO_PORTF_DATA_R |= LED_RED;
        // The next three methods are equivalent and produce the same de-assembled source code.
        // We can access it this way -  note its cast as a pointer then dereferenced
        //*(( unsigned long volatile *)(0x40025000 + (LED_RED << 2 ))) = LED_RED;  // the bit shift avoids the two non used lines AO and A1
        // or access like this. This next line indexes into the gpioF set of registers just like an array because that is what it is.  All 256 registers can be accessed like this.
        // This indexes only into the red bit.
        //*(GPIO_PORTF_DATA_BITS_R + LED_RED) = LED_RED;//pointer arithmetic
        //Probably the cleanest way to do it is this and is exactly the following pointer arithmetic
        GPIO_PORTF_AHB_DATA_BITS_R [LED_RED] = LED_RED;// array indexing

        int volatile counter[2] = {0,0};
           while (counter[0] < 290000){// note now we are using an array of counters or pointers (registers) and array arithmetic
             ++counter[0];
           }
         GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;

         while( *(counter + 1) < 290000){
            ++counter[1];
            }

      }

    return 0;
}
