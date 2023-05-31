/*  Oled functions and Menu options
 *  File: Oled.h
 *  Ver: 1.0
 *  Created on: 06/06/2020
 *  Author: Stefano Valfrè
 */
 
#ifndef _OLED_H
#define _OLED_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "LOGO.h"
#include "E2prom.h"
#include "IO.h"
#include "PID.h"
#include "SenseCurrent.h"
#include "Timer.h"
#include "PWM.h"

#define TARGHET1 0
#define TARGHET2 1

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//HILETGO 0.96 OLED
#define OLED_MOSI 11  //SDA PIN   
#define OLED_CLK 12   //SCK PIN  
#define OLED_DC 9   //DC PIN   
#define OLED_CS 8   //CS PIN
#define OLED_RESET 10 //RES PIN

//Stati per la macchina di setting
#define CHANGE_TARGHET1 0
#define CHANGE_TARGHET2 1
#define SET_PID 2
#define SET_PARAM_PID_KP 3
#define SET_PARAM_PID_KD 4
#define SET_PARAM_PID_KI 5
#define CONFIRM_PID 6
#define SET_TIME 7
#define SET_TIME_SECOND 8

#define MAX_TEMP 450
#define MIN_TEMP 0

#define ADDR_TEMP_1 0x00
#define ADDR_TEMP_2 0x02
#define ADDR_TIME_OUT 0x05
#define ADDR_KP 0x10
#define ADDR_KD 0x15
#define ADDR_KI 0x20

//#define MAX_PWM 55  //Massimo duty cycle consentito 55%
#define OFF 0       //PWM off

void OLED_Init(void);
void ShowLogo(void);
void ShowMainScreen(bool SelectTarget, bool statusTIP, int ReadTemp);
void ShowSetting(void);
void ShowFault(void);
void FadeLed(void);

#endif
