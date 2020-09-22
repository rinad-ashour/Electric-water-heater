#ifndef __PORT_H__
#define __PORT_H__

#include "Main.h"


/* Leds' pins */

#define LED_HEAT_PORT_DR   (GPIO_PORTB_DATA)
#define LED_HEAT_PORT_CR   (GPIO_PORTB_CONTROL)
#define LED_HEAT_PIN       (GPIO_PIN_6)

/* Heater */
#define HEATER_PORT_DR      (GPIO_PORTC_DATA)
#define HEATER_PORT_CR      (GPIO_PORTC_CONTROL)
#define HEATER_PIN          (GPIO_PIN_5)

/* Fan */
#define FAN_PORT_DR         (GPIO_PORTC_DATA)
#define FAN_PORT_CR         (GPIO_PORTC_CONTROL)
#define FAN_PIN             (GPIO_PIN_2)

/* Temperature sensor */
#define TS_PORT_DR          (GPIO_PORTA_DATA)
#define TS_PORT_CR          (GPIO_PORTA_CONTROL)
#define TS_PIN              (GPIO_PIN_2)

/* I2C */

#define ICLK                 (RC3)
#define IDAT                 (RC4)
#define TIDAT                (TRISC4)

/* Push-Buttons */
#define PB_UP_PORT_DR     (GPIO_PORTB_DATA)
#define PB_UP_PORT_CR     (GPIO_PORTB_CONTROL)
#define PB_UP_PIN         (GPIO_PIN_1)

#define PB_DOWN_PORT_DR    (GPIO_PORTB_DATA)
#define PB_DOWN_PORT_CR    (GPIO_PORTB_CONTROL)
#define PB_DOWN_PIN        (GPIO_PIN_2)

#define PB_SET_PORT_DR      (GPIO_PORTB_DATA)
#define PB_SET_PORT_CR      (GPIO_PORTB_CONTROL)
#define PB_SET_PIN          (GPIO_PIN_3)

/* SSD */
#define SSD_DATA_PORT_DR        (GPIO_PORTD_DATA)
#define SSD_DATA_PORT_CR        (GPIO_PORTD_CONTROL)


#define SSD_TENS_DR     (GPIO_PORTA_DATA)
#define SSD_TENS_CR     (GPIO_PORTA_CONTROL)
#define SSD_TENS_PIN    (GPIO_PIN_3)

#define SSD_UNITS_DR    (GPIO_PORTA_DATA)
#define SSD_UNITS_CR    (GPIO_PORTA_CONTROL)
#define SSD_UNITS_PIN   (GPIO_PIN_4)

#endif // __PORT_H__


