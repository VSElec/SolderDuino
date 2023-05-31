/*  Library for Eeprom functions
    File: E2prom.cpp
    Ver: 1.0
    Created on: 06/06/2020
    Author: Stefano Valfrè
*/

/*
  To decompose a 16-bit number:
  High part  BH -->  Number >>8
  Lower part BL -->  Number & 0xFF

  To recompose the number:
  Number = (BL|(BH <<8))
*/

#include "E2prom.h"

/*
   MEMORY STRUCTURE:
   ADDRESS 0x00: Temperature Targhet1 BH
   ADDRESS 0x01: Temperature Targhet1 BL

   ADDRESS 0x02: Temperature Targhet2 BH
   ADDRESS 0x03: Temperature Targhet2 BL

   ADDRESS 0x04: Firmware version

   ADDRESS 0x05: TimeOut BH
   ADDRESS 0x06: TimeOut BL

   ADDRESS 0x10: Kp
   ADDRESS 0x15: Kd
   ADDRESS 0x20: Ki
*/
void WriteByte(uint8_t address_start, uint16_t data)
{
  //Write the high part
  EEPROM.write(address_start, data >> 8);
  //Write the lower part
  EEPROM.write(address_start + 1, data & 0xFF);
}

uint16_t ReadByte(uint8_t address_start)
{
  //(lower part |(high part <<8))
  return (EEPROM.read(address_start + 1) | EEPROM.read(address_start) << 8);
}

void WriteDouble(uint8_t address_start, double data)
{
  //Write a double number in memory
  EEPROM.put(address_start, data);
}

double ReadDouble(uint8_t address_start)
{
  //Read a double number in memory
  double valueRead;
  EEPROM.get(address_start, valueRead);
  return valueRead;
}
