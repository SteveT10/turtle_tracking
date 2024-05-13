/**
 * Test file for readfromspi() implementation.
 * Transmits a byte 0x00, then sends 4 dummy bytes in one SPI transmission.
 * Expect to receive 0xDECA0130,
 *
 * NOTE: Still unable to pass this test (5/12/2024)
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
 * @version 5-12-2024
 */
#include "deca_device_api.h"
#include "deca_spi.h"
#include "driverlib.h"
#include "lcd.h"
#include <stdint.h>

int main(void) {
    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);
    PMM_unlockLPM5();

    initLCD();
    deca_sleep(10);

    initSpi(GPIO_PORT_P5, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2, GPIO_PORT_P4, GPIO_PIN7);
    reset_DW1000(); /* Target specific drive of RSTn line into DW1000 low for a period. */
    setSpiRateLow();
    uint8_t buf[] = {0x00};
    uint8_t buf2[4];
    uint8_t buf3[] = {0x00};
    uint8_t buf4[] = {0x01, 0x02, 0x03, 0x04};
    while(1) {
        readfromspi(1, buf, 4, buf2);
        //writetospi(sizeof(buf3), buf3, sizeof(buf4), buf4);
        //lcd_display_str(buf2);
        deca_sleep(1000);
    }
}
