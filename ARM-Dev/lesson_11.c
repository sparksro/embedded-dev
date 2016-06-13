// lesson 11 - Embedded programing stdint.h and mixing types
//
#include <stdint.h>
#include"tm4c123gh6pm.h"
#include "delay.h"

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)

uint8_t u8a, u8b;
uint16_t u16c, u16d;
uint32_t u32e, u32f;

int8_t s8;
int16_t s16;
int32_t s32;// note that the storage locations of these variables is different than
// the order we specified them.  The compiler will change order so never assume your order will
// be preserved.

int main()
{
  u8a = sizeof(u8a);
  u16c = sizeof(uint16_t);
  u32e = sizeof(uint32_t);

  u8a = 0xa1u;  // memory address 2000000c
  u16c = 0xc1c2u; // memory address 20000008
  u32e = 0xe1e2e3e4u;  // memory address 20000000

  u16c = 40000u;
  u16d = 30000u;

  u16c = 100u;
  //In mixed signed and unsigned expressions he C standard is to promote the signed variable to unsigned. The fix
  // is an explicit cast from unsigned to signed.
  // Thus you should avoid mixing signed and unsigned variables with out a cast to the desired type.

  //u32e = u16c + u16d; // THis should result in -90 but note that this works on this board as its native data type size
  // is 32 bits but if the boards native type was 16 bits it would get truncated in overflow during
  // the addition.  The following is much more portable as it insures the data type is 32 bits thus the over flow is not lost.
  u32e = (uint32_t)u16c + u16d;
  // in the 16 bit processor it promotes the variables to 32 bit but in the 32 bit processor
  // it requires no more computational cycles.

  //s32 - 10 - u16c; // This works here as the variables are 32 bit and the 2s comp component is not lost and reinterpreted to 32 bit signed.
  //But would fail in a 16 bit processor as the 2s comp part designating it as negative is lost in the 16 bit variables.  The variable is not signed
  // thus not sign extended into the 32bit register and interpreted as unsigned. (Not due to lack of space for the variable - insufficient number of bits so it can be cast to a 16 bit signed version.)
  // The following is better and portable.
  s32 = 10 - (int16_t)u16c; // here we cast to a 16 bit signed version
  //also note that C also auto promotes these values to normal 32 bit int
  u8b = u8a;
  u16d = u16c;
  u32f = u32e;

  // The following behaves unexpectedly with out the int32_t cast and jumps to the else.
  if ((int32_t)u32e > -1) {// fixed with an explicit cast
    u8a = 1u;
  }
  else {
    u8a = 0u;
  }

  // In the following you might think that this if would be true.
  u8a = 0xffu;// = 255
  if(~u8a == 0x00u) {// but it will always be false as the u8a variable is signed.
    u8b = 1u;
  }
  if((uint8_t)(~u8a) == 0x00u) {// The answer is to convert back down to unsigned.
    u8b = 1u;
  }


  // Arm uses little endian configuration.
  //   -- Arm instructions --
  // LDRB, STRB - read and write bytes
  // LDRH, STRH - read and write half words
  // LLDR, SDR - read and write whole words
  //

  SYSCTL_RCGCGPIO_R |= (1U << 5);// enable clock for GPIOF
  SYSCTL_GPIOHBCTL_R = (1U << 5);// enable AHB for GPIOF
  GPIO_PORTF_AHB_DIR_R |= ( LED_RED | LED_BLUE | LED_GREEN );
  GPIO_PORTF_AHB_DEN_R |= ( LED_RED | LED_BLUE | LED_GREEN );

  GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
  while (1){
    GPIO_PORTF_AHB_DATA_BITS_R [LED_RED] = LED_RED;
    delay(350000);
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
    delay(350000);
    }

    //return 0;
}

