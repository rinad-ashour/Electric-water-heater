#ifndef __PB_H__
#define __PB_H__

typedef enum
{
    PB_UP,
    PB_DOWN,
    PB_SET
}tPB;

typedef enum
{
    PB_RELEASED,
    PB_PRE_PRESSED,
    PB_PRESSED,
    PB_PRE_RELEASED
}tPB_State;


void PB_Init(void);
void PB_Update(void);
tPB_State PB_GetState(tPB pb);
#endif // __PB_H__


