/*  Soldering Station Controller - SolderDuino
 *  File: Weller_1.0.ino
 *  Ver: 1.0
 *  Created on: 06/06/2020
 *  Author: Stefano Valfrè
 */
#include "E2prom.h"
#include "IO.h"
#include "PWM.h"
#include "SenseTemp.h"
#include "Oled.h"
#include "PID.h"
#include "Timer.h"
#include "UART.h"
#include <avr/wdt.h>

// State machine variables
#define IDLE_SOLDER 0
#define MAINSCREEN  1
#define SETTING  2

//Variables state definition of the tip
#define NOTCONNECT 0
#define CONNECT 1

//Temperature variables
#define MAX_TEMP 450
#define MIN_TEMP 0

#define TIME_SENS 55 //Delay for reading the thermocouple
#define TIME_LOGO 1000 //Delay for Logo

#define TARGHET_1 0
#define TARGHET_2 1

//Variabili FSM
byte stateFSM = LOW;
extern uint8_t stateSetting;

//Variables for selecting the Target 1 or Targhet 2 temperature
bool SelectTarget = 0;

//Status variable of the encoder switch IO.h
extern byte stateSW;

//Reset the position of the encoder IO.h
extern bool resetSW;

//Temperature Target
extern uint16_t Target1;
extern uint16_t Target2;

//Temperature read
int read_Temperature = 0;

//0 = Tip not connected 1 = Connected tip
uint8_t statusTIP = NOTCONNECT;

void setup()
{
  //Pin initialization
  InitIO();
  InitPid();
  OLED_Init();

  //Logo
  ShowLogo();

  //Watchdog timer 2sec
  wdt_enable(WDTO_2S);
  delay(TIME_LOGO);
}

void loop()
{
  Info(); //It shows the system information if we send the character to the serial '?'
  
  switch (stateFSM)
  {
    case IDLE_SOLDER:
      statusTIP = NOTCONNECT;
      PWM_OFF();
      ShowMainScreen(SelectTarget, statusTIP, read_Temperature); //Main screen update with selected target and tip status
      if (Read_Encoder_SW() == SHORTPRESS)
      {
        stateFSM = MAINSCREEN;
        ResetTimer();
        statusTIP = CONNECT;
        resetSW = 1;
        stateSW = UNPRESS;
      }
      break;

    case MAINSCREEN:
      //Enable the timer
      StartTimeOut();
      ShowMainScreen(SelectTarget, statusTIP, read_Temperature);
      
      /*
         To read the thermocouple I must to turn off the tip 
         and wait 50ms and then I can reactivate it
      */
      PWM_OFF();
      delay(TIME_SENS);
      read_Temperature = adc2celsius(ReadSensorADC(15));

      //PID and PWM management if Targhet 1 has been selected
      if (SelectTarget == TARGHET_1)
      {
        if (Target1 + Read_Encoder() > 0 && Target1 + Read_Encoder() < MAX_TEMP) PWM_ON((uint8_t)PID_On(read_Temperature, Target1 + Read_Encoder()));
        else if (Target1 + Read_Encoder() >= MAX_TEMP) PWM_ON((uint8_t)PID_On(read_Temperature, MAX_TEMP));
        else if (Target1 + Read_Encoder() < MIN_TEMP) PWM_ON((uint8_t)PID_On(read_Temperature, MIN_TEMP));
        //StreamingON(read_Temperature, Target1 + Read_Encoder()); //Graph of the Targhet temperature and the read temperature
      }
      
      //PID and PWM management if Targhet 2 has been selected
      if (SelectTarget == TARGHET_2)
      {
        if (Target2 + Read_Encoder() > 0 && Target2 + Read_Encoder() < MAX_TEMP) PWM_ON((uint8_t)PID_On(read_Temperature, Target2 + Read_Encoder()));
        else if (Target2 + Read_Encoder() >= MAX_TEMP) PWM_ON((uint8_t)PID_On(read_Temperature, MAX_TEMP));
        else if (Target2 + Read_Encoder() < MIN_TEMP) PWM_ON((uint8_t)PID_On(read_Temperature, MIN_TEMP));
        //StreamingON(read_Temperature, Target2 + Read_Encoder()); //Graph of the Targhet temperature and the read temperature
      }

      //By pressing quickly I can set the temperature targhet 1 or 2
      if (Read_Encoder_SW() == SHORTPRESS)
      {
        resetSW = 1;
        SelectTarget = !SelectTarget;
        ResetTimer();
        stateSW = UNPRESS;
      }
      //If I press for more than 3 seconds I go to the settings menu
      if (Read_Encoder_SW() == LONGPRESS)
      {
        resetSW = 1;
        stateFSM = SETTING;
        stateSW = UNPRESS;
      }
      break;

    case SETTING:
      PWM_OFF();  //Turn off the tip

      ShowSetting();
      
      //If I press for more than 3 seconds I return to the main menu
      if (Read_Encoder_SW() == LONGPRESS)
      {
        stateSetting = 0;
        resetSW = 1;
        stateFSM = MAINSCREEN;
        ResetTimer();
        stateSW = UNPRESS;
      }
      break;

    default:
      break;
  }
  
  wdt_reset(); //Whatchdog reset
}
