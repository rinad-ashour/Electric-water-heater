#include "main.h"
#include "port.h"
#include "count.h"
#include "eeprom.h"
#include "i2c.h"
#include "ssd.h"
#include "pb.h"
#include "display.h"
#include "timer.h"
#include "temp.h"

#define COUNTER_PERIOD_MS (20)
#define TEMP_CHANGE_OFF  (5000)
static tByte count;
static tByte settemp=60;
void count_Init(void)
{
//initialize the count and store initial eeprom value
    e2pext_w(0x0010,settemp);

    count=e2pext_r(0x0010);
}

void count_Update(void)
{
    static tWord count_counter=0;
    static tWord temp_state_counter=0;
    count_counter+=TMR_TICK_MS;
    /*is it time to execute the function*/
    if(count_counter!=COUNTER_PERIOD_MS)
{
    return;
}
count_counter=0;
/*update PB up and down if PB set was pressed on*/
if(display_ONOFF()==EH_ON)
{temp_state_counter+=COUNTER_PERIOD_MS;
    if(PB_GetState(PB_UP)==PB_PRE_RELEASED)
    {
        temp_state_counter=0;
        if(display_GetState()==temp_set)
        {/*change display state if the PB up or down were pressed for the first time*/
            display_SetState(temp_change);
            count=e2pext_r(0x0010);
             SSD_SetSymbol(SSD_UNITS,count%10);
    SSD_SetSymbol(SSD_TENS,count/10);
            temp_state_counter=0;
        }
        else {temp_state_counter=0;
        /*max count is 75*/
        if(count<75)
            count+=5;
             SSD_SetSymbol(SSD_UNITS,count%10);
    SSD_SetSymbol(SSD_TENS,count/10);
        }
    }
    else if(PB_GetState(PB_DOWN)==PB_PRE_RELEASED)
    {
        temp_state_counter=0;
        if((display_GetState())==temp_set)
        {
            display_SetState(temp_change);
            temp_state_counter=0;
        }
        else {temp_state_counter=0;
        /*min count is 35*/
        if(count>35)
            count-=5;
             SSD_SetSymbol(SSD_UNITS,count%10);
    SSD_SetSymbol(SSD_TENS,count/10);
        }
    }
    else if(temp_state_counter==TEMP_CHANGE_OFF)
    {
        display_SetState(temp_set);
       SSD_SetSymbol(SSD_UNITS,temp_GetResults()%10);
    SSD_SetSymbol(SSD_TENS,temp_GetResults()/10);
    settemp=count;
        e2pext_w(0x0010,settemp);
        temp_state_counter=0;
    }

}
}
tByte count_GetCount(void)
{
    return count;
}

