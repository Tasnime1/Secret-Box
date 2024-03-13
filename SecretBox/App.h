/************************************************************************************************
*            FILE: APP.H
*          DRIVER: APP
*     DESCRIPTION: Header file for all APPLICATION-related functions prototypes and constants
*          Author: Tasneem Mansour.
*         Version: v1
*            Date: 9.3.2024
*
************************************************************************************************/

#ifndef APP_H
#define APP_H


/*- INCLUDES
************************************************************************************************/
#include "Arduino.h"
#include "HardwareSerial.h"
#include "mpu6050.h"
#include "ultrasonic.h"
#include "battery.h"
#include <WiFi.h>
#include "time.h"
#include <ESP32Time.h>

/*- FUNCTIONS' PROTOTYES
************************************************************************************************/
void App_init(void);
void App_start(void);
void APP_getMPUreadings();
void APP_checkBoxHasFallen();
void APP_getUltrasonicReading();
void APP_checkBoxHasBeenOpened();
void APP_getBatteryReadings();

#endif /* APP.H */