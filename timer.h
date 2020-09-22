#ifndef __TIMER_H__
#define __TIMER_H__
#include "main.h"


#define TMR_TICK_MS				(5)

void TMR_Init(void);
void TMR_Start(void);
tByte TMR_CheckOverFlow(void);
void TMR_Stop(void);
void TMR_Update(void) __interrupt 0; /* ISR @  vector 0 */

#endif

