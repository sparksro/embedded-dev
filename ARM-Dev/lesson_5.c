
// lesson 5 - Preprocessor and volatile memory
  
//#include"lm4f120h5qr.h" 
// This is the .h file he used in the example however I am using the tm4c123gxl board
// I did an extensive search on line and had a hard time finding the .h file for it.  I finally found one 
// here: http://users.ece.utexas.edu/~valvano/arm/index.htm  That is listed for both the tm4c123 and tm4c1294 boards
// I beleive this to work for my board but we will see.  There is also some interesting project code at that site.  
// Update - Confirmed that his header also works for this project

#include"tm4c123gh6pm.h"
 //I beleive this to be the correct header file for my board and is the only version I could locate.
// If you take a look at some of the define statement in this file you will note most are of the type volitile
// this tells the copiler that the object might change even though no statements in the program appear to change it.
// My guess is that his .h file would work in most cases for my board but this is far from tested.  My observations so far with GPIO are that
// The port address he has refferenced are the same on this board.
 

// Change code to use predifined macros -prev def and calls left in but commented out
  
// Take code from lesson 4 and define as preprocessor macros 
// The compiler does not see this code as any different than the way we had it before but it makes it much
// more human readable.
/*  
#define RCGCGPIO ( *((unsigned int *) 0x400FE608U) ) // wake up block F
// we can also first define a base address then add to it
#define GPIOF_BASE 0x40025000U
// Then add the offset
#define GPIOF_DIR (*((unsigned int *)(GPIOF_BASE + 0x400U)) )// pin Dirrection as output
#define GPIOF_DEN (*((unsigned int *)(GPIOF_BASE + 0x51CU)) )// pin set to Digital Enable 
#define GPIOF_DATA (*((unsigned int *)(GPIOF_BASE + 0x3FCU)) )
//define values for the LED bin value- note it converst from dec to bin automatically 
*/   
#define red 2
#define blue 4
#define green 8
#define white 14
#define off 0;
  
 int main()
{ 
      // now we write it in C
      //RCGCGPIO = 32;// turn on or wake up the GPIO F block - dec 32, bin 100000 by turning on the clock
      // 0x20u in the example he continues to use this one - its not easy to find in the .h code and I had to look it up by the hex number
      SYSCTL_RCGCGPIO_R  = 32; // 0x20u
      //GPIOF_DIR = 14;// set F block pin dirrection as output
      GPIO_PORTF_DIR_R = 14; //0x0EU
      //GPIOF_DEN = 14;// set the function of the pins to digital output
      GPIO_PORTF_DEN_R = 14;
      
      int volatile counterA = 0;
      while (counterA < 30){
        //GPIOF_DATA = red;// red on
        GPIO_PORTF_DATA_R = red;
        int volatile counter = 0;// the key word volatile here keeps the compiler from optimizing the delay loop away.  If 
        // optimization was set to high it would see these loops as having no value so would optimize them out.  The volatile key word prevents this.
        while (counter < 190000){
            ++counter;
            }
            
            //GPIOF_DATA = off;// red off
            GPIO_PORTF_DATA_R = off;
            counter = 0;
            while (counter < 190000){
            ++counter;
            }
            
            //GPIOF_DATA = blue;// blue on
            GPIO_PORTF_DATA_R = blue; 
            counter = 0;
            while (counter < 190000){
            ++counter;
            }
            
            //GPIOF_DATA = off;// blue off
            GPIO_PORTF_DATA_R = off;
            counter = 0;
            while (counter < 190000){
            ++counter;
            }
            
            //GPIOF_DATA = green;// green on
            GPIO_PORTF_DATA_R = green;
            counter = 0;
            while (counter < 190000){
            ++counter;
            }
            
            //GPIOF_DATA = off;// green off
            GPIO_PORTF_DATA_R = off;
            counter = 0;
            while (counter < 190000){
            ++counter;
            }
            
            //GPIOF_DATA = white;// white on (all three)
            GPIO_PORTF_DATA_R = white;
            counter = 0;
            while (counter < 190000){
            ++counter;
            }
            
            //GPIOF_DATA = off;// white off
            GPIO_PORTF_DATA_R = off;
            counter = 0;
            while (counter < 190000){
            ++counter;
            }
            ++counterA;
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
