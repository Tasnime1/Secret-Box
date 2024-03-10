/************************************************************************************************
*            FILE: BATTERY.H
*          DRIVER: BATTERY
*     DESCRIPTION: Header file for all Battery-related functions prototypes and constants
*          Author: Tasneem Mansour.
*         Version: v1
*            Date: 10.3.2024
*
************************************************************************************************/

#ifndef BATTERY_H
#define BATTERY_H


/*- INCLUDES
************************************************************************************************/
#include "Arduino.h"

/*- Defines
************************************************************************************************/
#define batteryPin 14
#define batteryMinVoltage 2.3
/**The 4.77 volts are measured practically
***When batteries were full and output of voltage regulator was 5 volts
***The sketch only got 4.77 indicating full capacity
***Adjust yours using same method
**/
#define batteryMaxVoltage 4.77

/*- APIs' PROTOTYES
************************************************************************************************/
float Battery_getBatteryVoltage();
float Battery_getBatteryPercentage();


#endif /* BATTERY.H */