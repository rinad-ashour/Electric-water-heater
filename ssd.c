#include "main.h"
#include "port.h"
#include "timer.h"
#include "ssd.h"


#define SSD_PERIOD_MS   (5)


#define N_SSD_SYMBOLS   (11)


/* SSD Symbols port data values */
static tByte SSD_Data[N_SSD_SYMBOLS] =
{
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111,
    0b00000000,
};

/* Current SSD to be updated */
static tSSD SSD_current = SSD_UNITS;

/* SSD values */
static tSSD_Symbol SSD_Symbols[N_SSD] = {SSD_NULL};

static void SSD_Out(tSSD ssd, tSSD_Symbol ssd_symbol);

void SSD_Init(tSSD ssd)
{

    /* Initialize SSD data pins */
    GPIO_InitPort(SSD_DATA_PORT_CR, GPIO_OUT);
    SSD_Out(ssd, SSD_NULL);

    /* Initialize SSD control pin and turn SSD OFF*/
    switch (ssd)
    {
        case SSD_UNITS:
            GPIO_InitPortPin(SSD_UNITS_CR, SSD_UNITS_PIN, GPIO_OUT);
            break;
        case SSD_TENS:
            GPIO_InitPortPin(SSD_TENS_CR, SSD_TENS_PIN, GPIO_OUT);
            break;

        default:
            break;
    }
    SSD_SetState(ssd, SSD_OFF);

}

void SSD_Update(void)
{
    static tWord SSD_counter = 0;


    /*is it time to execute the function*/
    SSD_counter += TMR_TICK_MS;

    if (SSD_counter != SSD_PERIOD_MS){
        return;
    }

    SSD_counter = 0;

    /* display current SSD value of the current SSD */

SSD_Out(SSD_current,SSD_Symbols[SSD_current]);
    if (SSD_current == SSD_TENS)
    {
        SSD_current = SSD_UNITS;
    } else
    {
        SSD_current++;
    }
}

tSSD_Symbol SSD_GetSymbol(tSSD ssd)
{

    return SSD_Symbols[ssd];

}
void SSD_SetSymbol(tSSD ssd, tSSD_Symbol ssd_symbol)
{

    SSD_Symbols[ssd] = ssd_symbol;

}

tSSD_State SSD_GetState(tSSD ssd)
{
    tSSD_State ret = SSD_OFF;

    switch (ssd)
    {
        case SSD_UNITS:
            ret = GPIO_ReadPortPin(SSD_UNITS_DR, SSD_UNITS_PIN);
            break;
        case SSD_TENS:
            ret = GPIO_ReadPortPin(SSD_TENS_DR, SSD_TENS_PIN);
            break;


        default:
            break;
    }
      return ret;

}

void SSD_SetState(tSSD ssd, tSSD_State state)
{

    switch (ssd)
    {
        case SSD_UNITS:
            GPIO_WritePortPin(SSD_UNITS_DR, SSD_UNITS_PIN, state);
            break;
        case SSD_TENS:
            GPIO_WritePortPin(SSD_TENS_DR, SSD_TENS_PIN, state);
            break;


        default:
            break;
    }

}

static  void SSD_Out(tSSD ssd, tSSD_Symbol ssd_symbol)
{

    /* Turn off SSDs */
    SSD_SetState(SSD_UNITS, SSD_OFF);
    SSD_SetState(SSD_TENS, SSD_OFF);

    /* Output ssd_symbol on selected ssd */
    GPIO_WritePort(SSD_DATA_PORT_DR, SSD_Data[ssd_symbol]);

    /* Turn ssd ON */
    SSD_SetState(ssd, SSD_ON);



}


