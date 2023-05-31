/*  First Run EEPROM
    File: FirstRun_1.0.ino
    Ver: 1.0
    Created on: 06/06/2020
    Author: Stefano Valfrè
*/

#include "E2prom.h"

#define ADDR_TEMP_1 0x00
#define ADDR_TEMP_2 0x02
#define ADDR_TIME_OUT 0x05
#define ADDR_KP 0x10
#define ADDR_KD 0x15
#define ADDR_KI 0x20
#define ADDR_FW 0x04

const int Temp1 = 250;
const int Temp2 = 350;
const int TimeOut = 600; //10min --> 10*60
const double Kp = 45.00;
const double Kd = 5.00;
const double Ki = 90.00;
const int ver_fw = 1;

void setup()
{
  //Initialize the LED pin as an output.
  pinMode(13, OUTPUT);
  Serial.begin(115200);

  for (int i = 0 ; i < EEPROM.length() ; i++)
  {
    EEPROM.write(i, 0);
  }
  Serial.println("Eeprom erased");

  //Write Targhet 1 in EEPROM
  WriteByte(ADDR_TEMP_1, Temp1);

  //Write Targhet 2 in EEPROM
  WriteByte(ADDR_TEMP_2, Temp2);

  //Write PID Kp in EEPROM
  WriteDouble(ADDR_KP, Kp);
  //Write PID Kd in EEPROM
  WriteDouble(ADDR_KD, Kd);
  //Write PID Ki in EEPROM
  WriteDouble(ADDR_KI, Ki);

  //Write firmware verision in EEPROM
  EEPROM.put(ADDR_FW, 1);


  //Write Timeout in EEPROM
  WriteByte(ADDR_TIME_OUT, TimeOut);
  Serial.println("Eeprom writing finished ");
}

void loop()
{
  if (ReadByte(ADDR_TEMP_1) == Temp1 && ReadByte(ADDR_TEMP_2) == Temp2 && EEPROM.read(ADDR_FW) == ver_fw && ReadByte(ADDR_TIME_OUT) == TimeOut && ReadDouble(ADDR_KP) == Kp && ReadDouble(ADDR_KD) == Kd && ReadDouble(ADDR_KI) == Ki)
  {
    Serial.println("Eeprom reading OK");
    digitalWrite(13, HIGH);
    Serial.print(F("FW Version: "));
    Serial.println(EEPROM.read(ADDR_FW));
    Serial.print(F("Temperature Targhet 1: "));
    Serial.print(ReadByte(ADDR_TEMP_1));
    Serial.println(F("°C"));
    Serial.print(F("Temperature Targhet 2: "));
    Serial.print(ReadByte(ADDR_TEMP_2));
    Serial.println(F("°C"));
    Serial.println(F("Parameters PID:"));
    Serial.print(F("Kp: "));
    Serial.println(ReadDouble(ADDR_KP));
    Serial.print(F("Ki: "));
    Serial.println(ReadDouble(ADDR_KI));
    Serial.print(F("Kd: "));
    Serial.println(ReadDouble(ADDR_KD));
    Serial.print(F("Timeout: "));
    Serial.println(ReadByte(ADDR_TIME_OUT)/60);
     Serial.println("");
  }
  else
  {
    Serial.println("Eeprom reading Error");
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }

}
