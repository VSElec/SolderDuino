/*  Library for read current sense and battery voltage
 *  File: SenseCurrent.h
 *  Ver: 1.0
 *  Created on: 06/06/2020
 *  Author: Stefano Valfrè
 */
 
#ifndef _SENSECURRENT_H
#define _SENSECURRENT_H

#include <Arduino.h>
#include "IO.h"

uint16_t ReadPower(void);
float ReadBattery(void);

#endif
