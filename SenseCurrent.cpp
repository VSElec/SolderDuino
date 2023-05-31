/*  Library for read current sense and battery voltage
 *  File: SenseCurrent.cpp
 *  Ver: 1.0
 *  Created on: 06/06/2020
 *  Author: Stefano Valfrè
 */
 
#include "SenseCurrent.h"

float rawCurrent, rawSupply;
float supply, I, power;

uint16_t ReadPower(void)
{
  //I read an average of the current
  for (byte i = 0; i < 10; i++)
  {
    rawCurrent = rawCurrent + analogRead(CURRENT);
  }
  rawCurrent = rawCurrent / 10;

  // Vo=Is*Rs*Rl/5000
  I= 5.01*(rawCurrent*(5.0/1024.0));
  power = I * ReadBattery();
  return round(power);

}

float ReadBattery(void)
{
  rawSupply = 0.0;
  //I read an average of the current battery
  for (byte i = 0; i < 10; i++)
  {
    rawSupply = rawSupply + analogRead(SUPPLY_SENS);
  }
  rawSupply = rawSupply / 10.0;

  supply = ((rawSupply * (5.0 / 1024.0)) * 9.2); 
  return supply;
}
