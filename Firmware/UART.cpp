/*  Library for show Info of System and plot graph of temperature
 *  File: UART.cpp
 *  Ver: 1.0
 *  Created on: 06/06/2020
 *  Author: Stefano Valfrè
 */
 
#include "UART.h"

bool choice = 0;

void StreamingON(int Read_Temperature, uint16_t Target_Temperature)
{
  //Functions for serial plotter
  if (choice == 0)
  {
    Serial.println(F("TempRead[°C],TempTarghet[°C]"));
    Serial.print(Read_Temperature);
    Serial.print(F("\t"));
    Serial.print(Target_Temperature);
    Serial.print(F("\t"));
    Serial.println(0);
  }
}

void Info(void)
{
  if (Serial.read() == '?')
  {
    choice = 1;
    Serial.println(F("SolderingStation"));
    Serial.print(F("FW Version: "));
    Serial.println(ReadByte(ADDR_FW));
    Serial.print(F("Temperature Targhet 1: "));
    Serial.print(ReadByte(ADDR_TEMP_1));
    Serial.println(F("°C"));
    Serial.print(F("Temperature Targhet 2: "));
    Serial.print(ReadByte(ADDR_TEMP_2));
    Serial.println(F("°C"));
    Serial.println(F("Parameters PID:"));
    Serial.print(F("Kp: "));
    Serial.println(ReadDouble(ADDR_KP));
    Serial.print(F("Ki: "));
    Serial.println(ReadDouble(ADDR_KI));
    Serial.print(F("Kd: "));
    Serial.println(ReadDouble(ADDR_KD));
  }
}
