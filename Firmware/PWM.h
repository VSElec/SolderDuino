/*  Library for PWM functions
 *  File: PWM.h
 *  Ver: 1.0
 *  Created on: 06/06/2020
 *  Author: Stefano Valfrè
 */
 
#ifndef _PWM_H
#define _PWM_H

#include "IO.h"
#include "SenseCurrent.h"

#define MAX_PWM 70  //Maximum allowed duty cycle 70%
#define OFF 0       //PWM off

#define MIN_VOLT 11 //Minimum allowed operating voltage

void PWM_ON(uint8_t duty_cycle);
void PWM_OFF(void);
void setPwmFrequency(int pin, int divisor);

#endif
