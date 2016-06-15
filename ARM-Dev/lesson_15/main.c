// lesson 15
#include "delay.h"

#include"tm4c_cmsis.h"

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)


// See bsp.c and startup_tm4c

int16_t x = -1;
uint32_t y = LED_RED | LED_GREEN;

int16_t sqr[] = {
  1*1,
  2*2,
  3*3,
  4*4
};

typedef struct {
  uint8_t y;
  uint16_t x;
} Point;

Point p1 = {
  123u,
  0x1234u
};

Point p2;

typedef struct {
  Point top_left;
  Point bottom_right;
}Window;

typedef struct {
  Point corners [3];
}Triangle;

Window w = {
  { 123u, 0x1234u },
  { 234u, 0x6789u },
};

Window w2;
Triangle t;

int main()
{
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
  pp->x = 1u;
  wp->top_left = *pp;


  SYSCTL->RCGC2 |= (1U << 5);
  SYSCTL->GPIOHSCTL = (1U << 5);

  GPIOF_HS->DIR |= ( LED_RED | LED_BLUE | LED_GREEN );
  GPIOF_HS->DEN |= ( LED_RED | LED_BLUE | LED_GREEN );

  GPIOF_HS->DATA_Bits[LED_BLUE] = LED_BLUE;
  while (1){
    GPIOF_HS->DATA_Bits[LED_RED] = LED_RED;
    delay(350000);

    GPIOF_HS->DATA_Bits[LED_RED] = 0;
    delay(350000);
    }

    //return 0;
}
