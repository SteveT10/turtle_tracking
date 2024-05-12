/**
 * decamutexoff() and decamutexon() implementations for msp430fr2476.
 * IRQ and Init processes also added.
 *
 * @author Steven Tieu.
 * @version 4-28-2024
 */
#include "deca_device_api.h"
#include "mutex.h"
#include <driverlib.h>

//NOTE: Untested. I do not know if this file works completely.
static uint8_t PORT;
static uint16_t PIN;
static uint16_t IRQ_VECTOR; //TODO: Test if this works.

void initDWMinterrupt(port, pin) {
    PORT = port;
    PIN = pin;

    switch(port) {
        case GPIO_PORT_P1:
            IRQ_VECTOR = PORT1_VECTOR;
            break;
        case GPIO_PORT_P2:
            IRQ_VECTOR = PORT2_VECTOR;
            break;
        case GPIO_PORT_P3:
            IRQ_VECTOR = PORT3_VECTOR;
            break;
        case GPIO_PORT_P4:
            IRQ_VECTOR = PORT4_VECTOR;
            break;
        case GPIO_PORT_P5:
            IRQ_VECTOR = PORT5_VECTOR;
            break;
        default: //GPIO_PORT_P6:
            IRQ_VECTOR = PORT6_VECTOR;
        //TODO: Error handling needed for Invalid Port or Unsupported MCU.
    }

    GPIO_setAsInputPinWithPullDownResistor(
        PORT,
        PIN
    );

    GPIO_selectInterruptEdge(
        PORT,
        PIN,
        GPIO_LOW_TO_HIGH_TRANSITION
    );

    GPIO_clearInterrupt(
        PORT,
        PIN
    );

    GPIO_enableInterrupt(
        PORT,
        PIN
    );
}

decaIrqStatus_t decamutexon (void) {
    decaIrqStatus_t state = GPIO_getInterruptStatus(
        PORT,
        PIN
    );
    if(state) {
        GPIO_disableInterrupt(
            PORT,
            PIN
        );
    }
    return state;
}

void decamutexoff (decaIrqStatus_t state) {
    if(state) {
        GPIO_enableInterrupt(
            PORT,
            PIN
        );
    }
}

//DWM1000 Pin Interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = IRQ_VECTOR
__interrupt void DWM1000_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(IRQ_VECTOR))) DWM1000_ISR(void)
#else
#error Compiler not supported!
#endif
{
    dwt_isr();
    GPIO_clearInterrupt(
        PORT,
        PIN
    );
}
