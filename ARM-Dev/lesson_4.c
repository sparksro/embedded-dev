
int main()
{
  // lesson 4 - Blink
  // If you have the board set the project options ->debuger->setup to ti-stellaris
  // and check the use flash loaders under download.  The other option is to run
  // in simulator mode.
  // With a board go to TI Stellaris and check reset will do system reset and then go
  // to project and choose rebuild all.
  
  // starting address of GPIO port F - 0x40025000
  
 // GPIO reg F base address  0x400F.E000 Offset 0x608
  // open symbolic memory view from View now paste in memory address 0x400F.E608
  // set this register value to 0x00000020 this turns on F on bit 5 with a binary 00100000
  // set address 40025400 to value 0x0000000e which = 1110 in binary or 14 dec -sets as output
  // set address 4002551c to the same
  // scroll up to 400253fc enter 0x00000002 this will turn the red led on by setting bit 1
  // set bit 2 by writting hex 4
  // set bit 3 by writting hex 8
  // set all three to 1 or bin 1110 = hex 14 or e turns all three on
  
  // now we write it in C
  *((unsigned int *) 0x400FE608U) = 0x20U;// turn on or wake up the GPIO F block - dec 32, bin 100000
  *((unsigned int *) 0x40025400U) = 0x0EU;// set F block pin dirrection as output
  *((unsigned int *) 0x4002551CU) = 0x0EU;// set the function of the pins to digital output
  int counterA = 0;
  
  while (counterA < 20){
    
    *((unsigned int *) 0x400253FCU) = 2;// red on
    int counter = 0;
    while (counter < 1000000){
    ++counter;
    }
    
    *((unsigned int *) 0x400253FCU) = 0;// red off
    counter = 0;
    while (counter < 1000000){
    ++counter;
    }
    
    *((unsigned int *) 0x400253FCU) = 4;// blue on
    counter = 0;
    while (counter < 1000000){
    ++counter;
    }
    
    *((unsigned int *) 0x400253FCU) = 0;// blue off
    counter = 0;
    while (counter < 1000000){
    ++counter;
    }
    
    *((unsigned int *) 0x400253FCU) = 8;// green on
    counter = 0;
    while (counter < 1000000){
    ++counter;
    }
    
    *((unsigned int *) 0x400253FCU) = 0;// green off
    counter = 0;
    while (counter < 1000000){
    ++counter;
    }
    
    *((unsigned int *) 0x400253FCU) = 14;// white on (all three)
    counter = 0;
    while (counter < 1000000){
    ++counter;
    }
    
    *((unsigned int *) 0x400253FCU) = 0;// white off
    counter = 0;
    while (counter < 1000000){
    ++counter;
    }
    ++counterA;
  }
  //turn every thing back off
  *((unsigned int *) 0x400FE608U) = 0x00U;
  *((unsigned int *) 0x40025400U) = 0x00U;
  *((unsigned int *) 0x4002551CU) = 0x00U;
    return 0;
}
