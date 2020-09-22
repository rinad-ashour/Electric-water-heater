#include <pic16f877a.h>
#include "adc.h"
#include "main.h"
#include "port.h"
#include "temp.h"
#include "ssd.h"
#include "display.h"
#include "timer.h"
#define TEMP_PERIOD_MS (100)
tWord TC;
tWord adc_output;
void temp_Init(void)
{

}
void temp_Update(void)
{static tWord temp_counter=0;
temp_counter+=TMR_TICK_MS;
/*is it time to execute the function*/
if(temp_counter!=TEMP_PERIOD_MS)
{
    return;
}
temp_counter=0;
    /*using LM35 temperature sensor*/
  adc_output=ADC_GetResult(2);
TC=(adc_output*100/204);/*Temperature (sensed value) equation*/
/*if display is on and in temp set state,sent temperature to SSD*/
if(display_GetPOWERState()==EH_ON&&display_GetState()==temp_set)
{
    SSD_SetSymbol(SSD_UNITS,TC%10);
    SSD_SetSymbol(SSD_TENS,TC/10);
}
}
tByte temp_GetResults(void)
{
    return TC  ;
}

