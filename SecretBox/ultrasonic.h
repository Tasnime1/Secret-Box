/************************************************************************************************
*            FILE: ULTRASONIC.H
*          DRIVER: ULTRASONIC
*     DESCRIPTION: Header file for all Ultrasonic-related functions prototypes and constants
*          Author: Tasneem Mansour.
*         Version: v1
*            Date: 10.3.2024
*
************************************************************************************************/

#ifndef ULTRASONIC_H
#define ULTRASONIC_H


/*- INCLUDES
************************************************************************************************/
#include "Arduino.h"

/*- Defines
************************************************************************************************/
#define TRIG_PIN 23 //Trigger pin sending sound waves, OUTPUT
#define ECHO_PIN 19 //Echo pin receiving sound waves, INPUT

/*- APIs' PROTOTYES
************************************************************************************************/
void Ultrasonic_init(void);
float ultrasonic_calc_distance();

#endif /* ULTRASONIC.H */