/*  Library for manage PID
    File: PID.h
    Ver: 1.0
    Created on: 06/06/2020
    Author: Stefano Valfrè
*/

#ifndef _PID_H
#define _PID_H

#include <PID_v1.h>
#include <Arduino.h>
#include "E2prom.h"

void InitPid(void);
double PID_On(uint16_t TemperatureRead, uint16_t TemperatureTarget);

#endif
