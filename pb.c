#include "main.h"
#include "port.h"
#include "timer.h"
#include "pb.h"

#define PB_PERIOD_MS   (20)

#define N_SAMPLES      (2)

#define N_PB      (3)


#define PB_PRESSED_LEVEL        (0)
#define PB_RELEASED_LEVEL       (1)



/* PB info: samples, state */
typedef struct
{
    tByte pb_samples[N_SAMPLES];
    tPB_State pb_state;
}tPB_Info;

/* Pb info */
static tPB_Info PBs_Info[N_PB];

void PB_Init(void)
{
    tByte i = 0;

    /* Initialize push-buttons as inputs */
    GPIO_InitPortPin(PB_UP_PORT_CR, PB_UP_PIN, GPIO_IN);
    GPIO_InitPortPin(PB_DOWN_PORT_CR, PB_DOWN_PIN, GPIO_IN);
    GPIO_InitPortPin(PB_SET_PORT_CR, PB_SET_PIN, GPIO_IN);

    /* Initialize push-buttons info */
    for (i = PB_UP; i < N_PB; i++)
    {
        /* Initialize PUSH-BUTTON samples */
        PBs_Info[i].pb_samples[0] = PB_RELEASED_LEVEL;
        PBs_Info[i].pb_samples[1] = PB_RELEASED_LEVEL;

        /* Initialize push-buttons state */
        PBs_Info[i].pb_state = PB_RELEASED;

    }

}


tPB_State PB_GetState(tPB pb)
{

    return PBs_Info[pb].pb_state;

}


void PB_Update(void)
{
    static tWord pb_counter = 0;
    tByte index = 0;

    /*is it time to execute the function*/
    pb_counter += TMR_TICK_MS;

    if (pb_counter != PB_PERIOD_MS){
        return;
    }

    pb_counter = 0;

    /* Update pb states */
    for (index = PB_UP; index < N_PB; index++)
    {
        /* Update pb samples */
        PBs_Info[index].pb_samples[0] = PBs_Info[index].pb_samples[1];

        if (index == PB_UP)
        {
            PBs_Info[index].pb_samples[1] = GPIO_ReadPortPin(PB_UP_PORT_DR, PB_UP_PIN);
        } else if (index == PB_DOWN)
        {
            PBs_Info[index].pb_samples[1] = GPIO_ReadPortPin(PB_DOWN_PORT_DR, PB_DOWN_PIN);
        } else if (index == PB_SET)
        {
            PBs_Info[index].pb_samples[1] = GPIO_ReadPortPin(PB_SET_PORT_DR, PB_SET_PIN);
        } else
        {

        }

        /* Update pb state */
        switch(PBs_Info[index].pb_state)
        {

            case PB_RELEASED:
                /* Go to pre-pressed state if needed */
                if ((PBs_Info[index].pb_samples[0] == PB_PRESSED_LEVEL) &&
                    (PBs_Info[index].pb_samples[1] == PB_PRESSED_LEVEL))
                {
                    PBs_Info[index].pb_state = PB_PRE_PRESSED;
                } else
                {

                }
                break;
            case PB_PRE_PRESSED:
                /* Go to pressed state if needed  */
                if (PBs_Info[index].pb_samples[1] == PB_PRESSED_LEVEL)
                {
                    PBs_Info[index].pb_state = PB_PRESSED;
                } else
                {

                }
                break;
            case PB_PRESSED:
                /* Go to pre-released state if needed */
                if ((PBs_Info[index].pb_samples[0] == PB_RELEASED_LEVEL) &&
                    (PBs_Info[index].pb_samples[1] == PB_RELEASED_LEVEL))
                {
                    PBs_Info[index].pb_state = PB_PRE_RELEASED;
                }
                else
                {

                }
                break;
            case PB_PRE_RELEASED:
                /* Go to released state if needed */
                if (PBs_Info[index].pb_samples[1] == PB_RELEASED_LEVEL)
                {
                    PBs_Info[index].pb_state = PB_RELEASED;
                } else
                {

                }
                break;
            default:
                break;
        }

    }

}

