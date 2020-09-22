#include "main.h"
#include "port.h"
#include "count.h"
#include "eeprom.h"
#include "i2c.h"
#include "ssd.h"
#include "pb.h"
#include "display.h"
#include "utilities.h"
#include "timer.h"
#include "temp.h"
#define DISPLAY_PERIOD_MS (20)
#define SSD_BLINK_MS (1000)
static tDISP_state display_setting=temp_set;
static void display_Blink_SSD(void);
static void display_off(void);
static void display_on(void);
static tEH_state current_state=EH_OFF;
void display_Init(void)
{/*SSD initialization*/
    SSD_Init(SSD_UNITS);
    SSD_Init(SSD_TENS);

    SSD_SetSymbol(SSD_UNITS,SSD_NULL);
    SSD_SetSymbol(SSD_TENS,SSD_NULL);

}
static void display_off(void)
{
    SSD_SetSymbol(SSD_UNITS,SSD_NULL);
    SSD_SetSymbol(SSD_TENS,SSD_NULL);
current_state=EH_OFF;
}
static void display_on(void)
{
   SSD_SetSymbol(SSD_UNITS,temp_GetResults()%10);
    SSD_SetSymbol(SSD_TENS,temp_GetResults()/10);
    current_state=EH_ON;
}

void display_Update(void)
{
    static tWord display_counter=0;
    display_counter+=TMR_TICK_MS;
    /*is it time to execute function*/
    if(display_counter!=DISPLAY_PERIOD_MS)
    {
        return;
    }
    display_counter=0;
    if(display_setting==temp_change)
    {/*if display state is temp change , blink SSD*/
        static tWord setting_counter=0;
        setting_counter+=DISPLAY_PERIOD_MS;
        if(setting_counter==SSD_BLINK_MS)
        {
             display_Blink_SSD();

             setting_counter=0;
        }


    }

}
tEH_state display_ONOFF(void)
{
    if(PB_GetState(PB_SET)==PB_PRE_RELEASED)
    {
        if(current_state==EH_OFF)
        {
            display_on();
        }
        else {display_off();}
    }

return current_state;}

void display_Blink_SSD(void)
{
    if(SSD_GetSymbol(SSD_UNITS)==SSD_NULL||SSD_GetSymbol(SSD_TENS)==SSD_NULL)
    {
        SSD_SetSymbol(SSD_UNITS,(count_GetCount())%10);
        SSD_SetSymbol(SSD_TENS,(count_GetCount())/10);
SSD_Update();
    }
    else{
        SSD_SetSymbol(SSD_UNITS,SSD_NULL);
        SSD_SetSymbol(SSD_TENS,SSD_NULL);

    }
}

void display_SetState(tDISP_state state)
{
    display_setting=state;
}
tDISP_state display_GetState()
{
    return display_setting;
}
tEH_state display_GetPOWERState(void)
{
    return current_state;
}
