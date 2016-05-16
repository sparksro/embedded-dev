
//Lesson 2 - Flow Controll
int main()
{
    unsigned int counter = 0;
    //Note the at the PC in the register window is the instruction pointer as we step 
    // through the increments the addresss number changes.
    ++counter;
    ++counter;
    ++counter;
    //when in the while loop the ocunter only points at two addesss ie the two lines of the loop.
    // if you look at the registeres you will see that register
    // R0 is being used to hold the value of counter.  It moves it into that register and looking
    // at the Disassembly view you can see it adds R0 to R0 to get the new value.
   // When its down with the code above it jumps over a couple lines.  One of the lines it jumps over is a B.N
    // This is a branch.  It then jumps tot the cmp line where it compares R0 to 21 in the while loop.
    // Note that the while loop adds complexity to your code thus takes more time.  If you 
    // Need speed consider something like incemnting the counter a few more times per loop.
    // THis will decrease the amount of times it enters the desision structure.
    while(counter < 21 ){
      ++counter;
    }
    
    // THis if counter uses a bit wise conpairison to tell if the value in counter is 
    // odd or even.
    if ((counter & 1) != 0) {
      // do something when the counter is odd.
    }
    else{ 
      // do something else
    }
    
    
    //If you expand the APSR register you will wee that the N at the end Negative
    // Sets the negative flag (or bit) to 1 as it it uses subtraction to compare.
    
    
    return 0;
}
