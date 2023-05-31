/*  Library for Time Out
 *  File: Timer.cpp
 *  Ver: 1.0
 *  Created on: 06/06/2020
 *  Author: Stefano Valfrè
 */
 
#include "Timer.h"

#define IDLE_SOLDER 0
#define ADDR_TIME_OUT 0x05

int counterTime = ReadByte(ADDR_TIME_OUT); //Contains the time left
int tminutes;
int seconds;
long previousMills = 0;
int interval = 1000;

extern byte stateFSM;

void StartTimeOut(void)
{
  if (millis() -  previousMills > interval)
  {
    previousMills = millis();
    counterTime--;
    tminutes = counterTime / 60;
    seconds = counterTime % 60;
  }
  if (counterTime == 0) stateFSM = IDLE_SOLDER;

}

void ResetTimer(void)
{
  counterTime = ReadByte(ADDR_TIME_OUT);
}
