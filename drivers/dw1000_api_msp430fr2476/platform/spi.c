#include "deca_device_api.h"
#include "deca_types.h"
#include <msp430.h>
#include <driverlib.h>
#include "spi.h"

int writetospi(uint16 headerLength, const uint8 *headerBuffer, uint32 bodylength, const uint8 *bodyBuffer){
    while(EUSCI_A_SPI_isBusy(EUSCI_A0_BASE)); //Wait for SPI to be free,
    int status = DWT_SUCCESS;
    uint16 i;
    for(i = 0; i < headerLength; i++) {
        EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, *headerBuffer);
        headerBuffer++;
    }
    
    for(i = 0; i < bodylength; i++) {
        EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, *bodyBuffer);
        bodyBuffer++;
    }

    if(UCA0STATW & (UCOE | UCFE)) {//If Error occurred.
        status = DWT_ERROR;
    }
    return status;
}

int readfromspi(uint16 headerLength, const uint8 *headerBuffer, uint32 readlength, uint8 *readBuffer) {
    while(EUSCI_A_SPI_isBusy(EUSCI_A0_BASE)); //Wait for SPI to be free,
    int status = DWT_SUCCESS;
    uint16 i;
    for(i = 0; i < headerLength; i++) {
        EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, headerBuffer[i]);
    }
    
    for(i = 0; i < readlength; i++) {
        readBuffer[i] = EUSCI_A_SPI_receiveData(EUSCI_A0_BASE);
    }

    if(UCA0STATW & (UCOE | UCFE)) {//If Error occurred.
        status = DWT_ERROR;
    }

    return status;
}

int initSpi(uint8_t selectedPort, uint16_t selectedPins, uint8_t enPort, uint8_t enPin) {
    EUSCI_A_SPI_remapPins(EUSCI_A0_BASE, USCIA0RMP); //Change to alternative pins for A0 module
    GPIO_setAsPeripheralModuleFunctionInputPin(
        selectedPort,
        selectedPins,
        GPIO_PRIMARY_MODULE_FUNCTION
    );
    GPIO_setAsPeripheralModuleFunctionInputPin(
        enPort,
        enPin,
        GPIO_PRIMARY_MODULE_FUNCTION
    );

    PMM_unlockLPM5();

    //Initialize Master
    EUSCI_A_SPI_disable(EUSCI_A0_BASE);
    EUSCI_A_SPI_initMasterParam param = {0};
    param.selectClockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK;
    param.clockSourceFrequency = CS_getSMCLK();
    param.desiredSpiClock = 500000; //In Hz
    param.msbFirst = EUSCI_A_SPI_MSB_FIRST;
    param.clockPhase = EUSCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    param.clockPolarity = EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
    param.spiMode = EUSCI_A_SPI_4PIN_UCxSTE_ACTIVE_LOW;
    EUSCI_A_SPI_select4PinFunctionality(EUSCI_A0_BASE, EUSCI_A_SPI_ENABLE_SIGNAL_FOR_4WIRE_SLAVE); //Mst controls EN
    EUSCI_A_SPI_initMaster(EUSCI_A0_BASE, &param);

    EUSCI_A_SPI_enable(EUSCI_A0_BASE); //Enable SPI module
    __delay_cycles(100); //Wait for slave to initialize

    return 0;
}
