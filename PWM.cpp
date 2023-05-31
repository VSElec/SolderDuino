/*  Library for PWM functions
 *  File: PWM.cpp
 *  Ver: 1.0
 *  Created on: 06/06/2020
 *  Author: Stefano Valfrè
 */

#include "PWM.h"

extern double Output;

void PWM_OFF(void)
{
  //I turn off PWM
  analogWrite(TIP, OFF);
}

void PWM_ON(uint8_t duty_cycle)
{
  if (ReadBattery() < MIN_VOLT)
  {
    Output = OFF;
    duty_cycle = OFF;
  }
  //Conversion DutyCycle*255/100
  if (duty_cycle > MAX_PWM)
  {
    analogWrite(TIP, (uint8_t)((MAX_PWM * 255) / 100));
  }
  else
  {
    analogWrite(TIP, (uint8_t)((duty_cycle * 255) / 100));
  }
}
