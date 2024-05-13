/**
 * Prints some different digits on 16x2 LCD. LCD is configured for 4 bit-mode.
 *
 *                  MSP430FR2476
 *                -----------------
 *            /|\|                 |
 *             | |                 |
 *             --|RST              |
 *               |                 |
 *               |             P2.2|-> Register Select
 *               |                 |
 *               |             P2.1|<- Read/Write
 *               |                 |
 *               |             P2.0|-> Enable
 *               |                 |
 *               |             P1.0|-> D4
 *               |                 |
 *               |             P1.1|-> D5
 *               |                 |
 *               |             P1.2|-> D6
 *               |                 |
 *               |             P1.3|-> D7
 *
 * Note: LCD can still encounter errors, reset if this occurs.
 */

#include "lcd.h"
#include "driverlib.h"
#include "deca_device_api.h"
void main(void) {
    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    PMM_unlockLPM5(); //This needs to be before LCD init.

    initLCD();
    deca_sleep(10); //Needs time to finish setting up LCD.

    char *numbers[] = {"1.0", "2.00", "'3.00'", "<four>", "FIVE?"};
    int count = 0;
    while(1) {
        displayLCD("Hello World!", numbers[count]);
        count++;
        count = count % 5;
        deca_sleep(1000);
    }
}

