#include "i2c.h"
#include"eeprom.h"
#include "main.h"
#include "port.h"

tWord e2pext_r(tWord addr)
{
  tByte ret;
 tByte ah;
  tByte al;

  ah=(addr&0x0100)>>8;
  al=addr&0x00FF;

  i2c_start();
  if(ah)
  {
    i2c_wb(0xA2);
  }
  else
  {
    i2c_wb(0xA0);
  }
  i2c_wb(al);

  i2c_start();
  if(ah)
  {
    i2c_wb(0xA3);
  }
  else
  {
    i2c_wb(0xA1);
  }
  ret=i2c_rb(1);
  i2c_stop();

  return ret;
}


void e2pext_w(tWord addr, tWord val)
{
  tWord tmp;
  tByte ah;
  tByte al;
  tByte nt;

  tmp=val;
  ah=(addr&0x0100)>>8;
  al=addr&0x00FF;
  nt=0;

  do
  {
    i2c_start();
    if(ah)
    {
      i2c_wb(0xA2);
    }
    else
    {
      i2c_wb(0xA0);
    }
    i2c_wb(al);
    i2c_wb(tmp);
    i2c_stop();

    nt++;
  }
  while((tmp != e2pext_r(addr))&&(nt < 10));
}


