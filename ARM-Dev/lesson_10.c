// lesson 10 - More Functions, Overflow and Pitfalls
// In this lesson we will break push the stack to the breaking point by hacking the recursive function.
// In the last part of the lesson pointers are covered but the notes are not recorded here as its fairly
// standard C stuff.
#include"tm4c123gh6pm.h"
#include "delay.h"

#define RCGCGPIO ( *((unsigned int *) 0x400FE608U) )
#define GPIOF_BASE 0x40025000U
#define GPIOF_DIR (*((unsigned int *)(GPIOF_BASE + 0x400U)) )
#define GPIOF_DEN (*((unsigned int *)(GPIOF_BASE + 0x51CU)) )
#define GPIOF_DATA (*((unsigned int *)(GPIOF_BASE + 0x3FCU)) )

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)

unsigned factRecursive(unsigned n);

int main()
{
      unsigned volatile x;

      x = factRecursive(0u);
      x = 2u + 3u*factRecursive(1u);
      //(void)factRecursive(5u); //used for the stack overflow
      (void)factRecursive(7u); // used for corrupting the stack

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

unsigned factRecursive(unsigned n){
  //unsigned foo[100];
  // This will tax the stack to the breaking point and generate a stack overflow.  At 5 levels of the recursive call it
  // runs out of room.  On the 7th loop of running it it crashes and the program
  // stops running.   Note here the stack pointer points at 0x20000000 the end of the stack.  If you click the red hand above and look in Dissembly you will see the
  // it had trouble at the BusFault Handler. This is an exception handler in the IAR startup code.
  // Which the linker links in to your main program.

  // next we will corrupt the stack.  This indexes into the array out of bounds and corrupts the lr pointer so it
  // can no longer return correctly.  Because it can not return from main properly the stack just
  // continues to grow until it fills and crashes.
  unsigned foo[6];
  foo[n] = n;
  if (n == 0u){
    return 1u;
  }
  else {
    return foo[n] * factRecursive(n - 1u);
  }
}

// The stack size can be changed by going to project options > linker.  Check override default and click edit.  Go to stack/heap tab.  The default is 2kBytes.  1KB should be sufficient
// or 1024.  The heap is the general location for malloc and free operations (allocated memory.) In real time embedded programing it generally causes more
// harm than good and it should not be used. So set it to 0, save and click ok.
