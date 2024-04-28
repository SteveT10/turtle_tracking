#ifndef _DECA_SPI_H_
#define _DECA_SPI_H_
#include <stdint.h>

/**
 * Initializes SPI Module for DWM1000 usage.
 * Note: Current implementation only supports UCA0 module on pins 5.0-5.2, 4.7
 *
 * @param selectedPort is the port that TX, RX, and CLK pins are on.
 * @param selectedPins is the TX, RX, and CLK pins.
 * @param enPort is the port the enable pin is on.
 * @param enPin is the enable pin number.
 */
//TODO: Find a way to input pin numbers in a more intuitive way.
int initSpi(uint8_t selectedPort, uint16_t selectedPins, uint8_t enPort, uint8_t enPin);

#endif /* _DECA_SPI_H_ */
