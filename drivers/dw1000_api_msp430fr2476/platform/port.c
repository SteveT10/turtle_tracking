#include "port.h"
#include "driverlib.h"

void reset_DW1000(void) {
    //Pull low to reset
    GPIO_setAsOutputPin(DW1000_RST_PORT, DW1000_RSTn);
    GPIO_setOutputLowOnPin(DW1000_RST_PORT, DW1000_RSTn);

    //Can't be pulled high externally, go to tri-state by switching to input.
    GPIO_setAsInputPin(DW1000_RST_PORT, DW1000_RSTn);
}
