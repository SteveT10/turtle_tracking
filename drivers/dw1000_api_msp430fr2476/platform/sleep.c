#include "deca_device_api.h"
#include "sleep.h"
#include "driverlib.h"

//16 Mhz MCLK

int COUNT = 0;

void deca_sleep(unsigned int time_ms) {
    COUNT = 0;
    Timer_A_stop(TA0_BASE); //TAxCTL MC = 0 //Disable Timer
    Timer_A_clear(TA0_BASE);

    Timer_A_initUpModeParam param = {0};
    param.clockSource = TIMER_A_CLOCKSOURCE_SMCLK; //16 Mhz
    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    param.timerPeriod = 16000; //1 ms periods.
    param.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;
    param.timerClear = TIMER_A_DO_CLEAR; //TACLR = 1 in TAxCTL reg
    param.startTimer = true;

    Timer_A_initUpMode(TA0_BASE, &param); //TAxCTL MC = 01.

    __bis_SR_register(LPM0_bits | GIE);           // Enter LPM0 w/ interrupts

    //Enter Low power mode and wait for interrupts 
    while(COUNT <  time_ms);  //Temp while loop, need to look into power modes.

    //TAxCCRn //Period Register for up  mode
}

void Timer_A (void) {
    COUNT++;
}