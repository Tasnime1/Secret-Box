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

/*- APIs' DECLARATION
************************************************************************************************/
float Battery_getBatteryVoltage()
{
  //Read the input on analog pin 14
  int sensorValue = analogRead(batteryPin);

  //Convert the analog reading (which goes from 0 - 4095) to a voltage (0 - 3.3V):
  float voltage = sensorValue * (3.3 / 4095.0);
  voltage *= 2;
  if(voltage > batteryMaxVoltage) voltage = batteryMaxVoltage;
  return voltage;
}

float Battery_getBatteryPercentage()
{
  //Read the input on analog pin 14
  int sensorValue = analogRead(batteryPin);

  //Convert the analog reading (which goes from 0 - 4095) to a voltage (0 - 3.3V):
  float voltage = sensorValue * (3.3 / 4095.0);
  //Since it's a voltage divider circuit with 2 equal 10Kohm resistance then multiply voltage by 2
  voltage *= 2;
  //It's actually not a battery directly connected to the setup but but voltage taken from a voltage regulator
  //They're 3-series batteries with overall 12V
  //To-Do: Just use one battery for the application and comment this line out
  if(voltage > batteryMaxVoltage) voltage = batteryMaxVoltage;

  //Calculate battery percentage
  //A zero percent battery doesn't indicate a 0V battery but rather 2.3V
  //Minimum threshold at which ESP32 can't be powered on with
  float batteryPercentage = ((voltage - batteryMinVoltage )/ (batteryMaxVoltage - batteryMinVoltage)) * 100;
  return batteryPercentage;
}
