#include "deca_device_api.h"
#include "mutex.h"
#include "driverlib.h"

void initDWMinterrupt() {
    GPIO_setAsInputPinWithPullDownResistor(
        GPIO_PORT_P2,
        GPIO_PIN0
    );

    GPIO_selectInterruptEdge(
        GPIO_PORT_P2,
        GPIO_PIN0,
        GPIO_LOW_TO_HIGH_TRANSITION
    );

    GPIO_clearInterrupt(
        GPIO_PORT_P2,
        GPIO_PIN0
    );

    GPIO_enableInterrupt(
        GPIO_PORT_P2,
        GPIO_PIN0
    );
}

decaIrqStatus_t decamutexon (void) {
    decaIrqStatus_t s = GPIO_getInterruptStatus(
        GPIO_PORT_P2,
        GPIO_PIN0
    );
    if(s) {
        GPIO_disableInterrupt(
            GPIO_PORT_P2,
            GPIO_PIN0
        );
    }
    return s;
}

void decamutexoff (decaIrqStatus_t state) {
    if(state) {
        GPIO_enableInterrupt(
            GPIO_PORT_P2,
            GPIO_PIN0
        );
    }
}

void P2_ISR(void) {
    dwt_isr();
    GPIO_clearInterrupt(
        GPIO_PORT_P2,
        GPIO_PIN0
    );
}
