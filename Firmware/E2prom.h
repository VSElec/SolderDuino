/*  Library for Eeprom functions
    File: E2prom.h
    Ver: 1.0
    Created on: 06/06/2020
    Author: Stefano Valfrè
*/
#ifndef _E2PROM_H
#define _E2PROM_H

#include <Arduino.h>
#include <EEPROM.h>

void WriteByte(uint8_t address_start, uint16_t data);
uint16_t ReadByte(uint8_t address_start);
double ReadDouble(uint8_t address_start);
void WriteDouble(uint8_t address_start, double data);

#endif
