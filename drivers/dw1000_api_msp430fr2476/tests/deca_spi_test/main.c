/**
 * Sends the bytes for strings "header" and "body" on 4 pin SPI lines every second.
 * Test file for initspi() and writetospi() implementation.
 *
 *                  MSP430FR2476
 *                -----------------
 *            /|\|                 |
 *             | |                 |
 *             --|RST              |
 *               |                 |
 *               |             P5.2|-> Data OUT (UCA0SIMO)
 *               |                 |
 *               |             P5.1|<- Data IN  (UCA0SOMI)
 *               |                 |
 *               |             P5.0|-> Serial Clock Out (UCA0CLK)
 *               |                 |
 *               |             P4.7|-> Serial Enable (UCA0STE)
 *
 * @author Steven Tieu.
 * @version 4-28-2024
 */
#include "deca_device_api.h"
#include "deca_spi.h"
#include <driverlib.h>
#include <stdint.h>

int main(void) {
    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    initSpi(GPIO_PORT_P5, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2, GPIO_PORT_P4, GPIO_PIN7);
    setSpiRateLow();
    uint8_t buf[] = "header";
    uint8_t buf2[] = "body";
    while(1) {
        writetospi(sizeof(buf) - 1, buf, sizeof(buf2) - 1, buf2);
        deca_sleep(1000);
    }
}
