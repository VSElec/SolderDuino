/*  Library for show Info of System and plot graph of temperature
 *  File: UART.h
 *  Ver: 1.0
 *  Created on: 06/06/2020
 *  Author: Stefano Valfrè
 */
 
#ifndef _UART_H
#define _UART_H

#include <Arduino.h>
#include "E2prom.h"

#define ADDR_TEMP_1 0x00
#define ADDR_TEMP_2 0x02
#define ADDR_FW 0x04
#define ADDR_KP 0x10
#define ADDR_KD 0x15
#define ADDR_KI 0x20

void StreamingON(int Read_Temperature, uint16_t Target_Temperature);
void Info(void);
#endif
