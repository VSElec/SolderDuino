/*  Oled functions and Menu options
 *  File: Oled.cpp
 *  Ver: 1.0
 *  Created on: 06/06/2020
 *  Author: Stefano Valfrè
 */

#include "Oled.h"

//Variables for the Fade Led
long previousMillis = 0;   
byte i = 0;
bool dir_Led = 1;           // 1 = UP, 0 = DOWN
byte LED_MAX = 50;
byte LED_MIN = 0;
byte intervalLED = 20;      //Interval at which to blink (milliseconds)

//Selection variable in the setting menu
uint8_t stateSetting = 0;

//Read Temperature
extern int read_Temperature;

//Status variable of the encoder switch
extern byte stateSW;

//Reset the position of the encoder
extern bool resetSW;

//Reads the target temperatures in eeprom
uint16_t Target1 = ReadByte(ADDR_TEMP_1);
uint16_t Target2 = ReadByte(ADDR_TEMP_2);

//External variables timeout
extern int tminutes;
extern int seconds;
extern int counterTime;

//External variables of current and battery reading
extern uint16_t rawCurrent, rawSupply;
extern int supply, current;
extern float Vo_mv, Vi_mv, I, power;

//External variable that sets the dutycicle of the pwm (PID.h)
extern double Kp, Ki, Kd;
extern double Setpoint, Input, Output;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void OLED_Init(void)
{
  if (!display.begin(SSD1306_SWITCHCAPVCC))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
}

