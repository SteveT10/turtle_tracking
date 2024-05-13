#include "deca_device_api.h"
#include "deca_types.h"
#include <msp430.h>
#include <driverlib.h>
#include "deca_spi.h"
/*
 * TODO list:
 *      Make code more modular, allow for more SPI module choices.
 *
 *
 *
 */

static uint8_t CS;
static uint8_t CS_PORT;

void setCsPin(unsigned char isHigh);

int writetospi(uint16 headerLength, const uint8 *headerBuffer, uint32 bodylength, const uint8 *bodyBuffer){
    while(EUSCI_A_SPI_isBusy(EUSCI_A0_BASE)); //Wait for SPI to be free,
    int status = DWT_SUCCESS;
    uint16 i;

    setCsPin(0);
    for(i = 0; i < headerLength; i++) {
        EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, *headerBuffer);
        headerBuffer++;
    }
    
    for(i = 0; i < bodylength; i++) {
        EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, *bodyBuffer);
        bodyBuffer++;
    }
    setCsPin(1);
    if(UCA0STATW & (UCOE | UCFE)) {//If Error occurred.
        status = DWT_ERROR;
    }
    return status;
}

int readfromspi(uint16 headerLength, const uint8 *headerBuffer, uint32 bodyLength, uint8 *bodyBuffer) {
    while(EUSCI_A_SPI_isBusy(EUSCI_A0_BASE)); //Wait for SPI to be free,
    int status = DWT_SUCCESS;
    uint16 i;

    setCsPin(0);
    deca_sleep(1);
    for(i = 0; i < headerLength; i++) {
        EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, *headerBuffer);
        headerBuffer++;
        deca_sleep(1);
    }
    
    for(i = 0; i < bodyLength; i++) {
        *bodyBuffer = EUSCI_A_SPI_receiveData(EUSCI_A0_BASE);
        bodyBuffer++;
        deca_sleep(1);
    }
    setCsPin(1);
    if(UCA0STATW & (UCOE | UCFE)) {//If Error occurred.
        status = DWT_ERROR;
    }

    return status;
}

int initSpi(uint8_t selectedPort, uint16_t selectedPins, uint8_t csPort, uint8_t csPin) {
    EUSCI_A_SPI_remapPins(EUSCI_A0_BASE, USCIA0RMP); //Change to alternative pins for A0 module
    GPIO_setAsPeripheralModuleFunctionInputPin(
        selectedPort,
        selectedPins,
        GPIO_PRIMARY_MODULE_FUNCTION
    );

    /*GPIO_setAsPeripheralModuleFunctionInputPin(
    	csPort,
        csPin,
        GPIO_PRIMARY_MODULE_FUNCTION
    );*/

    //CS must be driven by GPIO for multi-byte transmissions.
    GPIO_setAsOutputPin(csPort, csPin);

    CS = csPin;
    CS_PORT = csPort;

    //Active low CS for dwm1000.
    setCsPin(1);


    EUSCI_A_SPI_disable(EUSCI_A0_BASE);
    EUSCI_A_SPI_initMasterParam param = {0};
    param.selectClockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK;
    param.clockSourceFrequency = CS_getSMCLK();
    param.desiredSpiClock = 500000; //3 Mhz
    param.msbFirst = EUSCI_A_SPI_MSB_FIRST;
    param.clockPhase = EUSCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    param.clockPolarity = EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
    param.spiMode = EUSCI_A_SPI_3PIN;
    //param.spiMode = EUSCI_A_SPI_4PIN_UCxSTE_ACTIVE_LOW;
    //EUSCI_A_SPI_select4PinFunctionality(EUSCI_A0_BASE, EUSCI_A_SPI_ENABLE_SIGNAL_FOR_4WIRE_SLAVE); //Mst controls EN
    EUSCI_A_SPI_initMaster(EUSCI_A0_BASE, &param);

    EUSCI_A_SPI_enable(EUSCI_A0_BASE); //Enable SPI module

    __delay_cycles(1000); //Wait for slave to initialize

    return 0;
}

void setCsPin(unsigned char isHigh) {
	if(isHigh) {
		GPIO_setOutputHighOnPin(CS_PORT, CS);
	} else {
		GPIO_setOutputLowOnPin(CS_PORT, CS);
	}
}

void setSpiRateLow() {
    EUSCI_A_SPI_disable(EUSCI_A0_BASE);
    EUSCI_A_SPI_changeMasterClockParam param = {0};
    param.clockSourceFrequency = CS_getSMCLK();
    param.desiredSpiClock = 500000; //3 Mhz or less is acceptable.
    EUSCI_A_SPI_changeMasterClock(EUSCI_A0_BASE, &param);

    EUSCI_A_SPI_enable(EUSCI_A0_BASE); //Enable SPI module
}

void setSpiRateHigh(void) {
    EUSCI_A_SPI_disable(EUSCI_A0_BASE);
    EUSCI_A_SPI_changeMasterClockParam param = {0};
    param.clockSourceFrequency = CS_getSMCLK();
    param.desiredSpiClock = 8000000; //20 Mhz is the max when CLKPLL is locked.

    EUSCI_A_SPI_changeMasterClock(EUSCI_A0_BASE, &param);

    EUSCI_A_SPI_enable(EUSCI_A0_BASE); //Enable SPI module
}

