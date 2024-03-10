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
#include <Arduino.h>
#include "mpu6050.h"
#include "ultrasonic.h"
#include "battery.h"

/*- FUNCTIONS' PROTOTYES
************************************************************************************************/
void App_init(void);
void App_start(void);


#endif /* APP.H */