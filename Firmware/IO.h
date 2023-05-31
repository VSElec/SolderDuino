/*  Library for I/O functions initialize and Encoder read
 *  File: IO.h
 *  Ver: 1.0
 *  Created on: 06/06/2020
 *  Author: Stefano Valfrè
 */
 
#ifndef _IO_H
#define _IO_H

#include <Arduino.h>
#include <Encoder.h>

#define TEMP_SENSOR A0  //WELLER SENSOR
#define SUPPLY_SENS A1  //POWER SUPPLY
#define CURRENT A2      //CURRENT READER
#define NTC A3          //NTC READER

//State Switch encoder
#define UNPRESS 0
#define SHORTPRESS 1
#define LONGPRESS 2

//ENCODER PIN
#define ENC_A 2
#define ENC_SW 3
#define ENC_B 4

#define TIP 6           //WELLER HEATER

#define LED_STATE 5     //LED STATUS

void InitIO(void);
long Read_Encoder(void);
uint8_t Read_Encoder_SW(void);
#endif