void ShowLogo(void)
{
  display.clearDisplay(); //for Clearing the display
  display.setCursor(0, 0);
  display.setTextColor(WHITE, BLACK);
  display.print(F("Soldering Station"));
  display.drawBitmap(0, 16, myLogo, 128, 64, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
}

void ShowMainScreen(bool SelectTarget, bool statusTIP, int ReadTemp)
{
  display.clearDisplay();
  //Targhet 1 selected
  if (SelectTarget == TARGHET1)
  {
    //Display Temperature Target1
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.print(F(">T1: "));
    display.print(Target1);
    display.print((char)247);
    display.println("C");

    //Display Temperature Target2
    display.setCursor(70, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.print(F("T2: "));
    display.print(Target2);
    display.print((char)247);
    display.println("C");

    //Display SetTemperature
    display.setCursor(0, 20);
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.print(F("Set: "));
    if (Target1 + Read_Encoder() >= MIN_TEMP && Target1 + Read_Encoder() <= MAX_TEMP) display.print(Target1 + Read_Encoder());
    else if (Target1 + Read_Encoder() < MIN_TEMP) display.print(MIN_TEMP);
    else if (Target1 + Read_Encoder() > MAX_TEMP) display.print(MAX_TEMP);
    display.print((char)247);
    display.println("C");
  }

  //Targhet 2 selected
  if (SelectTarget == TARGHET2)
  {
    //Display Temperature Target2
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.print(F("T1: "));
    display.print(Target1);
    display.print((char)247);
    display.println("C");

    //Display Temperature Target2
    display.setCursor(60, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.print(F(">T2: "));
    display.print(Target2);
    display.print((char)247);
    display.println("C");

    //Display SetTemperature
    display.setCursor(0, 20);
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.print(F("Set: "));
    if (Target2 + Read_Encoder() >= MIN_TEMP && Target2 + Read_Encoder() <= MAX_TEMP) display.print(Target2 + Read_Encoder());
    else if (Target2 + Read_Encoder() < MIN_TEMP) display.print(MIN_TEMP);
    else if (Target2 + Read_Encoder() > MAX_TEMP) display.print(MAX_TEMP);
    display.print((char)247);
    display.println("C");
  }

  //TIP OFF
  if (statusTIP == 0)
  {
    //Display IDLE
    display.setCursor(35, 35);
    display.setTextSize(2);
    display.setTextColor(WHITE, BLACK);
    display.println(F("IDLE"));
    FadeLed();
  }

  //TIP ON
  if (statusTIP == 1)
  {
    if (read_Temperature < 500)
    {
      analogWrite(LED_STATE, LED_MIN);
      //Display ReadTemperature
      display.setCursor(40, 35);
      display.setTextSize(2);
      display.setTextColor(WHITE, BLACK);
      //If you want to see the real temperature just leave the writing: display.print(ReadTemp);
      //Instead with the writing below if we have a difference of +/- 1 it only displays the writing of the Setpoint
      if (abs(Setpoint - Input) <= 1) display.print((int)Setpoint);
      else display.print(ReadTemp);
      display.print(" ");
      display.print((char)247);
      display.println("C");
    }
    else
    {
      //Display Unconect TIP
      analogWrite(LED_STATE, LED_MAX);
      display.setCursor(25, 35);
      display.setTextSize(1);
      display.setTextColor(WHITE, BLACK);
      display.println(F("Connect TIP"));
    }
  }

  //Dispaly Time
  display.setCursor(90, 57);
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.print(tminutes);
  display.print(":");
  display.println(seconds);

  display.setCursor(70, 20);
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.print("PWM: ");
  //The correct reading of the Duty is the Output variable but it is limited to MAX_PWM
  if ((uint8_t)Output > MAX_PWM) display.print(MAX_PWM);
  else display.print((uint8_t)Output);
  display.println("%");

  display.setCursor(0, 57);
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.print(F("Power: "));
  //If the pwm is 0 I show 0 otherwise I show the real power
  if ((uint8_t)Output == OFF) display.print(OFF);
  else display.print(ReadPower());
  display.println(F("W"));

  display.display();
}

void ShowSetting(void)
{
  Target1 = ReadByte(ADDR_TEMP_1);
  Target2 = ReadByte(ADDR_TEMP_2);

  display.clearDisplay();

  //Display Temperature Target1
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.print(F("Setting:"));

  switch (stateSetting)
  {
    case CHANGE_TARGHET1:
      display.setCursor(0, 20);
      display.setTextSize(1);
      display.setTextColor(BLACK, WHITE);
      display.print(F("Targhet1: "));
      display.print(Target1 + Read_Encoder());
      display.print((char)247);
      display.println("C");

      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Targhet2: "));
      display.print(Target2);
      display.print((char)247);
      display.println("C");

      display.setCursor(50, 57);
      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.println(F("Next: Set PID"));

      if (Read_Encoder_SW() == SHORTPRESS)
      {
        if (Target1 + Read_Encoder() > MIN_TEMP && Target1 + Read_Encoder() < MAX_TEMP) WriteByte(ADDR_TEMP_1, Target1 + Read_Encoder());
        else if (Target1 + Read_Encoder() < MIN_TEMP) WriteByte(ADDR_TEMP_1, MIN_TEMP);
        else if (Target1 + Read_Encoder() > MAX_TEMP) WriteByte(ADDR_TEMP_1, MAX_TEMP);
        stateSetting = CHANGE_TARGHET2;
        stateSW = UNPRESS;
        resetSW = 1;
      }
      break;

    case CHANGE_TARGHET2:
      display.setCursor(0, 20);
      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Targhet1: "));
      display.print(Target1);
      display.print((char)247);
      display.println("C");

      display.setTextSize(1);
      display.setTextColor(BLACK, WHITE);
      display.print(F("Targhet2: "));
      display.print(Target2 + Read_Encoder());
      display.print((char)247);
      display.println("C");

      display.setCursor(50, 57);
      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.println(F("Next: Set PID"));

      if (Read_Encoder_SW() == SHORTPRESS)
      {
        if (Target2 + Read_Encoder() > MIN_TEMP && Target2 + Read_Encoder() < MAX_TEMP) WriteByte(ADDR_TEMP_2, Target2 + Read_Encoder());
        else if (Target2 + Read_Encoder() < MIN_TEMP) WriteByte(ADDR_TEMP_2, MIN_TEMP);
        else if (Target2 + Read_Encoder() > MAX_TEMP) WriteByte(ADDR_TEMP_2, MAX_TEMP);

        stateSetting = SET_PID;
        stateSW = UNPRESS;
        resetSW = 1;
      }
      break;
      
    case SET_PID:
      display.setCursor(0, 20);
      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Targhet1: "));
      display.print(Target1);
      display.print((char)247);
      display.println("C");

      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Targhet2: "));
      display.print(Target2);
      display.print((char)247);
      display.println("C");

      display.setCursor(40, 57);
      display.setTextSize(1);
      display.setTextColor(BLACK, WHITE);
      display.println(F(">Next: Set PID"));

      if (Read_Encoder_SW() == SHORTPRESS)
      {
        stateSetting = SET_PARAM_PID_KP;
        stateSW = UNPRESS;
        resetSW = 1;
      }
      break;

    case SET_PARAM_PID_KP:
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Setting PID:"));
      display.setCursor(0, 20);
      display.setTextColor(BLACK, WHITE);
      display.print(F("Kp: "));
      display.println(Kp + (double)((Read_Encoder() / 5.0) / 10.0));
      display.setTextColor(WHITE, WHITE);
      display.print(F("Kd: "));
      display.println(Kd);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Ki: "));
      display.println(Ki);

      display.setCursor(40, 57);
      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.println(F("Next: Set Time"));

      if (Read_Encoder_SW() == SHORTPRESS)
      {
        stateSetting = SET_PARAM_PID_KD;
        Kp = Kp + (double)((Read_Encoder() / 5.0) / 10.0);
        if (Kp >= 0)WriteDouble(ADDR_KP, Kp);
        else
        {
          Kp = 0;
          WriteDouble(ADDR_KP, Kp = 0);
        }
        stateSW = UNPRESS;
        resetSW = 1;
      }
      break;

    case SET_PARAM_PID_KD:
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Setting PID:"));
      display.setCursor(0, 20);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Kp: "));
      display.println(Kp);
      display.setTextColor(BLACK, WHITE);
      display.print(F("Kd: "));
      display.println(Kd + (double)((Read_Encoder() / 5.0) / 10.0));
      display.setTextColor(WHITE, WHITE);
      display.print(F("Ki: "));
      display.println(Ki);

      display.setCursor(40, 57);
      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.println(F("Next: Set Time"));

      if (Read_Encoder_SW() == SHORTPRESS)
      {
        stateSetting = SET_PARAM_PID_KI;
        Kd = Kd + (double)((Read_Encoder() / 5.0) / 10.0);
        if (Kd >= 0)WriteDouble(ADDR_KD, Kd);
        else
        {
          Kd = 0;
          WriteDouble(ADDR_KD, Kd);
        }

        stateSW = UNPRESS;
        resetSW = 1;
      }
      break;

    case SET_PARAM_PID_KI:
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Setting PID:"));
      display.setCursor(0, 20);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Kp: "));
      display.println(Kp);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Kd: "));
      display.println(Kd);
      display.setTextColor(BLACK, WHITE);
      display.print(F("Ki: "));
      display.println(Ki + (double)((Read_Encoder() / 5.0) / 10.0));

      display.setCursor(40, 57);
      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.println(F("Next: Set Time"));

      if (Read_Encoder_SW() == SHORTPRESS)
      {
        stateSetting = CONFIRM_PID;
        Ki = Ki + (double)((Read_Encoder() / 5.0) / 10.0);
        if (Ki >= 0)WriteDouble(ADDR_KI, Ki);
        else
        {
          Ki = 0;
          WriteDouble(ADDR_KI, Ki);
        }
        stateSW = UNPRESS;
        resetSW = 1;
      }
      break;

    case CONFIRM_PID:
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Setting PID:"));
      display.setCursor(0, 20);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Kp: "));
      display.println(Kp);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Kd: "));
      display.println(Kd);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Ki: "));
      display.println(Ki);

      display.setCursor(35, 57);
      display.setTextSize(1);
      display.setTextColor(BLACK, WHITE);
      display.println(F(">Next: Set Time"));
      if (Read_Encoder_SW() == SHORTPRESS)
      {
        stateSetting = SET_TIME;
        stateSW = UNPRESS;
        resetSW = 1;
      }
      break;

    case SET_TIME:
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Setting TimeOut:"));
      counterTime = ReadByte(ADDR_TIME_OUT);
      tminutes = counterTime / 60;
      seconds = counterTime % 60;

      //Dispaly Time
      display.setCursor(40, 40);
      display.setTextSize(2);
      display.setTextColor(BLACK, WHITE);
      display.print(tminutes + (Read_Encoder() / 5));
      display.setTextColor(WHITE, WHITE);
      display.print(":");
      display.println(seconds);
      if (Read_Encoder_SW() == SHORTPRESS)
      {
        if (tminutes + (Read_Encoder() / 5) >= 0) tminutes = tminutes + (Read_Encoder() / 5);
        else tminutes = 0;
        stateSetting = SET_TIME_SECOND;
        stateSW = UNPRESS;
        resetSW = 1;
      }
      break;

    case SET_TIME_SECOND:
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.setTextColor(WHITE, WHITE);
      display.print(F("Setting TimeOut:"));
      //Dispaly Time
      display.setCursor(40, 40);
      display.setTextSize(2);
      display.setTextColor(WHITE, WHITE);
      display.print(tminutes);
      display.print(":");
      display.setTextColor(BLACK, WHITE);
      display.println(seconds + (Read_Encoder() / 5));
      if (Read_Encoder_SW() == SHORTPRESS)
      {
        if (seconds + (Read_Encoder() / 5) >= 0)seconds = seconds + (Read_Encoder() / 5);
        else seconds = 10; //Set at 10 seconds to avoid going below 0
        counterTime = tminutes * 60 + seconds;
        WriteByte(ADDR_TIME_OUT, counterTime);
        stateSetting = CHANGE_TARGHET1;
        stateSW = UNPRESS;
        resetSW = 1;
      }
      break;

    default:
      break;
  }

  display.display();
}

void ShowFault(void)
{
  display.clearDisplay();
  display.setCursor(35, 0);
  display.setTextSize(2);
  display.setTextColor(WHITE, WHITE);
  display.println(F("ERROR"));
  display.setCursor(0, 35);
  display.setTextSize(1);
  display.println(F("         HIGH"));
  display.println(F("     TEMPERATURE"));
  display.display();
}

void FadeLed(void)
{
  unsigned long currentMillis = millis();

  if (i == LED_MAX)
  {
    dir_Led = 0;
  }

  if (i == LED_MIN)
  {
    dir_Led = 1;
  }

  if (currentMillis - previousMillis > intervalLED && dir_Led == 1)
  {
    //Save the last time you blinked the LED
    previousMillis = currentMillis;
    i = i + 1; //Climb ramp
    analogWrite(LED_STATE, i); //Set the LED brightness
  }

  if (currentMillis - previousMillis > intervalLED && dir_Led == 0)
  {
    //Save the last time you blinked the LED
    previousMillis = currentMillis;
    i = i - 1; //Descent ramp
    analogWrite(LED_STATE, i); //Set the LED brightness
  }
}
