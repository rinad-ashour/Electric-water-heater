#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "main.h"
#include "port.h"
tWord e2pext_r(tWord addr);
void e2pext_w(tWord addr, tWord val);
#endif

