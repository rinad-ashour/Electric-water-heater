#ifndef __I2C_H__
#define __I2C_H__
#include "main.h"
#include "port.h"

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_wb(tWord val);
tWord i2c_rb(tByte ack);

#endif




