#ifndef _DECA_SPI_H_
#define _DECA_SPI_H_

#include "deca_device_api.h"
#include "deca_types.h"
#include "spi.h"
#include "driverlib.h"
#include <stdint.h>

/*
TO DO LIST
- deca_device_api.h
    - int writetospi (uint16 hLen, const uint8 *hbuff, uint32 bLen, const uint8 *buffer) ;
    - int readfromspi (uint16 hLen, const uint8 *hbuff, uint32 bLen, uint8 *buffer) ;
    
- deca_spi.h
    - initSpi()

- GPIO interupt on dwm1000 interrupt
    - Must call dwt_isr(), processes interrupt
    - NOTE: app code must set dwt_setcallbacks(), all cbs can be set to NULL.

- deca_irq.c: mutex locks on SPI lines, prevent interrupts.
    - decaIrqStatus_t decamutexon (void) ;
        - Called when SPI transaction starts.
    - void decamutexoff (decaIrqStatus_t state) ;
        - Called when SPI transaction finishes
    -NOTE: mspware constains status, disable, enable IRQ functions.

- deca_sleep.c: sleep function from platform.
    void deca_sleep (unsigned int time_ms) ;
*/

//Init
//Set Data Rate

int writetospi(uint16 headerLength, const uint8 *headerBuffer, uint32 bodylength, const uint8 *bodyBuffer){
    while(EUSCI_A_SPI_isBusy(EUSCI_A0_BASE)); //Wait for SPI to be free,

    uint16 i;
    for(i = 0; i < headerLength; i++) {
        EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, *headerBuffer);
        headerBuffer++;
    }
    
    for(i = 0; i < bodylength; i++) {
        EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, *bodyBuffer);
        bodyBuffer++;
    }
    //EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, );
    //Wait while SPI is transmitting.
}

int readfromspi(uint16 headerLength, const uint8 *headerBuffer, uint32 readlength, uint8 *readBuffer) {
    uint16 i;
    for(i = 0; i < headerLength; i++) {
        EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, headerBuffer[i]);
    }
    
    for(i = 0; i < readlength; i++) {
        readBuffer[i] = EUSCI_A_SPI_receiveData(EUSCI_A0_BASE);
    }
}

int initSpi() {
    // Configure SPI Pins for UCA0CLK, UCA0TXD/UCA0SIMO and UCA0RXD/UCA0SOMI
    /*
    * Select Port 5
    * Set Pin 0, Pin 1 and Pin 2 to input Secondary Module Function
    */
    GPIO_setAsPeripheralModuleFunctionInputPin(
    	GPIO_PORT_P5,
    	GPIO_PIN0 + GPIO_PIN#ifndef
    );
    EUSCI_A_SPI_remapPins(EUSCI_A0_BASE, USCIA0RMP); //Change to alternative pins for module

    //Initialize Master
    EUSCI_A_SPI_initMasterParam param = {0};
    param.selectClockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK;
    param.clockSourceFrequency = CS_getSMCLK();
    param.desiredSpiClock = 500000;
    param.msbFirst = EUSCI_A_SPI_MSB_FIRST;
    param.clockPhase = EUSCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    param.clockPolarity = EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
    param.spiMode = EUSCI_A_SPI_3PIN;
    EUSCI_A_SPI_initMaster(EUSCI_A0_BASE, &param);

    //Enable SPI module
    EUSCI_A_SPI_enable(EUSCI_A0_BASE);
    //Wait for slave to initialize
    __delay_cycles(100);
}

#endif /* _DECA_SPI_H_ */
