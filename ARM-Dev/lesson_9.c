// lesson 9 - More Functions, the Stack, Recursion and AAPCS
//
//
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

//delay function prototype and definition moved to their own files.

unsigned factIterative(unsigned n);
unsigned factRecursive(unsigned n);

int main()
{
      unsigned volatile x;
      // A recursive function would not normally be used in embedded programming as it uses a lot of memory.
      // A better version for embedded is iterative or better yet a look up table.
      x = factRecursive(0u);// returns 1 in R0
      x = 2u + 3u*factRecursive(1u); // returns 2+3*(1!) = 5
      (void)factRecursive(5u); // returns 5! or 78u = 120 decimal
      // This iterative version was not given in the lesson but added by me as another example.
      // This is a better function for embedded dev.
      x = factIterative(0u);// returns 1 in R0
      x = 2u + 3u*factIterative(1u); // returns 2+3*(1!) = 5
      (void)factIterative(5u); // returns 5! or 78u = 120 decimal
      i
      //AAPCS Document describes the function calling convention rules. Ex when to use
      // what registers such as LR, R0, R1 and R2.  The caller and callie must know the
      // conventions of where to return and where to read the returned data.  AAPCS = Arm Application Procedure Call Stack
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
      // note: Pe111 warning that statement is unreachable is because while(1) {} loop above never terminates.
      // You can ignore it or change the while to a count loop so that it eventually ends say after 5000 loops or comment out the return 0.
    return 0;
}


unsigned factIterative(unsigned n){
  // iterative method
  unsigned volatile f = 1u;
  unsigned int i;
  for (i = 1; i <= n ; i++){
    f *= i;
  }
  return f;
}

unsigned factRecursive(unsigned n){
  //ma mathematical def of factorial recursive
  //0! = 1
  //n! = n*(n-1)! for n > 0

  if (n == 0u){
    return 1u;
  }
  else {
    return (n * factRecursive(n - 1u) );
  }
}
