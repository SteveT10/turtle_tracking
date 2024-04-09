#include <msp430.h> 
#include "deca_device_api.h"
#include "sleep.h"
#include "spi.h"
#include "mutex.h"

/**
 * main.c
 */

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	unsigned int delay = 1000;
	deca_sleep(delay);
	return 0;
}
