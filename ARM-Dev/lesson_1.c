
//notes:
// Under project-> options->general set target device to TI LM4F120HQR
// Use C99 under C/C++ tab
// set optimatizaton to low- this program wont work correctly under higher optimization
// this project uses the simulator. Make sure its selected under the driver catigory in project options -> debugger.
// Click on the run button (green rt arrow.) Go to view then click: dissasebly, memory, register, locals

// This lesson goes over how the computer counts at a low level.  I recomend you look it up and gov
int main()
{
    unsigned int counter = 0;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    
    // to run on the TI launch pad board click on stop debugning then go to project -> options
    // where it says Driver and simulator change to TI Stellaris
    // click on download tab and select verify download and use flash loaders then click ok.
    // atach your board via usb cable 
    
    return 0;
}
