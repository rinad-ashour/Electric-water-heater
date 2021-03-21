#include "main.h"
#include "port.h"
#include "pb.h"
#include "timer.h"
#include "display.h"
#include "count.h"
#include "ssd.h"
#include "temp.h"
#include "eeprom.h"
#include "adc.h"
#include "compare.h"
#include "i2c.h"

tWord __at(0x2007) CONFIG = _HS_OSC & _WDT_OFF & _PWRTE_ON & _BODEN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _DEBUG_OFF & _CP_OFF;
tByte flag = 0;

void main(void)
{   TRISC &= ~0x08;
    i2c_init();
    ADC_Init(1);
    PB_Init();
    count_Init();
    display_Init();
    compare_Init();
    TMR_Init();
    TMR_Start();
    while(1)
    {

    }

}

