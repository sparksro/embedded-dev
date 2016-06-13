
// lesson 8 - Functions and the Stack
// Not many notes taken in this lesson.  Its best if you view the original lesson.
//This is not to minimize the lesson as it is an important one.
#include"tm4c123gh6pm.h"

#define RCGCGPIO ( *((unsigned int *) 0x400FE608U) )
#define GPIOF_BASE 0x40025000U
#define GPIOF_DIR (*((unsigned int *)(GPIOF_BASE + 0x400U)) )
#define GPIOF_DEN (*((unsigned int *)(GPIOF_BASE + 0x51CU)) )
#define GPIOF_DATA (*((unsigned int *)(GPIOF_BASE + 0x3FCU)) )

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)

void delay(int delay_time) {
  int volatile counter = 0;
  while (counter < delay_time){
      ++counter;
 }
}

int main()
{
      SYSCTL_RCGCGPIO_R |= (1U << 5);
      SYSCTL_GPIOHBCTL_R = (1U << 5);
      GPIO_PORTF_AHB_DIR_R |= ( LED_RED | LED_BLUE | LED_RED );
      GPIO_PORTF_AHB_DEN_R |= ( LED_RED | LED_BLUE | LED_RED );

      GPIO_PORTF_AHB_DATA_R = LED_BLUE;
      while (1){

        GPIO_PORTF_AHB_DATA_BITS_R [LED_RED] = LED_RED;
        delay(350000);
        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
        delay(650000);

      }

    return 0;
}
