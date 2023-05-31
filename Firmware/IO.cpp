/*  Library for I/O functions initialize and Encoder read
    File: IO.cpp
    Ver: 1.0
    Created on: 06/06/2020
    Author: Stefano Valfrè
*/

#include "IO.h"

//Switch Encoder management variables
unsigned long startTime;
unsigned long endTime;
unsigned long duration;
byte timerRunning;
byte stateSW;  //Returns if it is a short or long press of the encoder

//Reset the position of the encoder
bool resetSW = 0;

//Definition of the encoder pin
Encoder myEnc(ENC_A, ENC_B);

void InitIO(void)
{
  //---------------------------------------------- Set PWM frequency for TIP PWM-----------------------------

  //TCCR2B = TCCR2B & B11111000 | B00000001;    // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000011;    // set timer 2 divisor to    32 for PWM frequency of   980.39 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000100;    // set timer 2 divisor to    64 for PWM frequency of   490.20 Hz (The DEFAULT)
  //TCCR2B = TCCR2B & B11111000 | B00000101;    // set timer 2 divisor to   128 for PWM frequency of   245.10 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000110;    // set timer 2 divisor to   256 for PWM frequency of   122.55 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000111;    // set timer 2 divisor to  1024 for PWM frequency of    30.64 Hz

  //UART Serial
  Serial.begin(115200);
  //Encoder Switch
  pinMode(ENC_SW, INPUT);
  //Heater
  pinMode(TIP, OUTPUT);
  //Status Led
  pinMode(LED_STATE, OUTPUT);
}

long Read_Encoder(void)
{
  //Every single shot changes the temperature by 5 ° C

  //If there is a reset = 1 then I reset the position of the encoder
  if (resetSW != 0)
  {
    myEnc.write(0);
    resetSW = 0;
  }
  long newPosition = myEnc.read();
  return (-newPosition / 4) * 5;
}

uint8_t Read_Encoder_SW(void)
{
  if (timerRunning == 0 && digitalRead(ENC_SW) == LOW)
  { 
    // button pressed & timer not running already
    startTime = millis();
    timerRunning = 1;
  }

  if (timerRunning == 1 && digitalRead(ENC_SW) == HIGH)
  { 
    // timer running, button released
    endTime = millis();
    timerRunning = 0;
    duration = endTime - startTime;

    if (duration > 50 && duration < 220)
    {
      //Shor Press
      stateSW = SHORTPRESS;
    }
    if (duration > 1000 && duration < 2000)
    {
      //Long Press
      stateSW = LONGPRESS;
    }
  }

  return stateSW;
}
