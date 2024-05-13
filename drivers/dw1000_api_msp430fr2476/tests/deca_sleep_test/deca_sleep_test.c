/**
 * Toggles a LED connected to P1.0 on and off every 1 second approximately.
 * Test file for deca_sleep implementation.
 *
 *              MSP430FR2476
 *           -----------------
 *       /|\|                 |
 *        | |                 |
 *        --|RST              |
 *          |                 |
 *          |             P1.0|-->LED
 *
 * @author Steven Tieu.
 * @version 4-28-2024
 */

#include "driverlib.h"
#include "deca_device_api.h"

int main(void) {
    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);
    PMM_unlockLPM5(); //Unlock Dev Board LED?

    // Set P1.0 to output direction
    GPIO_setAsOutputPin(
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings

    while(1) {
        // Toggle P1.0 output
        GPIO_toggleOutputOnPin(
            GPIO_PORT_P1,
            GPIO_PIN0
            );
        deca_sleep(1000);
    }

}
