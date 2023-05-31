/*  Library for manage PID 
 *  File: PID.cpp
 *  Ver: 1.0
 *  Created on: 06/06/2020
 *  Author: Stefano Valfrè
 */
#include "PID.h"

double Setpoint, Input, Output;

//Suggested values Kp=45 Kd=5 Ki=90
double Kp = ReadDouble(0x10);
double Ki = ReadDouble(0x20);
double Kd = ReadDouble(0x15);

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void InitPid(void)
{
  myPID.SetMode(AUTOMATIC);
}

double PID_On(uint16_t TemperatureRead, uint16_t TemperatureTarget)
{
  Input = TemperatureRead;
  Setpoint = TemperatureTarget;

  //If the difference is 10 ° C, set a less aggressive pid
  if (abs(Setpoint - Input) < 10) myPID.SetTunings(Kp / 6, Ki / 4, Kd / 5);
  else myPID.SetTunings(Kp, Ki, Kd);
  
  myPID.Compute();
  Output = ((Output * 100) / 255); //Convert DutyCycle to %
  
  return Output;
}
