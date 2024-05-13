//Basic Project Template including platform, decadriver, and TI's driverlib.
//Copy this entire project.

#include "driverlib.h"

void main(void) {
    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);
    PMM_unlockLPM5(); //Switch Power Mode to allow for I/O.


}
