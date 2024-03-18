/************************************************************************************************
*            FILE: BATTERY.CPP
*          DRIVER: BATTERY
*     DESCRIPTION: Source file for all Battery-related functions declarations
*          Author: Tasneem Mansour.
*         Version: v1
*            Date: 10.3.2024
*
************************************************************************************************/


/*- INCLUDES
************************************************************************************************/
#include "battery.h"

/*- GLOBAL VARIABLES
************************************************************************************************/
float voltage;     /*battery voltage*/
float percentage;  /*battery percentage*/
int sensorValue;   /*Analog pin reading where voltage divider is connected to*/


/*- APIs' DECLARATION
************************************************************************************************/
float Battery_getBatteryVoltage()
{
  //Read the input on analog pin 14
  sensorValue = analogRead(batteryPin);

  //Convert the analog reading (which goes from 0 - 4095) to a voltage (0 - 3.3V):
  voltage = sensorValue * (3.3 / 4095.0);
  voltage *= 2;
  if(voltage > batteryMaxVoltage) voltage = batteryMaxVoltage;
  if(voltage < batteryMinVoltage) voltage = batteryMinVoltage;
  return voltage;
}

float Battery_getBatteryPercentage()
{
  //Calculate battery percentage
  //A zero percent battery doesn't indicate a 0V battery but rather 2.3V
  //Minimum threshold at which ESP32 can't be powered on with
  float batteryPercentage = (abs(voltage - batteryMinVoltage )/ (batteryMaxVoltage - batteryMinVoltage)) * 100;
  return batteryPercentage;
}
