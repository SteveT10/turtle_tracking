/**
 * deca_sleep implementation for msp430fr2476.
 *
 * @author Steven Tieu.
 * @version 4-28-2024
 */
#include "deca_device_api.h"
#include <msp430.h>

static int COUNT;

void deca_sleep(unsigned int time_ms) {
    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    COUNT = 0;
    //PM5CTL0 &= ~LOCKLPM5;

    TA0CTL &= ~0x0030; //Disable Timer
    TA0CCTL0 |= CCIE;                             // TACCR0 interrupt enabled
    TA0CCR0 = 1044; //1 MHz clock = SMCLK? Datasheet states 16 Mhz, but this was closest to 1 ms period.
    TA0CTL |= TASSEL__SMCLK | MC__UP;     // SMCLK, up mode

    __bis_SR_register(GIE);           // Enable interrupts
    while(COUNT < time_ms); //TODO: Enter Low Power Mode to converse power when this happens?
    TA0CTL &= ~0x0030; //Disable Timer
}

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
    COUNT++;
}
