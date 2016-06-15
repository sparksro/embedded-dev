/* Startup code for TM4C MCU */

int __vector_table[] @ ".intvec" = { //_@ ".intvec"  is special functionality provided by IAR to make sure this goes into the correct part of memory.  There is no standard C functionallity to do this.
  0,
  0
};