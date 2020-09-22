#ifndef __DISPLAY_H__
#define __DISPLAY_H__
 typedef enum {temp_set,
 temp_change}tDISP_state;
 typedef enum {EH_ON,
 EH_OFF}tEH_state;

 void display_Init(void);
 void display_Update(void);
 tEH_state display_ONOFF(void);
 void display_SetState(tDISP_state state);
 tDISP_state display_GetState(void);
 tEH_state display_GetPOWERState(void);

#endif

