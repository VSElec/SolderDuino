/*  Library for reading the thermocouple and the NTC
 *  File: SenseTemp.h
 *  Ver: 1.0
 *  Created on: 06/06/2020
 *  Author: Stefano Valfrè
 */
 
#ifndef _SENSETEMP_H
#define _SENSETEMP_H

#include "IO.h"

uint16_t ReadSensorADC(byte avarage);
uint16_t adc2celsius(uint16_t adc_value);
uint16_t ReadSensorNTC(byte avarage);
uint16_t NTCcelsius(uint16_t adc_value);
#endif
