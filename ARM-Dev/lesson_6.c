
// lesson 6 - Bit wise operators in C

#include"tm4c123gh6pm.h"

#define RCGCGPIO ( *((unsigned int *) 0x400FE608U) ) // wake up block F
#define GPIOF_BASE 0x40025000U

#define GPIOF_DIR (*((unsigned int *)(GPIOF_BASE + 0x400U)) )// pin Direction as output
#define GPIOF_DEN (*((unsigned int *)(GPIOF_BASE + 0x51CU)) )// pin set to Digital Enable
#define GPIOF_DATA (*((unsigned int *)(GPIOF_BASE + 0x3FCU)) )
//define values for the LED bin value- note it converts from dec to bin automatically

#define red 2
#define blue 4
#define green 8
#define white 14
#define off 0;

 // this is a good way to define bit positions that helps avoid mistakes
#define LED_RED (1U << 1)// uses bit shift as apposed to my direct assignment above
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)

int main()
{
      SYSCTL_RCGCGPIO_R  |= 32; // 0x20u// the complete bit set notation here (see below) would be |= (1U <<5)
      GPIO_PORTF_DIR_R |= 14; //0x0EU
      GPIO_PORTF_DEN_R |= (LED_RED | LED_BLUE | LED_RED );// this improves readability over how it was done in the above two lines and also helps the compiler understand your intent.
      // while the above |= is not mandatory it is the bit set idium and indicates your intention of setting bits not setting a value.

      int volatile counterA = 0;

      //GPIOF_DATA = blue;// blue on
      GPIO_PORTF_DATA_R = LED_BLUE;
      while (1){
         int volatile counter = 0;
         while (counter < 290000){
            ++counter;
            }

        //can no longer turn on red like we did before as it will mess with the blue value
        //GPIO_PORTF_DATA_R = red;
        // the following requires read write permissions
        GPIO_PORTF_DATA_R |= red;// we or in the red and turn on that bit
        //also valid
        //GPIO_PORTF_DATA_R |= red;
           counter = 0;
           while (counter < 290000){
             ++counter;
           }
         GPIO_PORTF_DATA_R  =  GPIO_PORTF_DATA_R ^ red;   // now we xor it back out or turn it off but leave blue still on
        // or we could do this
        //GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R & ~LED_RED;
      }
      //turn every thing back off
      //RCGCPIO = off;
     SYSCTL_RCGCGPIO_R  = off; // or 0 would work also
     //GPIOF_DIR = off;
     GPIO_PORTF_DIR_R = off;
     //GPIOF_DEN = off;
     GPIO_PORTF_DEN_R = off;
    return 0;
}
