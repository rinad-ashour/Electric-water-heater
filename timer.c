#include "main.h"
#include "timer.h"
#include "pb.h"
#include "compare.h"
#include "display.h"
#include "ssd.h"
#include "count.h"
#include "temp.h"

extern tByte flag;

void TMR_Init(void)
{

	TMR_SET_PRESCALER_256;
	TMR_DISABLE_CLOCK;

}
void TMR_Start(void)
{

	TMR_CLEAR_FLAG;
	TMR_UPDATE_REGISTER(TMR_TICK_MS);
	TMR_ENABLE_INTERRUPT;
	GLOBAL_INTERRUPT_ENABLE;
	TMR_ENABLE_CLOCK;

}
tByte TMR_CheckOverFlow(void)
{

	return TMR_GET_FLAG;

}
void TMR_Stop(void)
{

	TMR_DISABLE_CLOCK;

}
void TMR_Update(void) __interrupt 0
{ SSD_Update();
  PB_Update();
  count_Update();
  compare_Update();
  display_Update();
   temp_Update();


  TMR_CLEAR_FLAG;
  TMR_UPDATE_REGISTER(TMR_TICK_MS);
}


