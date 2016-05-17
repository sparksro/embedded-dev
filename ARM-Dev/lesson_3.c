
//Lesson 3 - 
int counter2 = 0;

int main()
{
  // Variables and pointers -contined from lesson 2
  // counter2 above after move is declared globally and by nature will no longer appear in the 
  // the locals window as it is no longer local.  To view it click on view then watch -> watch 1
  // now in the window click on the first line and add the name of the global vaiable.
  // Note that the address is a large number. This is in ram.  Set the memory location
  // The address of the global variable, in this case 0x20000000 Right click on the memory
  // block appearing in the window and change to 4x to see 4 byte increments. Now you can
  // step through your code and watch the value change on the 20000000 line bellow.
  // Note that the LNR>N line iln the disassembly view is loading the value from main 
  // memory in to RO where you can also see the value is increasing in the register view.
  // Note the lines of code in the disasembly view.  Step through and notice
  // there are 9 lines of code to make up your two bellow.  Notice how it is pulling 
  // the value from main memeory loading it in R0 then it adds and then stores it back into the location 
  // where R1 is pointing which is our 0x20000000 location.
    while(counter2 < 5){
      ++counter2;
    }
   counter2 = 0;//reload
    int *p_int;// pointer stores the address of the varable 
    p_int = &counter2;// in this case it now stores the address of our global variable.
    while(*p_int < 21 ){// this works the same as above but now we use the pointer.
      // note we had to derefrence it. 
      ++*p_int;
      // The difference in the lower leve code here is that we now have less lines of code.  It is simpler and more efficient.  Compare
      // the two version in the disassembly view.  It is no longer useing R0 store the value but R0 now just
      // points to the Ram location of our global variable.  R1 now contains the value.  The lines of
      // code are fewer as it can now use the pointer we created and it does not have to use 
      // the registers quite as heavely.
    }
    
    p_int = (int *)0x20000002u;// u at the end designates it as unsigned 
    *p_int = 0xDEADBEEF;
    // this is kind of scarry- its an intentional miss allignment in the memory
    // note in the memeory window how part of the value is in one collumn (our previous counter variable) 
    // and part over the next address in memory. Pointers are powerfull and can be dangerious if used carelessly.
    //
    
    return 0;
}
