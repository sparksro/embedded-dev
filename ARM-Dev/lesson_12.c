// lesson 12 - structures and CMSIS
//
#include <stdint.h>
#include"tm4c123gh6pm.h"
//#include"tm4c_cmsis.h" // new header contains structures we can use to access data structure members.
// Note: I did not change the access methods as he did as there seems to be some access errors with the 7.4 version and Windows 10
// It did not know where to find the the core_cmsis.h file.  I copied the file into the project file and that just kicked the can down the
// road further leading to more errors.  It continues to work with the manual hard coding.
#include "delay.h"

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)

//typedef struct {
typedef __packed struct {
  uint8_t y;
  uint16_t x;
} Point;
// I ran all the following in the simulator:
// The IAR compiler provides an extra key word called __packed.  It forces the
// use of the extra byte between the data members.
// with out the key word the memory looks like this aa 00 04 00 with the 04 and last 00 being the 16 bit and the
// 01 being the 8 bit.  With the key word __packed it should eliminate the space. The memory  now looks like aa 03 00.  Its
// interesting that the size now is 3 and not 4.  As a further experiment I changed the value of p1.x to 0xbbccU and the memory
// then looks like this: aa cc bb 00.  The 00 is empty.

// Use packed structures judiciously - only when you need to avoid padding.
typedef struct {
  Point top_left;
  Point bottom_right;
}Window;

typedef struct {
  Point corners [3];
}Triangle;

Window w, w2;
Triangle t;

// Lesson goes on to review other structures and pointers.  Using pointers to structure members is ofter more efficient than passing the memory arround.
// The functionality that we hard coded / accessed as pre-processor macros previously to turn on and off the LEDs can be accessed through Structures.  See
//
Point p1, p2;

int main()
{
  //p1.x = sizeof(Point);
  p1.x = 0xbbccu;
  p1.y = 0xAAu;

  w.top_left.x = 1u;
  w.bottom_right.y = 2u;

  t.corners[0].x = 1u;
  t.corners[2].y = 2u;

  p2 = p1;
  w2 = w;// These innocent looking assignment of more complex structures uses a sizable amount of memory for an embedded device.
  //Its better to use pointers.
  Point *pp;//pointer to the point type
  Window * wp;// pointer to window type

  //intialize them
  pp = &p1;
  wp = &w2;

  // access the members of a structure
  (*pp).x = 1u;
  (*wp).top_left = *pp; // these are the C method of access
  // or
  // Alternate and equivalent way (C++)
  pp->x = 1u;
  wp->top_left = *pp;

  // We can access the same thing we did to turn LEDs on and off but with pre-defined structures pre-made by the manufacturer.
  // SYSCTL_RCGCGPIO_R |= (1U << 5);// enable clock for GPIOF
  //SYSCTL->RCGC2 |= (1U << 5);
  SYSCTL_GPIOHBCTL_R = (1U << 5);// enable AHB for GPIOF
  //SYSCTL->GPIOHSCTL = (1U << 5);

  GPIO_PORTF_AHB_DIR_R |= ( LED_RED | LED_BLUE | LED_GREEN );
  //GPIOF_HS->DIR |= ( LED_RED | LED_BLUE | LED_GREEN );
  GPIO_PORTF_AHB_DEN_R |= ( LED_RED | LED_BLUE | LED_GREEN );
  //GPIO_HS->DEN |= ( LED_RED | LED_BLUE | LED_GREEN );

  GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
  //GPIO_HS->DATA_Bits[LED_BLUE] = LED_BLUE;
  while (1){
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
    //GPIO_HS->DATA_Bits[LED_RED] = LED_RED;
    delay(350000);
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
    //GPIO_HS->DATA_Bits[LED_RED] = LED_RED;
    delay(350000);
    }

    //return 0;
}

