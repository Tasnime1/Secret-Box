/************************************************************************************************
*            FILE: ULTRASONIC.CPP
*          DRIVER: ULTRASONIC
*     DESCRIPTION: Source file for all Ultrasonic-related functions declarations
*          Author: Tasneem Mansour.
*         Version: v1
*            Date: 10.3.2024
*
************************************************************************************************/


/*- INCLUDES
************************************************************************************************/
#include "ultrasonic.h"

/*- APIs' DECLARATION
************************************************************************************************/
void Ultrasonic_init(void) {
  // configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);
}

float ultrasonic_calc_distance(){
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  float duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate distance distance
  float distance_cm = 0.017 * duration_us;
  return distance_cm;
}

