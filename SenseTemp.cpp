/*  Library for reading the thermocouple and the NTC
 *  File: SenseTemp.cpp
 *  Ver: 1.0
 *  Created on: 06/06/2020
 *  Author: Stefano Valfrè
 */

#include "SenseTemp.h"
/*
   To read the ADC value, simply write: ReadSensorADC(10) where 10 is the number of samples
   To convert to degrees, simply write: adc2celsius(ReadSensorADC(10))
*/
extern byte stateFSM;

uint16_t ReadSensorADC(byte avarage)
{
  //Make an average of N samples
  uint32_t result = 0;

  for (byte i = 0; i < avarage; i++)
  {
    result = result + analogRead(TEMP_SENSOR);
  }
  return ((uint16_t)(result / avarage));
}

//Values ​​Thermocouple D referred to 0 ° C in uV
/*unsigned int tc_uV[49] = {0, 98, 200, 305, 415, 528, 644, 765, 888, 1015,
                          1145, 1278, 1415, 1554, 1696, 1840, 1988, 2138, 2290, 2445,
                          2602, 2761, 2923, 3087, 3253, 3420, 3590, 3762, 3935, 4110,
                          4286, 4465, 4644, 4825, 5008, 5192, 5377, 5563, 5751, 5940,
                          6129, 6320, 6512, 6705, 6899, 7093, 7288, 7484, 7681
                         };
*/

//Adjusted thermocouple D values
unsigned int tc_uV[49] = {0, 98, 300, 455, 615, 728, 844, 1055, 1188, 1365, 1545,
                          1728, 1865, 2004, 2146, 2290, 2438, 2588, 2740, 2895, 3052,
                          3211, 3373, 3537, 3703, 3870, 4040, 4212, 4385, 4560, 4716,
                          4885, 5044, 5225, 5308, 5442, 5627, 5813, 6001, 6140, 6229,
                          6420, 6612, 6705, 6899, 7093, 7288, 7484, 7681
                         };
int Th = 0;
int Tl = 0;
int Vh = 0;
int Vl = 0;
int new_temp = 0;
int sum32;
byte j;
int deltaV = 0;
int deltaT = 0;
float diff = 0;

//Convert raw ADC value to temperature in °C
uint16_t adc2celsius(uint16_t adc_value)
{
  /*
    uint8_t offset = 25;

    uint32_t celsius = ((uint32_t) adc_value) * 113419;
    celsius = (celsius>>16) + offset;
    return ( (uint16_t)(celsius & 0xFFFF) );
  */

  sum32 = adc_value * 27; //Convert the value of the ADC to uV (5*1000000/1024)/179
  for (j = 0; j < 49; j++)
  {
    if (sum32 < tc_uV[j])
      break;
  }
  
  //Linearization of the thermocouple
  Vh = tc_uV[j];
  Vl = tc_uV[j - 1];
  Th = j * 10;
  Tl = (j - 1) * 10;
  deltaV = Vh - Vl;
  deltaT = Th - Tl;
  diff = ((float)sum32 - (float)Vl) / (float)deltaV;
  diff = diff * (float)deltaT;
  new_temp = Tl + (int)diff;
  return round(new_temp + NTCcelsius(ReadSensorNTC(10)));
}

uint16_t ReadSensorNTC(byte avarage)
{
  ////Make an average of N samples
  uint32_t result = 0;

  for (byte i = 0; i < avarage; i++)
  {
    result = result + analogRead(NTC);
  }
  return ((uint16_t)(result / avarage));
}

uint16_t NTCcelsius(uint16_t adc_value)
{
  //Linearization of the NTC
  //°C=(ADC-250,65)/10,42
  return (uint16_t)((adc_value - 250.65) / 10.42) - 3;
}
