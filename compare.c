#include "main.h"
#include "port.h"
#include "compare.h"
#include "eeprom.h"
#include "i2c.h"
#include "adc.h"
#include "temp.h"
#include "timer.h"
#include "display.h"
#include "ssd.h"
#define COMPARE_PERIOD_MS (20)
 static void LED_BLINK(void);

 void compare_Init(void)
 {
     //Heater initialization
     GPIO_InitPortPin(HEATER_PORT_CR,HEATER_PIN,GPIO_OUT);
     GPIO_WritePortPin(HEATER_PORT_DR,HEATER_PIN,0);
     //Fan initialization
     GPIO_InitPortPin(FAN_PORT_CR,FAN_PIN,GPIO_OUT);
     GPIO_WritePortPin(FAN_PORT_DR,FAN_PIN,0);
     //LED initialization
     GPIO_InitPortPin(LED_HEAT_PORT_CR,LED_HEAT_PIN,GPIO_OUT);
     GPIO_WritePortPin(LED_HEAT_PORT_DR,LED_HEAT_PIN,0);

 }

 void compare_Update(void)
 {
     static tWord compare_counter=0;
     static tWord LED_counter=0;
     compare_counter+=TMR_TICK_MS;
     /*is it time to execute the function*/
     if(compare_counter!=COMPARE_PERIOD_MS)
     {
         return;
    }
    compare_counter=0;
/*if the Electric heater was on , we begin to compare temperatures*/
if(display_GetPOWERState()==EH_ON){
    if((temp_GetResults()+5)<=(e2pext_r(0x0010)))
    {LED_counter+=COMPARE_PERIOD_MS;
       GPIO_WritePortPin(HEATER_PORT_DR,HEATER_PIN,1);
       /*LED should blink every second(1000ms)*/
 if(LED_counter==1000)
       {
           LED_BLINK();
           LED_counter=0;
       }
       GPIO_WritePortPin(FAN_PORT_DR,FAN_PIN,0);

    }
    else if((temp_GetResults()-5)>=e2pext_r(0x0010))
    {
        GPIO_WritePortPin(FAN_PORT_DR,FAN_PIN,1);
         GPIO_WritePortPin(HEATER_PORT_DR,HEATER_PIN,0);
GPIO_WritePortPin(LED_HEAT_PORT_DR,LED_HEAT_PIN,1);
         } else  if(temp_GetResults()==e2pext_r(0x0010))
         {
              GPIO_WritePortPin(HEATER_PORT_DR,HEATER_PIN,0);
    GPIO_WritePortPin(FAN_PORT_DR,FAN_PIN,0);
    GPIO_WritePortPin(LED_HEAT_PORT_DR,LED_HEAT_PIN,0);

    }} else{

              GPIO_WritePortPin(HEATER_PORT_DR,HEATER_PIN,0);
    GPIO_WritePortPin(FAN_PORT_DR,FAN_PIN,0);
    GPIO_WritePortPin(LED_HEAT_PORT_DR,LED_HEAT_PIN,0);
    }



 }
 static void LED_BLINK(void)
 {
     tByte LED_state=GPIO_ReadPortPin(LED_HEAT_PORT_DR,LED_HEAT_PIN);
     if(LED_state==0)
     {
         LED_state=1;
         GPIO_WritePortPin(LED_HEAT_PORT_DR,LED_HEAT_PIN,1);
     }
     else{
        LED_state=0;
        GPIO_WritePortPin(LED_HEAT_PORT_DR,LED_HEAT_PIN,0);
     }
 }

